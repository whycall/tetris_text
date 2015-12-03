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
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void setcursortype(CURSOR_TYPE c){

     CONSOLE_CURSOR_INFO CurInfo;

 

     switch (c) {

     case NOCURSOR:

          CurInfo.dwSize=1;

          CurInfo.bVisible=FALSE;

          break;

     case SOLIDCURSOR:

          CurInfo.dwSize=100;

          CurInfo.bVisible=TRUE;

          break;

     case NORMALCURSOR:

          CurInfo.dwSize=20;

          CurInfo.bVisible=TRUE;

          break;

     }

     SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);

}



class Blocks{

public:

	Blocks(void){

		type_next=rand()%7;

	}

	static const int shape[7][4][4][4]; 

	int x;

	int y;

	int type;

	int rotation;

	int type_next;

	int getColor(int num);

};

const int Blocks::shape[7][4][4][4]={

	{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},

	{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},

	{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},

	{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},

	{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},

	{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},{0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},

	{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},{0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}}

};

int Blocks::getColor(int num){

	if(num<0) num*=(-1);

	return num-9;

}



class Tetris{

public:

	Tetris(int game_x,int game_y,int status_x,int status_y, int owner);

	

	int fCnt;

	int owner;

	int score;

	int lineCnt;



	static const int speed[11];

		int level;



	int game_x;

	int game_y;

	int status_x;

	int status_y;



	static const int WIDTH=11;

	static const int HEIGHT=23;



	int gameOrg[HEIGHT][WIDTH];

	int gameCpy[HEIGHT][WIDTH];

		void resetGameCpy(void){

			for(int i=0;i<HEIGHT;i++) for(int j=0;j<WIDTH;j++) gameCpy[i][j]=999;

		}
		
void drawGame(void);

	void newBlock(void);
		Blocks block;
		void move_block(int dir);
		void dropBlock(void);
		bool checkCrush(int x, int y, int rotation);
			bool crush_on;
	
	void initialGame(void);

	void gameOver(void);
		bool gameOver_on;
		int gameOverCnt; 
		int gameOverP; 
		
	void gameDelay(int cnt);
		bool gameDelay_on;
		int gameDelayCnt;
		void gameDelay(void); 

	void gameMsg(int x, int y, int type, int val=0);
		int gameMsgCnt;
		void gameMsg(void);

	void getKey(void);
		int keyCnt;
		bool upRotate_on;
		
	void checkLine(void); 
		int pushAttackReg[HEIGHT][WIDTH];
		int pushAttackRegP; 
	
	void getAttack(void);
		int getAttackReg[HEIGHT][WIDTH];
		int getAttackRegP; 
		int attackQueue_x; 
		
	int comOutput; 
		void comCheck(void); 
			int comX[10]; 
			int comY[10]; 
			int comR[10]; 
			int comXYRP; 
			int comGameValue[HEIGHT][WIDTH]; 
			int comGameUnder[HEIGHT][WIDTH]; 
			bool comCheck_on; 
			int comCheckAroundValue(int x, int y, int rotation); 
};
const int Tetris::speed[11]={20,20,15,10,20,10,5,15,10,2,1}; 

