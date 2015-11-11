#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define LEFT 0
#define RIGHT 1
#define DOWN 2
#define ROTATE 3

#define I_BLOCK 0
#define	T_BLOCK 1
#define S_BLOCK 2
#define Z_BLOCK 3
#define L_BLOCK 4
#define J_BLOCK 5
#define O_BLOCK 6


#define GAME_START 0
#define GAME_END 1

int game_start(void)
{ 
     static struct sigaction sa;
     static struct itimerval timer;
     time_t ptime; 
     struct tm *t; 
     FILE *fp = NULL; 
  
     if(game == GAME_START) 
     { 
         init_tetris_table(); 
  
         /* Install timer_handler as the signal handler for SIGVTALRM. */
         memset(&sa, 0, sizeof (sa));
         sa.sa_handler = &refresh; 
         sigaction(SIGVTALRM, &sa, NULL);
  
         /* Configure the timer to expire after 250 msec... */
         timer.it_value.tv_sec = 0; 
         timer.it_value.tv_usec = 1; 
  
         /* ... and every 250 msec after that. */
         timer.it_interval.tv_sec = 0; 
         timer.it_interval.tv_usec = 1; 
  
         /* Start a virtual timer. It counts down whenever this process is executing. */
         setitimer(ITIMER_VIRTUAL, &timer, NULL);
 
         /* Do busy work.  */ 
  
         while(1) 
         { 
             if(game == GAME_END) 
             { 
  
                 timer.it_value.tv_sec = 0;
                 timer.it_value.tv_usec = 0;
                 timer.it_interval.tv_sec = 0;
                 timer.it_interval.tv_usec = 0;
                 setitimer(ITIMER_VIRTUAL,&timer,NULL); 
  
  
                 // 기록 파일로 저장 
  
                 printf("\n\n 최종 득점 : %ld ", point); 
                 printf("\n\n 이름을 입력 하세요 : "); 
                 scanf("%s%*c", temp_result.name); 
                 temp_result.point = point; 
  
                 if(temp_result.point >= best_point) 
                     best_point = temp_result.point; 
  
  
                 ptime = time(NULL); // 현재 시각을 초 단위로 얻기 
                 t = localtime(&ptime); // 초 단위의 시간을 분리하여 구조체에 넣기 
  
                 temp_result.year = t->tm_year + 1900; 
                 temp_result.month = t->tm_mon + 1; 
                 temp_result.day = t->tm_mday; 
                 temp_result.hour = t->tm_hour; 
                 temp_result.min = t->tm_min; 
  
                 fp = fopen("result", "ab"); 
                 fseek(fp, 1, SEEK_END); 
                 fwrite(&temp_result, sizeof(struct result), 1, fp); 
                 fclose(fp); 
  
                 x = 3, y =0; 
                 point = 0; 
  
                 return 1;
             } 
         } 
     } 
  
   return 0;
 } 
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
