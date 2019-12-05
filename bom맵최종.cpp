#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

enum {
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};

//char tempMap[19][40];
char map[19][40] = {
	{"11111111111111111111111111111111111111"},
	{"1000000000000000g0110000a00000000000k1"},
	{"101101011k1101011011011010111110101101"},
	{"10000100010001000011000010001000100001"},
	{"11110111010111011111111011101011101111"},
	{"000101m0000001010000k01010000000101000"},
	{"111101011l1101011101111010110110101111"},
	{"1t00000100010000000000000e100010000001"},
	{"111101010O010101111011101010k010101111"},
	{"0001010111110101p000001010111110101000"},
	{"11110100000001011111111010000000101111"},
	{"100001011111010000110000101111101000f1"},
	{"1011c000010000011011011000001000001101"},
	{"10010111010111010011001011101011101001"},
	{"11010001k00100010111101000100010001011"},
	{"10000100010001000011000b1000100k100001"},
	{"10101111000111101011010111100011110101"},
	{"10000000010000000d11000000001000000001"},
	{"11111111111111111111111111111111111111"},

};// 0 : ���, 1 : ��, k : ����(������), p : �÷��̾�, O : Ż�ⱸ �� : ��� �� t : ������
int keyControl(void);
void titleDraw(void);
int menuDraw(void);

void infoDraw(void);

void init();
void gotoxy(int, int);
void setColor(int, int);
void drawMap(int* pX, int* pY, int* mX, int* mY, int* aX, int* aY, int* bX, int* bY, int* cX, int* cY, int* dX, int* dY, int* eX, int* eY, int* fX, int* fY, int* gX, int* gY, char(*tMap)[40]);
int move(char(*tMap)[40], int* pX, int* pY, int* mX, int* mY, int* aX, int* aY, int* bX, int* bY, int* cX, int* cY, int* dX, int* dY, int* eX, int* eY, int* fX, int* fY, int* gX, int* gY, int _x, int _y, int* pKey, int* item);
void gLoop(void);
void drawUI(int pX, int pY, int pKey);
void endDraw();

//int pKey = 0;
//int playing = 1;


int main(void)
{
	int menuCode;
	int playing = 1;

	init();
	while (1)
	{
		setColor(white, black);
		titleDraw();
		menuCode = menuDraw();

		if (menuCode == 0)
		{
			gLoop();
		}
		else if (menuCode == 1)
		{
			infoDraw();
		}
		else if (menuCode == 2)
		{
			break;
		}
		menuCode = 5;
		system("cls");
	}
	gotoxy(20, 18);
	printf("<������ ����Ǿ����ϴ�>");
	_getch();

	return 0;
}

void init()
{
	system("mode con cols=63 lines=20 | title Bomber Man");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void titleDraw(void)
{
	printf("\n");
	printf("                   *                                  \n");
	printf("           @@@@     *     @     @  @@@@   @@@@  @@@@  \n");
	printf("           @   @   @@@@   @@   @@  @   @  @     @   @ \n");
	printf("           @@@@   @    @  @ @ @ @  @@@@   @@@@  @@@@  \n");
	printf("           @   @  @    @  @  @  @  @   @  @     @  @  \n");
	printf("           @@@@    @@@@   @     @  @@@@   @@@@  @   @ \n");
	printf("\n");
	printf("                   @     @      @      @   @ \n");
	printf("                   @@   @@     @ @     @@  @ \n");
	printf("                   @ @ @ @    @@@@@    @ @ @ \n");
	printf("                   @  @  @   @     @   @  @@ \n");
}

int menuDraw(void)
{
	int x = 27;
	int y = 14;
	gotoxy(x - 2, y);
	printf("> ���ӽ���");
	gotoxy(x, y + 1);
	printf("���Ӽ���");
	gotoxy(x, y + 2);
	printf("  ����  ");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 14) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}

		case DOWN: {
			if (y < 16) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 14;
		}
		}
	}
}

void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int keyControl()
{
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{
		return SUBMIT;
	}
}