int Tetris::comCheckAroundValue(int x, int y, int rotation){
	int sum=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){ 
			if(block.shape[block.type][rotation][i][j]==1){
				for(int k=0;k<4;k++){
					switch(k){
					case 0:
						if(((i==0)&&(comGameValue[y+i-1][x+j]>0)) || 
							((i!=0)&&(block.shape[block.type][rotation][i-1][j]!=1)&&(comGameValue[y+i-1][x+j]>0))) sum+=comGameValue[y+i-1][x+j];
						break;
					case 1:
						if((i==4)|| 
							(block.shape[block.type][rotation][i+1][j]!=1)) sum+=comGameValue[y+i+1][x+j];
						break;
					case 2:
						if(((j==0)&&(comGameValue[y+i][x+j-1]>0)) || 
							((j!=0)&&(block.shape[block.type][rotation][i][j-1]!=1)&&(comGameValue[y+i][x+j-1]>0))) sum+=comGameValue[y+i][x+j-1];
						break;
					case 3:
						if(((j==4)&&comGameValue[y+i][x+j+1]>0) || 
							((j!=4)&&(block.shape[block.type][rotation][i][j+1]!=1)&&(comGameValue[y+i][x+j+1]>0))) sum+=comGameValue[y+i][x+j+1];
						break;
					}
				}
			}
		}
	}	
	return sum;
}
void Tetris::comCheck(void){
	int val=0;

	if(comCheck_on==true){
		for(int i=0;i<10;i++){
			comX[i]=0;
			comY[i]=0;
			comR[i]=0;
		}
		comXYRP=0;

		for(int i=0;i<HEIGHT;i++){
			for(int j=0;j<WIDTH;j++){
				if(gameOrg[i][j]>0) comGameValue[i][j]=i;
				else comGameValue[i][j]=0;
			}
		}
		for(int i=0;i<HEIGHT-1;i++){
			for(int j=0;j<WIDTH;j++){
				if(comGameValue[i][j]==0&&(comGameValue[i][j-1]>0||comGameValue[i][j+1]>0)) comGameValue[i][j]=(-i);
			}
		}
		for(int i=0;i<HEIGHT;i++){ 
			for(int j=0;j<WIDTH;j++){
				comGameUnder[i][j]=0;
			}
		}
		for(int i=0;i<HEIGHT;i++){ 
			for(int j=1;j<WIDTH-1;j++){
				if(gameOrg[i][j]>0&&gameOrg[i-1][j]==0){
					for(int k=i-1;k>0;k--){
						if(gameOrg[k][j]>0){
							for(int m=i-1;m>k;m--) comGameUnder[m][j]=1;
							break;
						}
					}
				}
			}
		}

		for(int i=0;i<21;i++){
			for(int j=0;j<WIDTH;j++){
				for(int k=0;k<4;k++){		

					if(checkCrush(j,i+1,k)==false&&checkCrush(j,i,k)==true&&comCheckAroundValue(j,i,k)>val){
						bool onUnder=false;						
						for(int m=0;m<4;m++){ 
							for(int n=0;n<4;n++){
								if(block.shape[block.type][k][m][n]==1&&comGameUnder[i+m][j+n]==1){
									onUnder=true;
								}
							}
						}					
						if(onUnder==false){ 		
							comXYRP=0;
							val=comCheckAroundValue(j,i,k);
							comX[0]=j;
							comY[0]=i;
							comR[0]=k;						
						}
						if(onUnder==true){ 
							comXYRP=0;

							if(checkCrush(j+1,i,k)==false&&checkCrush(j-1,i,k)==false&&checkCrush(j,i-1,k)==false) break;

							int tempX1=j;
							int tempY1=i;
							int tempX2=j;
							int tempY2=i;
							int tempXYRP=0;

							bool underStuck=true; 
							for(int s=1;s>-2;s-=2){ 
								for(int x=0;x<WIDTH;x++){
									if(underStuck==false) break;
									for(int y=0;y<HEIGHT;y++){
										if(tempY1-y==0){
											underStuck=false;
											tempXYRP++;
											comX[tempXYRP]=j+x*s;
											comY[tempXYRP]=tempY1;
											comR[tempXYRP]=k;
											break;
										}
										else if(checkCrush(j+x*s,tempY1-y,k)==true){
											tempX2=j+x*s;
											tempY2=tempY1-y;
										}
										else if(checkCrush(tempX1+x*s,tempY1-y,k)==false) break;
										
									}
									if(tempX1==tempX2 && tempY1==tempY2 && x!=0) break;
									else {
										tempX1=tempX2;
										tempY1=tempY2;
									}
								}
							}

							if(underStuck==false){
								val=comCheckAroundValue(j,i,k);							
								comX[0]=j;
								comY[0]=i;
								comR[0]=k;	
								comXYRP=tempXYRP;
							}
						}
					}
				}
			}
		}
		comCheck_on=false;
	}

	if(block.rotation!=comR[comXYRP]) comOutput=ROTATE;
	else if(comX[comXYRP]>block.x) comOutput=RIGHT;
	else if(comX[comXYRP]<block.x) comOutput=LEFT;
	else if(comX[comXYRP]==block.x) if(comXYRP==0) comOutput=SPACE; else  comOutput=DOWN;

	if(comX[comXYRP]==block.x && comY[comXYRP]==block.y && comR[comXYRP]==block.rotation && comXYRP>0) comXYRP--;
}
Tetris::Tetris(int game_x,int game_y,int status_x,int status_y, int owner){ 
	level=1;
	score=0;
	lineCnt=0;
	keyCnt=0;
	fCnt=speed[level];

	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			gameOrg[i][j]=0;
			gameCpy[i][j]=NULL;
			pushAttackReg[i][j]=-1;
			getAttackReg[i][j]=-1;
		}
	}	
	pushAttackRegP=HEIGHT-1;
	getAttackRegP=HEIGHT-1;

	this->game_x=game_x;
	this->game_y=game_y;
	this->status_x=status_x;
	this->status_y=status_y;
	this->owner=owner;
	
	upRotate_on=false;
	crush_on=false;
	gameDelay_on=false;
	gameDelayCnt=-1;
	gameOver_on=false;
	gameOverCnt=-1;
	gameMsgCnt=-1;
	comCheck_on=true;
	
	initialGame(); 
	newBlock(); 
}

