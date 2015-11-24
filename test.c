#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define LEFT 75
#define RIGHT 77
#define ROTATE 72
#define UP_ROTATE 100
#define DOWN 80
#define SPACE 32

#define SINGLE 0
#define PLAYER1 1
#define PLAYER2 2
#define COMPUTER 3

#define ACTIVE_BLOCK ((block.type+11)*(-1))
#define CEILLING -1
#define EMPTY 0
#define WALL 1
#define INACTIVE_BLOCK (block.type+11)



void gotoxy(int x,int y) {

	COORD pos={2*x,y};

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

}
