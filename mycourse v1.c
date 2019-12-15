#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char pl1[15],pl2[15];
  
void printBoard(int *board);
int welcome();
void turnPl1(int *board);
void turnPl2(int *board);
int ToDoTurn(int *board,int plac);
void isEmpty(int *board,int plac,int player);
int checkToWin();
void turnComp(int *board);
void EndTheGame(int win, int *board);
int findToTurn(int *board);

int main()
{
	int board[14]={4,4,4,4,4,4,0,4,4,4,4,4,4,0};
	int comp = 1;
	int check;
	int turn = 1;
	comp = welcome();
	printBoard(board);
	
	while(1){
		
		if(turn == 1){
			turnPl1(board);
			check = checkToWin(board);
			if(check) break;
		}
		
		else {
			if (comp == 0) {
			turnPl2(board);
			}
		    if( comp == 1){
			turnComp(board);
			}
			check = checkToWin(board);
			if(check) break;
			}
		if(turn == 1) turn = 2;
		else turn = 1;
	}
	
	EndTheGame(check,board);
	
	return 0;
}

void turnComp(int *board){
	srand(time(0));
	int place;
	int move;
	while(1){
	move = findToTurn(board);
	if(move > 0)ToDoTurn(board,move);
	else break;
	}
	while(1){
	place = rand()%6+7;
	if(board[place] != 0) break;
	}
	ToDoTurn(board,place);
	printBoard(board);
}

int checkToWin(int *board){
	if( ( board[0] == 0 ) && ( board[1] == 0 ) && ( board[2]== 0 ) && ( board[3] == 0 ) && ( board[4] == 0) && ( board[5] == 0)) {
		board[13] += (board[7] + board[8] + board[9] + board[10] + board[11] + board[12]);
		board[7] = board[8] = board[9] = board[10] = board[11] = board[12] = 0;
		if(board[6] > board[13]) return 1;
		if(board[13] > board[6]) return 2;
		if(board[6] == board[13]) return 3;
	}
	else 
		if( ( board[7] == 0 ) && ( board[8] == 0 ) && ( board[9]== 0 ) && ( board[10] == 0 ) && ( board[11] == 0) && ( board[12] == 0)) {
		board[6] += (board[0] + board[1] + board[2] + board[3] + board[4] + board[5]);
		board[0] = board[1] = board[2] = board[3] = board[4] = board[5] = 0;
		if(board[6] > board[13]) return 1;
		if(board[6] < board[13]) return 2;
		if(board[6] == board[13]) return 3;
	}
	if(board[6] > 24) return 1;
	if(board[13] > 24) return 2;
	//if(board[6] == board[13]) return 3;
	
	return 0; 
}

void turnPl2(int *board){
	int place;
	int repeat = 0;
	do{
		printf("player(%s) Chioce place 1-6\n",pl2);
		do{
			scanf("%i",&place);
			if(board[place+6]==0) {
				printf("board is empty");
				place=0;
			}
		}while(place<1 || place>6);
		place+=6;
		repeat = ToDoTurn(board,place);
		printBoard(board);
		
	}while(repeat == 1);
}
void turnPl1(int *board){
	int place;
	int repeat = 0;
	do{
		printf("player(%s ) Chioce place 1-6\n",pl1);
		do{
			scanf("%i",&place);
			if(board[place-1]==0) {
				printf("board is empty");
				place=0;
			}
		}while(place<1 || place>6);
		place--;
		repeat = ToDoTurn(board,place);
		printBoard(board);
	}while(repeat == 1);
	
}