void Tetris::initialGame(void){
	int i,j;

	for(j=1;j<WIDTH;j++){ 
		gameOrg[3][j]=CEILLING;
	}
	for(i=1;i<HEIGHT-1;i++){ 
		gameOrg[i][0]=WALL;
		gameOrg[i][WIDTH-1]=WALL;
	}
	for(j=0;j<WIDTH;j++){
		gameOrg[HEIGHT-1][j]=WALL;
	}

	gotoxy(status_x, status_y);
	switch(owner){
	case 0:
		printf("< PLAYER >");
		attackQueue_x=game_x-1;
		break;
	case 1:
		printf("<PLAYER1>");
		attackQueue_x=game_x-1;
		break;
	case 2:
		printf("<PLAYER2>");
		attackQueue_x=game_x+WIDTH;
		break;
	case 3:
		printf("<COMPUTER>");
		attackQueue_x=game_x+WIDTH;
		break;
	}
	gotoxy(status_x, status_y+1);
	printf("Next:");
	gotoxy(status_x, status_y+6);
	if(level==10) printf("Level:MAX");
	else printf("Level:%2d",level);
	gotoxy(status_x, status_y+7);
	printf("Speed:%2d",speed[level]);
}
void Tetris::getKey(){
	dropBlock();
	if(keyCnt>0){
		keyCnt--;
		return;
	}
	if(owner==COMPUTER)comCheck();

	keyCnt=3;

	if(((owner==SINGLE||owner==PLAYER2)&&GetAsyncKeyState(VK_LEFT)) || 
		(owner==PLAYER1&&GetAsyncKeyState('F')) ||
		(owner==COMPUTER&&comOutput==LEFT))
		if(checkCrush(block.x-1,block.y,block.rotation)==true) move_block(LEFT); 
	if(((owner==SINGLE||owner==PLAYER2)&&GetAsyncKeyState(VK_RIGHT)) || 
		(owner==PLAYER1&&GetAsyncKeyState('H')) ||
		(owner==COMPUTER&&comOutput==RIGHT))
		if(checkCrush(block.x+1,block.y,block.rotation)==true) move_block(RIGHT);
	if(((owner==SINGLE||owner==PLAYER2)&&GetAsyncKeyState(VK_DOWN)) || (owner==PLAYER1&&GetAsyncKeyState('G')) ||
		(owner==COMPUTER&&comOutput==DOWN)) 
		if(checkCrush(block.x,block.y+1,block.rotation)==true) move_block(DOWN);
	if(((owner==SINGLE||owner==PLAYER2)&&GetAsyncKeyState(VK_UP)) || (owner==PLAYER1&&GetAsyncKeyState('T')) ||
		(owner==COMPUTER&&comOutput==ROTATE)) {
		if(checkCrush(block.x,block.y,(block.rotation+1)%4)==true) move_block(ROTATE);
		else if(crush_on==true&&checkCrush(block.x,block.y-1,(block.rotation+1)%4)==true) move_block(UP_ROTATE); 
	}
	if((owner==SINGLE&&(GetAsyncKeyState(VK_SPACE)||GetAsyncKeyState('L'))) || 
		(owner==PLAYER2&&GetAsyncKeyState('L')) || 
		(owner==PLAYER1&&GetAsyncKeyState('Q')) ||
		(owner==COMPUTER&&comOutput==SPACE)){
		while(crush_on==false){
			dropBlock();
			score+=level;
		}
		fCnt=0;
	}


	if(GetAsyncKeyState('Z')){
		block.type_next=1;
	}

}
void Tetris::move_block(int dir){ 
	int i,j;
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j]=EMPTY;
		}
	}

	switch(dir){
	case LEFT:
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j-1]=ACTIVE_BLOCK;
			}
		}
		block.x--;
		break;
	case RIGHT: 
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j+1]=ACTIVE_BLOCK;
			}
		}
		block.x++;		
		break;
	case DOWN:
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i+1][block.x+j]=ACTIVE_BLOCK;
			}
		}
		block.y++;		
		break;
	case ROTATE:
		block.rotation=(block.rotation+1)%4;
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j]=ACTIVE_BLOCK;
			}
		}
		break;
	case UP_ROTATE:
		block.rotation=(block.rotation+1)%4;
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i-1][block.x+j]=ACTIVE_BLOCK;
			}
		}
		block.y--;
		upRotate_on=true;
		break;
	}
}
void Tetris::checkLine(void){
	int i, j;
	
	int	block_amount;
	int combo=0;
	
	for(i=HEIGHT-2;i>3;){
		block_amount=0;
		for(j=1;j<WIDTH-1;j++){ 
			if(gameOrg[i][j]>0) block_amount++;
		}
		if(block_amount==WIDTH-2){
			score+=100*level;
			lineCnt++;
			combo++; 

			if(pushAttackRegP>0){ 
				for(int m=1;m<WIDTH-1;m++){
					if(m>block.x&&m<block.x+4&&block.shape[block.type][block.rotation][i-block.y][m-block.x]==1) pushAttackReg[pushAttackRegP][m]=0;
					else pushAttackReg[pushAttackRegP][m]=16;
				}
				pushAttackRegP--;
				block.y++;
			}

			for(int k=i;k>1;k--){ 
				for(int l=1;l<WIDTH-1;l++){
					if(gameOrg[k-1][l]!=CEILLING) gameOrg[k][l]=gameOrg[k-1][l];
					if(gameOrg[k-1][l]==CEILLING) gameOrg[k][l]=EMPTY; 
				}
			}
		}
		else i--;
	}

	if(combo){ 
		if(combo>1){ //2콤보이상인 경우 메세지를 띄움
			drawGame();
			gameMsg((WIDTH/2)-1,block.y-2,0,combo);
			score+=(combo*level*100);
		} else { 
			if(pushAttackRegP>0){
				pushAttackRegP++;
				for(int m=1;m<WIDTH-1;m++){
					pushAttackReg[pushAttackRegP][m]=-1;
				}
			}
		}
		if(lineCnt>5&&level<10){
			level++;
			lineCnt=0;
			if(speed[level]<speed[level-1]) gameMsg((WIDTH/2)-1,5,1);
			else  gameMsg((WIDTH/2)-1,5,2);
			
			gotoxy(status_x, status_y+6);
			if(level==10) printf("Level:MAX");
			else printf("Level:%2d",level);
			gotoxy(status_x, status_y+7);
			printf("Speed:%2d",speed[level]);
		}
	}
	for(int i=1;i<WIDTH-2;i++) if(gameOrg[3][i]>0) gameOver_on=true;
}