void gLoop(void)
{
	int mKey;
	int pX, pY, mX, mY, aX, aY, bX, bY, cX, cY, dX, dY, eX, eY, fX, fY, gX, gY;
	int pKey = 0;
	int playing = 1;
	int item = 0;
	char tempMap[19][40];

	memcpy(tempMap, map, sizeof(tempMap));
	drawMap(&pX, &pY, &mX, &mY, &aX, &aY, &bX, &bY, &cX, &cY, &dX, &dY, &eX, &eY, &fX, &fY, &gX, &gY, tempMap);
	while (playing)
	{
		drawUI(pX, pY, pKey);
		mKey = keyControl();
		switch (mKey)
		{
		case UP:
			playing = move(tempMap, &pX, &pY, &mX, &mY, &aX, &aY, &bX, &bY, &cX, &cY, &dX, &dY, &eX, &eY, &fX, &fY, &gX, &gY, 0, -1, &pKey, &item);
			break;
		case DOWN:
			playing = move(tempMap, &pX, &pY, &mX, &mY, &aX, &aY, &bX, &bY, &cX, &cY, &dX, &dY, &eX, &eY, &fX, &fY, &gX, &gY, 0, 1, &pKey, &item);
			break;
		case RIGHT:
			playing = move(tempMap, &pX, &pY, &mX, &mY, &aX, &aY, &bX, &bY, &cX, &cY, &dX, &dY, &eX, &eY, &fX, &fY, &gX, &gY, 1, 0, &pKey, &item);
			break;
		case LEFT:
			playing = move(tempMap, &pX, &pY, &mX, &mY, &aX, &aY, &bX, &bY, &cX, &cY, &dX, &dY, &eX, &eY, &fX, &fY, &gX, &gY, -1, 0, &pKey, &item);
			break;
		case SUBMIT:
			playing = 0;
		}

	}
	//playing = 1;
}

void drawMap(int* pX, int* pY, int* mX, int* mY, int* aX, int* aY, int* bX, int* bY, int* cX, int* cY, int* dX, int* dY, int* eX, int* eY, int* fX, int* fY, int* gX, int* gY, char(*tMap)[40])
{
	char temp;
	system("cls");
	int h, w;
	for (h = 0; h < 19; h++)
	{
		for (w = 0; w < 40; w++)
		{
			temp = tMap[h][w];
			if (temp == '0')
			{
				setColor(black, black);
				printf(" ");
			}
			else if (temp == '1')
			{
				setColor(white, white);
				printf("#");
			}
			else if (temp == 'p')
			{
				*pX = w;
				*pY = h;
				setColor(lightcyan, black);
				printf("@");
			}
			else if (temp == 'O')
			{
				setColor(lightgreen, black);
				printf("O");
			}
			else if (temp == 'k')
			{
				setColor(yellow, black);
				printf("*");
			}
			else if (temp == 'l')
			{
				setColor(white, white);
				printf("#");
			}
			else if (temp == 'm')
			{
				*mX = w;
				*mY = h;
				setColor(lightred, black);
				printf("M");
			}
			else if (temp == 't')
			{
				setColor(cyan, black);
				printf("?");
			}
			else if (temp == 'a')
			{
				*aX = w;
				*aY = h;
				setColor(lightred, black);
				printf("M");
			}
			else if (temp == 'b')
			{
				*bX = w;
				*bY = h;
				setColor(lightred, black);
				printf("M");
			}
			else if (temp == 'c')
			{
				*cX = w;
				*cY = h;
				setColor(lightred, black);
				printf("M");
			}
			else if (temp == 'd')
			{
				*dX = w;
				*dY = h;
				setColor(lightred, black);
				printf("M");
			}
			else if (temp == 'e')
			{
				*eX = w;
				*eY = h;
				setColor(lightred, black);
				printf("M");
			}
			else if (temp == 'f')
			{
				*fX = w;
				*fY = h;
				setColor(lightred, black);
				printf("M");
			}
			else if (temp == 'g')
			{
				*gX = w;
				*gY = h;
				setColor(lightred, black);
				printf("M");
			}

		}
		printf("\n");
	}
	setColor(white, black);
}
void setColor(int forground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}

