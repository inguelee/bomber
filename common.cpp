#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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

char tempMap[19][40];
char map[19][40] = {
	{"11111111111111111111111111111111111111"},
	{"100000000000000000110000000000000000k1"},
	{"101101011k1101011011011010111110101101"},
	{"10000100010001000011000010001000100001"},
	{"11110111010111011111111011101011101111"},
	{"10000100000001010000k01010000000101000"},
	{"111101011l1101011101111010110110101111"},
	{"10000001000100000000000000100010000001"},
	{"111101010O010101111011101010k010101111"},
	{"0001010111110101p000001010111110101000"},
	{"11110100000001011111111010000000101111"},
	{"10000101111101000011000010111110100001"},
	{"10110000010000011011011000001000001101"},
	{"10010111010111010011001011101011101001"},
	{"11010001k00100010111101000100010001011"},
	{"1000010001000100001100001000100k100001"},
	{"10101111000111101011010111100011110101"},
	{"10000000010000000011000000001000000001"},
	{"11111111111111111111111111111111111111"},

};// 0 : 통로, 1 : 벽, k : 열쇠(아이템), p : 플레이어, O : 탈출구 ㅣ : 잠긴 문

void init();
void titleDraw();
int menuDraw();
void gotoxy(int, int);
int keyControl();
void gLoop();
void drawMap(int*, int*);
void setColor(int, int);
void drawUI(int, int);
void move(int*, int*, int, int);
void infoDraw();

int pKey = 0;
int playing = 1;

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
			pKey = 0;
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
	printf("<게임이 종료되었습니다>");
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

void titleDraw()
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

int menuDraw()
{
	int x = 27;
	int y = 14;
	gotoxy(x - 2, y);
	printf("> 게임시작");
	gotoxy(x, y + 1);
	printf("게임설명");
	gotoxy(x, y + 2);
	printf("  종료  ");
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

void gLoop()
{
	int mKey;
	int pX, pY;

	memcpy(tempMap, map, sizeof(tempMap));
	drawMap(&pX, &pY);
	while (playing)
	{
		drawUI(pX, pY);
		mKey = keyControl();
		switch (mKey)
		{
		case UP:
			move(&pX, &pY, 0, -1);
			break;
		case DOWN:
			move(&pX, &pY, 0, 1);
			break;
		case RIGHT:
			move(&pX, &pY, 1, 0);
			break;
		case LEFT:
			move(&pX, &pY, -1, 0);
			break;
		case SUBMIT:
			playing = 0;
		}

	}
	playing = 1;
}

void drawMap(int* pX, int* pY)
{
	char temp;
	system("cls");
	int h, w;
	for (h = 0; h < 19; h++)
	{
		for (w = 0; w < 40; w++)
		{
			temp = tempMap[h][w];
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
		}
		printf("\n");
	}
	setColor(white, black);
}
void setColor(int forground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}

void drawUI(int pX, int pY)
{
	setColor(white, black);

	gotoxy(40, 4);
	printf("플레이어 위치:(%02d,%02d)", pX, pY);

	setColor(yellow, black);
	gotoxy(45, 8);
	printf("열쇠: %d개", pKey);
	setColor(white, black);
}

void move(int* pX, int* pY, int _x, int _y)
{
	char mapObject = tempMap[*pY + _y][*pX + _x];
	setColor(white, black);

	if (mapObject == '0')
	{
		gotoxy(*pX, *pY);
		printf(" ");

		setColor(lightcyan, black);
		gotoxy(*pX + _x, *pY + _y);
		printf("@");
		*pX += _x;
		*pY += _y;
	}
	else if (mapObject == 'k')
	{
		pKey += 1;
		tempMap[*pY + _y][*pX + _x] = '0';
		gotoxy(*pX + _x, *pY + _y);
		printf(" ");
		if (pKey == 6)
		{
			tempMap[6][9] = '0';
			gotoxy(9, 6);
			printf(" ");

			setColor(lightred, black);
			gotoxy(41, 10);
			printf("탈출구가 열렸습니다");
		}
	}
	else if (mapObject == 'O')
	{
		playing = 0;
		setColor(yellow, black);
		gotoxy(39, 16);
		printf("! 탈출을 축하드립니다 !");
		Sleep(2000);
	}
}

void infoDraw()
{
	system("cls");
	printf("\n\n");
	printf("                        [ 게임설명 ]\n\n");
	printf("             몬스터들을 피하거나 폭탄으로 물리쳐\n");
	printf("                     열쇠를 얻어 탈출해라\n\n");
	printf("                        [ 조작법 ]\n\n");
	printf("                     이동: W, A, S, D\n\n");
	printf("                     폭탄설치: I, J, K, L\n\n");
	printf("                     선택: 스페이스바\n\n\n");
	printf("             개발자: 6조(강재윤, 이유진, 이인구)\n\n");
	printf("          스페이스바를 누르면 메인화면으로 이동합니다.");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}