int ToDoTurn(int *board,int plac){
	int stone = board[plac];
	int player;
	if(plac <= 6) player = 1;
	if(plac > 6) player = 2;
	board[plac] = 0;
	plac++;
	while(stone){
		if(plac == 6 && player == 1) {
		board[6]++;
		plac++;
		stone--;
		if(stone == 0) return 1;
		}
		if(plac == 13 && player == 2) {
		board[13]++;
		stone--;
		}
		if(plac == 13 && stone == 0 && player == 2 ){
		return 1;
		}
		if(plac == 6 && player == 2) {
			plac++;
		}
		if(plac == 13) plac = 0;
		
		board[plac++]++;
		stone--;
	}
	if(((plac>=1 && plac<=6) && player == 1 )
	    || ((plac >= 8 && plac <= 13) && player == 2 ))
			isEmpty(board,plac-1,player);
	
	if(plac == 14) plac = 13;
	else plac--;
	if((plac == 6 && player == 1) || (plac == 13 && player == 2)) return 1;
	else return 0;
	
}

void isEmpty(int *board,int plac,int player){
	int b;
	if(plac == 13) plac = 0;
	if(player == 1){
		if(plac >=0 && plac<=5)
			if((board[plac]==1) && (board[12-plac] != 0)){
				b = board[12-plac];
				board[12-plac] = 0;
				board[plac] = 0;
				board[6] += (b+1);
				return;
			}
	}
	
	if(player == 2){
		if(plac >=7 && plac<=12)
			if((board[plac]==1) && (board[12-plac] != 0)){
				b = board[12-plac];
				board[12-plac] = 0;
				board[plac] = 0;
				board[13] += (b+1);
				return;
			}
	}
}	

void printBoard(int *board){
	 system("clear");
    printf(            "\t    =================================================================================|\n"
                       "\t    |          |     6    |      5  |     4   |   3     |   2     |    1    |        |\n"
                       "\t    =================================================================================|\n"
                       "\t    |          |          |         |         |         |         |         |        |\n"
                       "\t    |          |%-3d       |%-3d      |%-3d      |%-3d      |%-3d      |%-3d      |        |\n"
                       "\t    |          |          |         |         |         |         |         |        |\n"
                       "\t    |  %-3d     |==========|=========|=========|=========|=========|=========| %-3d    |\n"
                       "\t    |          |          |         |         |         |         |         |        |\n"
                       "\t    |          |%-3d       |%-3d      |%-3d      |%-3d      |%-3d      |%-3d      |        |\n"
                       "\t    |          |          |         |         |         |         |         |        |\n"
                       "\t    =================================================================================|\n"
                       "\t    |          |   1      |   2     |   3     |   4     |   5     |   6     |        |\n"
                       "\t    =================================================================================|\n",

                       board[12],board[11],board[10],board[9],board[8],board[7],
                       board[13],board[6],board[0],board[1],board[2],board[3],board[4],board[5]); 

}


int welcome(){
	char c;
	int comp;
	do{
	printf("Hello it is game 'Kalah'\nWould you play? (y/n)");
	c = getchar();
	}while(c != 'y' && c != 'n');
	
	if(c == 'n'){
		printf("\nGood bye\n");
		exit (0);
	}
	
	do{
		printf("press:1 to play with computer \npress:0 to with someone\n");
		scanf("%i",&comp);
	}while(comp!= 1 && comp != 0);
	printf("\nname player one? ");
	scanf("%s",pl1);
	if(comp == 0){
	printf("\nname player two? ");
	scanf("%s",pl2);
	}
	else {
		strcpy(pl2,"Computer");
		}
	printf("\nHAVE FUN\n");
	getchar();
	return comp;
	
}

void EndTheGame(int win,int *board) {
	printBoard(board);
	if(win == 1){
		printf("%s is WINNER",pl1);
	}
	if(win == 2){
		printf("%s is WINNER",pl2);
	}
	if(win == 3) {
		printf("\n\n\n|D|R|A|W|");
	}
	
}

int findToTurn(int *board)
{
	int virtDesk[14];

	int move = 0,rep,j;
	for(move = 12;move > 6;move--){
		for(j = 0; j < 14; j++) virtDesk[j] = board[j];
		if(virtDesk[move] > 0){
			rep = ToDoTurn(virtDesk,move);
			if(rep == 1) return move;
		}
	}
	return 0;
}