void drawUI(int pX, int pY, int pKey)
{
	setColor(white, black);

	gotoxy(40, 4);
	printf("�÷��̾� ��ġ:(%02d,%02d)", pX, pY);

	setColor(yellow, black);
	gotoxy(45, 8);
	printf("����: %d/6��", pKey);

	setColor(white, black);
}

int move(char(*tMap)[40], int* pX, int* pY, int* mX, int* mY, int* aX, int* aY, int* bX, int* bY, int* cX, int* cY, int* dX, int* dY, int* eX, int* eY, int* fX, int* fY, int* gX, int* gY, int _x, int _y, int* pKey, int* item)
{
	int playflag = 1;
	char mapObject = tMap[*pY + _y][*pX + _x];
	char mapObject1 = tMap[*mY + _y][*mX + _x];
	char mapObject2 = tMap[*aY + _y][*aX + _x];
	char mapObject3 = tMap[*bY + _y][*bX + _x];
	char mapObject4 = tMap[*cY + _y][*cX + _x];
	char mapObject5 = tMap[*dY + _y][*dX + _x];
	char mapObject6 = tMap[*eY + _y][*eX + _x];
	char mapObject7 = tMap[*fY + _y][*fX + _x];
	char mapObject8 = tMap[*gY + _y][*gX + _x];



	setColor(white, black);

	if (mapObject == '0')
	{
		tMap[*pY][*pX] = '0';
		gotoxy(*pX, *pY);
		printf(" ");
		setColor(lightcyan, black);
		tMap[*pY + _y][*pX + _x] = 'p';
		gotoxy(*pX + _x, *pY + _y);
		printf("@");
		*pX += _x;
		*pY += _y;
	}
	if (mapObject1 == '0')
	{
		tMap[*mY][*mX] = '0';
		gotoxy(*mX, *mY);
		printf(" ");
		setColor(lightred, black);
		tMap[*mY + _y][*mX + _x] = 'm';
		gotoxy(*mX + _x, *mY + _y);
		printf("M");
		*mX += _x;
		*mY += _y;
	}
	if (mapObject2 == '0')
	{
		tMap[*aY][*aX] = '0';
		gotoxy(*aX, *aY);
		printf(" ");
		setColor(lightred, black);
		tMap[*aY + _y][*aX + _x] = 'a';
		gotoxy(*aX + _x, *aY + _y);
		printf("M");
		*aX += _x;
		*aY += _y;
	}
	if (mapObject3 == '0')
	{
		tMap[*bY][*bX] = '0';
		gotoxy(*bX, *bY);
		printf(" ");
		setColor(lightred, black);
		tMap[*bY + _y][*bX + _x] = 'b';
		gotoxy(*bX + _x, *bY + _y);
		printf("M");
		*bX += _x;
		*bY += _y;
	}
	if (mapObject4 == '0')
	{
		tMap[*cY][*cX] = '0';
		gotoxy(*cX, *cY);
		printf(" ");
		setColor(lightred, black);
		tMap[*cY + _y][*cX + _x] = 'c';
		gotoxy(*cX + _x, *cY + _y);
		printf("M");
		*cX += _x;
		*cY += _y;
	}
	if (mapObject5 == '0')
	{
		tMap[*dY][*dX] = '0';
		gotoxy(*dX, *dY);
		printf(" ");
		setColor(lightred, black);
		tMap[*dY + _y][*dX + _x] = 'd';
		gotoxy(*dX + _x, *dY + _y);
		printf("M");
		*dX += _x;
		*dY += _y;
	}
	if (mapObject6 == '0')
	{
		tMap[*eY][*eX] = '0';
		gotoxy(*eX, *eY);
		printf(" ");
		setColor(lightred, black);
		tMap[*eY + _y][*eX + _x] = 'd';
		gotoxy(*eX + _x, *eY + _y);
		printf("M");
		*eX += _x;
		*eY += _y;
	}
	if (mapObject7 == '0')
	{
		tMap[*fY][*fX] = '0';
		gotoxy(*fX, *fY);
		printf(" ");
		setColor(lightred, black);
		tMap[*fY + _y][*fX + _x] = 'd';
		gotoxy(*fX + _x, *fY + _y);
		printf("M");
		*fX += _x;
		*fY += _y;
	}
	if (mapObject8 == '0')
	{
		tMap[*gY][*gX] = '0';
		gotoxy(*gX, *gY);
		printf(" ");
		setColor(lightred, black);
		tMap[*gY + _y][*gX + _x] = 'd';
		gotoxy(*gX + _x, *gY + _y);
		printf("M");
		*gX += _x;
		*gY += _y;
	}


	if (mapObject == 'm' || mapObject == 'a' || mapObject == 'b' || mapObject == 'c' || mapObject == 'd' || mapObject == 'e' || mapObject == 'f' || mapObject == 'g' || mapObject5 == 'p' || mapObject1 == 'p' || mapObject2 == 'p' || mapObject3 == 'p' || mapObject4 == 'p' || mapObject6 == 'p' || mapObject7 == 'p' || mapObject8 == 'p')
	{
		playflag = 0;
		endDraw();
		Sleep(3000);

	}
	else if (mapObject == 'k')
	{
		*pKey += 1;
		tMap[*pY + _y][*pX + _x] = '0';
		gotoxy(*pX + _x, *pY + _y);
		printf(" ");
		if (*pKey == 6)
		{
			tMap[6][9] = '0';
			gotoxy(9, 6);
			printf(" ");

			setColor(lightgreen, black);
			gotoxy(41, 12);
			printf("Ż�ⱸ�� ���Ƚ��ϴ�");
		}
	}
	else if (mapObject == 'O')
	{
		playflag = 0;
		setColor(yellow, black);
		gotoxy(39, 16);
		printf("! Ż���� ���ϵ帳�ϴ� !");
		Sleep(5000);
	}
	else if (mapObject == 't')
	{
		srand(time(NULL));
		*item += rand() % 2 + 1;
		tMap[*pY + _y][*pX + _x] = '0';
		gotoxy(*pX + _x, *pY + _y);
		printf(" ");
		if (*item == 1)
		{
			playflag = 0;
			endDraw();
			Sleep(3000);
		}
		else if (*item == 2)
		{
			tMap[6][9] = '0';
			gotoxy(9, 6);
			printf(" ");

			setColor(lightgreen, black);
			gotoxy(41, 12);
			printf("Ż�ⱸ�� ���Ƚ��ϴ�");
		}
	}

	return playflag;
}

void infoDraw(void)
{
	system("cls");
	printf("\n");
	printf("                        [ ���Ӽ��� ]\n\n");
	printf("             ���͵��� ���ϰų� ��ź���� ������\n");
	printf("                    ���踦 ��� Ż���ض�\n\n");
	printf("              ������ : ��ź OR Ż�ⱸ ���� Key\n");
	printf("                *���� ���� �����ۿ� �ðܺ�*\n\n");
	printf("                        [ ���۹� ]\n\n");
	printf("                     �̵�: W, A, S, D\n");
	printf("                     ��ź��ġ: I, J, K, L\n");
	printf("                     ����: �����̽���\n\n");
	printf("             ������: 6��(������, ������, ���α�)\n\n");
	printf("         �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

void endDraw()
{
	system("cls");
	setColor(white, black);
	printf("\n\n\n\n\n");
	printf("               *             *             *\n");
	printf("                *             *             *\n");
	printf("               ###           ###           ###\n");
	printf("              #####         #####         #####\n");
	printf("               ###           ###           ###\n\n\n");
	printf("                        - Ż�� ���� -\n\n\n");
	printf("                  ! �ٽ� �� �� �����ϼ��� !");
}
