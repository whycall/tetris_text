#include "./define.h"
/* 테트리스 판을 2차원 배열로 표현
 * 양옆 2줄과 맨 아래 한줄은 벽
 * 따라서  20*8 이
 * 실제 테트로미노 블록들이
 * 움직이고 놓이는 공간이됨*/
char tetris_table[21][10];

/* 게임 종료때 마다
 * 이름과 득점점수와
 * 날짜, 시간이저장되는 구조체
 * */
static struct result
{
	char name[30];
	long point;
	int year;
	int month;
	int day;
	int hour;
	int min;
	int rank;
}temp_result;

int block_number = 0;  /*현재 블록 넘버 변수*/
int next_block_number = 0; /*다음 블록 넘버 변수 */
int block_state = 0; /*블록 상태, 회전함에 따라 변한다*/
int x = 3, y = 0; /*블록이 현재 테트리스판 어디에 위치해 있는지 알려주는 변수*/
int game = GAME_END; /*게임 상태 변수, 게임이 시작되거나 종료됨에 따라 변한다*/
int best_point = 0; /* 게임 최고 점수를 알려주는 변수*/
long point = 0; /* 현재 게임중 득점을 알려주는 변수 */


