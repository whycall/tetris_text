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

void Tetris::dropBlock(void){
	if(fCnt>0) fCnt--;
	bool can_down=checkCrush(block.x,block.y+1,block.rotation);

	if(crush_on==true && can_down==true){
		move_block(DOWN);
		if(upRotate_on==false) fCnt=speed[level];
		crush_on=false;
	}
	if(crush_on==true && can_down==false && fCnt==0){
		if(gameDelayCnt==-1){
			drawGame();
			gameDelay(5);
		}
		else if(gameDelayCnt==0){
			for(int i=0;i<HEIGHT;i++){ 
				for(int j=0;j<WIDTH;j++){
					if(gameOrg[i][j]==ACTIVE_BLOCK) gameOrg[i][j]=INACTIVE_BLOCK;
				}
			}
			gameDelayCnt=-1;
			upRotate_on=false;
			crush_on=false;
			checkLine(); 
			getAttack();
			if(gameOver_on==false) newBlock(); 
			fCnt=speed[level]; 
		}
		return; //함수 종료 
	}
	if(crush_on==false && can_down==true && fCnt==0){
		move_block(DOWN);
		if(upRotate_on==false) fCnt=speed[level];
	}
	if(crush_on==false && can_down==false){
		crush_on=true;
		if(upRotate_on==false) fCnt=speed[0];
	}
}
bool Tetris::checkCrush(int x, int y, int rotation){
	int i,j;
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block.shape[block.type][rotation][i][j]==1&&gameOrg[y+i][x+j]>0) return false;
		}
	}	
	return true;
};
void Tetris::newBlock(void){
	int i, j;	
if(owner==COMPUTER) comCheck_on=true;
	
	block.x=(WIDTH/2)-1;
	block.y=0; 
	block.type=block.type_next;
	block.type_next=rand()%7;
	block.rotation=0; 

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j]=ACTIVE_BLOCK;
		}
	}
	
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), block.type_next+2);
	for(i=1;i<3;i++){ 
		for(j=0;j<4;j++){
			gotoxy(status_x+j,status_y+i+2);
			if(block.shape[block.type_next][0][i][j]==1) printf("■");
			else printf("  ");
		}
	}
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
}
void Tetris::drawGame(void){ 
	int i, j;	
	
	for(j=1;j<WIDTH-1;j++){ 
		if(gameOrg[3][j]==EMPTY) gameOrg[3][j]=CEILLING;
	}
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			if(gameCpy[i][j]!=gameOrg[i][j]){
				gotoxy(game_x+j,game_y+i); 
				if(gameOrg[i][j]==EMPTY) printf("  ");
				else if(gameOrg[i][j]==CEILLING){
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
					printf(". ");
				}else if(gameOrg[i][j]==WALL){
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
					printf("▩"); 
				}else if(gameOrg[i][j]<0){
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), block.getColor(gameOrg[i][j]));
					printf("▣");
				}else if(gameOrg[i][j]>0){
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), block.getColor(gameOrg[i][j]));
					printf("■");
				}	
			}
		}
	}
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);

	for(i=0;i<HEIGHT;i++){ 
		for(j=0;j<WIDTH;j++){
			gameCpy[i][j]=gameOrg[i][j];
		}
	}
}
void Tetris::gameOver(void){
	gameOverCnt++;
	if(gameOverCnt==0) gameOverP=0;
	if(gameOverP<HEIGHT-1&&gameOverCnt%5==0){
		for(int j=1;j<WIDTH-1;j++){
			if(gameOrg[gameOverP][j]>10){
				gameOrg[gameOverP][j]=17;	
			}
		}
		gameOverP++;
	}
}
void Tetris::getAttack(void){
	if(getAttackRegP<HEIGHT-1){
		int line=(HEIGHT-1)-(getAttackRegP);
		if(getAttackRegP<HEIGHT-1){
			for(int i=4;i<HEIGHT-1;i++){
				for(int j=1;j<WIDTH-1;j++){
					if(i-line>0) gameOrg[i-line][j]=gameOrg[i][j];
					gameOrg[i][j]=EMPTY;
				}
			}
		}
		for(int i=getAttackRegP+1;i<HEIGHT;i++){
			for(int j=1;j<WIDTH-1;j++){
				gameOrg[i-1][j]=getAttackReg[i][j];
				getAttackReg[i][j]=-1;
			}
		}
		getAttackRegP+=line;
		for(int i=1;i<10;i++){
			gotoxy(attackQueue_x, game_y+i);printf("  ");
		}
	}
}
void Tetris::gameMsg(int x, int y, int type, int val){
	gameMsgCnt=10;
	switch(type){
	case 0:
		gotoxy(game_x+x,game_y+y);printf("%d COMBO!",val);
		break;
	case 1:
		gotoxy(game_x+x,game_y+y);printf("SPEED UP!!");
		break;
	case 2:
		gotoxy(game_x+x,game_y+y);printf("SPEED DOWN!!");
		break;
	}
}
void Tetris::gameMsg(void){
	if(gameMsgCnt>0) gameMsgCnt--;
	else if(gameMsgCnt==0) {
		resetGameCpy();
		gameMsgCnt=-1;
	}
}
void Tetris::gameDelay(int cnt){
	gameDelay_on=true;
	gameDelayCnt=cnt;
}
void Tetris::gameDelay(void){
	if(gameDelayCnt>0) gameDelayCnt--;
	else if(gameDelayCnt==0) gameDelay_on=false;
}

class BattleTetrisManager{
public:
	BattleTetrisManager(void);
	Tetris* p1;
	Tetris* p2;
	int gameMode;
	
	void titleMenu(void);
		void keyInstructions(int menuP);

	void resetManager(void);
	
	void gamePlay(Tetris &A);
	void getKey(void);
	void pushAttack(Tetris &A, Tetris &B);
	void checkWinner(Tetris A, Tetris B);
		bool winner_on;
};

BattleTetrisManager::BattleTetrisManager(void){ 
	p1=NULL;
	p2=NULL;
}

#define PvC 0
#define PvP	1
void BattleTetrisManager::resetManager(void){ 
	system("cls");
	delete p1; //
	delete p2; //

	winner_on=false;

	GetAsyncKeyState(VK_LEFT); 
	GetAsyncKeyState(VK_RIGHT);
	GetAsyncKeyState(VK_UP);
	GetAsyncKeyState(VK_DOWN);
	GetAsyncKeyState(VK_SPACE);
	GetAsyncKeyState('L');
	GetAsyncKeyState('F');
	GetAsyncKeyState('H');
	GetAsyncKeyState('G');
	GetAsyncKeyState('T');
	GetAsyncKeyState('Q');

	switch(gameMode){
	case PvC:
		p1=new Tetris(2,1,14,2, SINGLE);  
		p2=new Tetris(27,1,22,2, COMPUTER);
		break;
	case PvP:
		p1=new Tetris(2,1,14,2, PLAYER1);  
		p2=new Tetris(27,1,22,2, PLAYER2);
		break;
	}
}
void BattleTetrisManager::gamePlay(Tetris &A){		

	if(A.gameMsgCnt>=0)	A.gameMsg();

	if(A.gameDelay_on==true) A.gameDelay();
	else{  
		if(A.gameOver_on==false) A.getKey();
		else A.gameOver();
		A.drawGame();
	}
}
void BattleTetrisManager::getKey(void){ 
	if(GetAsyncKeyState(VK_ESCAPE)){
		delete p1;
		delete p2;
		gotoxy(0,24);
		printf("Thanks for playing :)");
		exit(0);
	}
}
void BattleTetrisManager::pushAttack(Tetris &A, Tetris &B){
	if(A.pushAttackRegP<A.HEIGHT-1){
		int line=(A.HEIGHT-1)-(A.pushAttackRegP);
		for(int i=B.getAttackRegP+1;i<B.HEIGHT;i++){
			for(int j=0;j<B.WIDTH-1;j++){
				if(i-line>0) B.getAttackReg[i-line][j]=B.getAttackReg[i][j];
			}
		}
		for(int i=A.pushAttackRegP+1;i<A.HEIGHT;i++){
			for(int j=0;j<A.WIDTH-1;j++){
				B.getAttackReg[i][j]=A.pushAttackReg[i][j];
				A.pushAttackReg[i][j]=-1;
			}
		}
		B.getAttackRegP-=line;
		A.pushAttackRegP+=line;
		
		int queue=B.HEIGHT-1-B.getAttackRegP;
		int queueP=0;
		while(queue>=5){ 
			gotoxy(B.attackQueue_x, B.game_y+1+queueP);
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x000C);
			printf("★");
			queue-=5;
			queueP++;
		}
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
		while(queue>=1){ 
			gotoxy(B.attackQueue_x, B.game_y+1+queueP);
			printf("○");
			queue--;
			queueP++;
		}
		while(queueP<10){ 
			gotoxy(B.attackQueue_x, B.game_y+1+queueP);
			printf("  ");
			queueP++;
		}
	}
}
void BattleTetrisManager::checkWinner(Tetris A, Tetris B){

	if(winner_on==true){ 
		if(GetAsyncKeyState(VK_RETURN)) resetManager();
		return;
	}

	int whoWin;
	if(winner_on==false && A.gameOver_on==true){
		winner_on=true;
		whoWin=B.owner;
	} else if (winner_on==false && B.gameOver_on==true){
		winner_on=true;
		whoWin=A.owner;
	} else return;
	
	gotoxy(15, 10);
	switch(whoWin){
	case SINGLE:
		printf(" <<   YOU WIN!   >>");
		break;
	case PLAYER1:
		printf(" << PLAYER 1 WIN >>");
		break;
	case PLAYER2:
		printf(" << PLAYER 2 WIN >>");
		break;
	case COMPUTER:
		printf(" << COMPUTER WIN >>");
		break;
	}
	gotoxy(14, 12);
		printf("Press <ENTER> to restart");
}
void BattleTetrisManager::keyInstructions(int menuP){
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
	switch(menuP){
	case PvP:
		gotoxy(21,15); printf("┌──<  Key Instructions  >──┐");		
		gotoxy(21,16); printf("│ PLAYER 1            PLAYER 2 │");
		gotoxy(21,17); printf("│    T       ROTATE      ↑    │"); 
		gotoxy(21,18); printf("│    H        RIGHT      →    │"); 
		gotoxy(21,19); printf("│    F        LEFT       ←    │"); 
		gotoxy(21,20); printf("│    G      SOFT DROP    ↓    │"); 
		gotoxy(21,21); printf("│    Q      HARD DROP     L    │"); 
		gotoxy(21,22); printf("└───────────────┘"); 
		break;
	case PvC:
		gotoxy(21,15); printf("┌──<  Key Instructions  >──┐");		
		gotoxy(21,16); printf("│                   PLAYER     │");
		gotoxy(21,17); printf("│     ROTATE          ↑       │"); 
		gotoxy(21,18); printf("│      RIGHT          →       │"); 
		gotoxy(21,19); printf("│      LEFT           ←       │"); 
		gotoxy(21,20); printf("│    SOFT DROP        ↓       │"); 
		gotoxy(21,21); printf("│    HARD DROP      SPACE      │"); 
		gotoxy(21,22); printf("└───────────────┘"); 

	}
}
void BattleTetrisManager::titleMenu(void){ // 게임타이틀
	int i,j;

	int text_battle_x=3;
	int text_battle_y=2;
	
	int text_tetris_x=16;
	int text_tetris_y=9;
	
	int text_menu_x=4;
	int text_menu_y=17;

	int menuP=PvC;
	int totalMenu=2;
	int menuCnt=0;

	int text_battle_order[9]={0,1,2,3,4,2,1,4,2};
	int text_battle [5][6][25]={
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,

		1,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,0,
		1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,
		1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,0,0,
		1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,
		1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,
		0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,
		0,1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,0,
		0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,
		0,1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,0,
		1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,
		1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,0,0,
		1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,
		1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,0,

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,
		0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,
		0,0,1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,
		0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,
		0,0,1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1
	};

	int text_tetris [5][21]={
		1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,1,0,1,1,1,
		0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,0,
		0,1,0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,0,1,1,1,
		0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1,
		0,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1
	};
	
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0003);
	for(int k=1;k<9;k++){
		for(i=0;i<6;i++){
			for(j=0;j<25;j++){
				if(text_battle[text_battle_order[k]][i][j]!=text_battle[text_battle_order[k-1]][i][j]){
					gotoxy(text_battle_x+j,text_battle_y+i); 
					if(text_battle[text_battle_order[k]][i][j]==1) printf("■");
					else if(text_battle[text_battle_order[k]][i][j]==0) printf("  ");
				}
			}
		}
		Sleep(100);
	}
	Sleep(200);

	
	
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x000F);
	gotoxy(text_menu_x,text_menu_y); printf("    1. PLAYER VS COMPUTER");
	gotoxy(text_menu_x,text_menu_y+2); printf("    2. PLAYER 1 VS PLAYER 2");
	
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
	gotoxy(33,7); printf("ver. 1.0");

	
	keyInstructions(menuP);
	gotoxy(21,23); printf("			 BW,JW		");

	for(int cnt=0;;cnt++){
		if(menuCnt>0) menuCnt--;
		Sleep(10);

		if((cnt+0)%60==0){
			switch(menuP){
			case PvC:
				gotoxy(text_menu_x,text_menu_y); 
				break;
			case PvP:
				gotoxy(text_menu_x,text_menu_y+2); 
				break;
			}
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x000F);
			printf(" →");
		}
		if((cnt+30)%60==0){
			switch(menuP){
			case PvC:
				gotoxy(text_menu_x,text_menu_y); 
				break;
			case PvP:
				gotoxy(text_menu_x,text_menu_y+2); 
				break;
			}
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x000F);
			printf("→ ");
		}
		if(cnt%75==0){	
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), cnt%7+2);
			for(i=0;i<5;i++){
				for(j=0;j<21;j++){
					gotoxy(text_tetris_x+j,text_tetris_y+i);
					if(text_tetris[i][j]==1) printf("▣");
				}
			}
		}
		if(GetAsyncKeyState(VK_UP)&&menuCnt==0){
			menuCnt=20;
			gotoxy(text_menu_x,text_menu_y); printf("   ");
			gotoxy(text_menu_x,text_menu_y+2); printf("   ");
			menuP=(menuP+1)%totalMenu;
			keyInstructions(menuP);
		}
		if(GetAsyncKeyState(VK_DOWN)&&menuCnt==0){
			menuCnt=20;
			gotoxy(text_menu_x,text_menu_y); printf("   ");
			gotoxy(text_menu_x,text_menu_y+2); printf("   ");
			menuP=(menuP+totalMenu-1)%totalMenu;
			keyInstructions(menuP);
		}
		if(GetAsyncKeyState(VK_RETURN)){
			gameMode=menuP;
			break;
		}
		if(GetAsyncKeyState('1')){
			gameMode=PvC;
			break;
		}
		if(GetAsyncKeyState('2')){
			gameMode=PvP;
			break;
		}
	}
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
}

int main(){
	srand((unsigned)time(NULL)); //난수표생성 
	setcursortype(NOCURSOR); //커서 없앰 
	
	BattleTetrisManager GM; //게임메니져생성
	GM.titleMenu(); //게임타이틀
	GM.resetManager(); // 게임메니져 리셋
	
	Tetris &player1=*GM.p1;
	Tetris &player2=*GM.p2;
	
	while(1){
		Sleep(20);
		GM.getKey();
		GM.gamePlay(player1);	
		GM.gamePlay(player2);
		GM.pushAttack(player1, player2);
		GM.pushAttack(player2, player1);
		GM.checkWinner(player1, player2);
	}
}//끝! 
