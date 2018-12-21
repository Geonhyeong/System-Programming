#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
#include "Tetris_GameStart2P.h"
#include<locale.h>
#include<ncursesw/curses.h>

char tetris_table1[21][10];
char tetris_table2[21][10];

extern char i_block;
extern char t_block;
extern char s_block;
extern char z_block;
extern char j_block;
extern char o_block;
extern char l_block;


int block_number1 = 0;  /*현재 블록 넘버 변수*/
int next_block_number1 = 0; /*다음 블록 넘버 변수 */
int block_state1 = 0; /*블록 상태, 회전함에 따라 변한다*/
int x1 = 3, y_1 = 0; /*블록이 현재 테트리스판 어디에 위치해 있는지 알려주는 변수*/
long point1 = 0; /* 현재 게임중 득점을 알려주는 변수 */

int block_number2 = 0;  /*현재 블록 넘버 변수*/
int next_block_number2 = 0; /*다음 블록 넘버 변수 */
int block_state2 = 0; /*블록 상태, 회전함에 따라 변한다*/
int x2 = 3, y2 = 0; /*블록이 현재 테트리스판 어디에 위치해 있는지 알려주는 변수*/
long point2 = 0; /* 현재 게임중 득점을 알려주는 변수 */

/* 게임 시작시 호출되는 함수.   game변수를 참조하여 게임을 종료하거나 시작함 . 게임 시작시 refresh()함수가 콜백함수로 설정되고 타이머를 등록함. */
int game_start_2p(void)
{
	int _refresh_2p(int);
	setlocale(LC_CTYPE, "ko_KR.utf-8");
	if(game == GAME_START)
	{
		initscr();
		clear();
		init_tetris_table_2p();

		signal(SIGVTALRM,_refresh_2p);
		if(set_ticker(game)==-1)
			perror("set_ticker");

		while(1)
		{
			if(game == GAME_END)
			{
				game_end_2p();
				endwin();
				return 1;
			}
		}
	}

  return 0;
}

/*테트리스판을 초기화 한다. 벽과 공간을 나눔*/
int init_tetris_table_2p(void)
{
	int i,j;

	for(i = 0 ; i < 21 ; i++){
		for(j = 0 ; j < 10 ; j++){
			if(j==0 || j==9||i==20){
				tetris_table1[i][j] = 1;
				tetris_table2[i][j] = 1;
			}
			else{
				tetris_table1[i][j] = 0;
				tetris_table2[i][j] = 0;
			}
		}
	}
	return 0;
}







/* 타이머에 콜백함수로 등록되어 계속 새로고침 하면서 호출되는 함수. 키입력 확인,  화면새로고침, 한줄완성검사등의 계속 상태가 변함을 확인해야 되는 함수를 호출한다 */
int _refresh_2p(int signum)
{
	static int downcount1 = 0;
	static int setcount1 = 0;
	static long speedcount1 = 0;
	static int speed1 = 5;
	static int firststart1 = 0;

	static int downcount2 = 0;
	static int setcount2 = 0;
	static long speedcount2 = 0;
	static int speed2 = 5;
	static int firststart2 = 0;

	char ch;

	srand((unsigned)time(NULL));
	
	display_tetris_table_2p(speed1,speed2);
	refresh();

	ch = _getch();
	if(game==GAME_START || game==GAME_PLAYER2_END){
		if(firststart1 == 0)
		{
			block_number1= rand()%7;
			firststart1++;
		}
		if(downcount1 == speed1-1)
		{
			point1 += 1;
			move_block_2p(DOWN,&x1,&y_1,&block_state1,&block_number1,tetris_table1);
		}

		if(speedcount1 == 499)
		{
			if(speed1 != 1)
				speed1--;
		}

		downcount1++;
		downcount1 %= speed1;
		speedcount1++;
		speedcount1 %= 500;

		if(x1 == 3 && y_1 == 0)
		{
			if(collision_test_2p(LEFT,&x1,&y_1,&block_state1,&block_number1,tetris_table1) || collision_test_2p(RIGHT,&x1,&y_1,&block_state1,&block_number1,tetris_table1) || collision_test_2p(DOWN,&x1,&y_1,&block_state1,&block_number1,tetris_table1) || collision_test_2p(ROTATE,&x1,&y_1,&block_state1,&block_number1,tetris_table1))
			{
				if(game==GAME_PLAYER2_END) game = GAME_END;
				else game = GAME_PLAYER1_END;
				downcount1 = 0;
				setcount1 = 0;
				speedcount1 = 0;
				speed1 = 5;
				firststart1 = 0;
			
			}
		}
		if(collision_test_2p(DOWN,&x1,&y_1,&block_state1,&block_number1,tetris_table1))
		{
			if(setcount1 == 9)
			{
				check_one_line_2p(tetris_table1,&point1);
				block_number1= next_block_number1;
				next_block_number1 = rand()%7;
				block_state1 = 0;
				x1 = 3;
				y_1 = 0;
			}
			setcount1++;
			setcount1 %= 10;
		}

		switch(ch)
		{
			case 'a' :	move_block_2p(LEFT,&x1,&y_1,&block_state1,&block_number1,tetris_table1);
						  		break;
			case 'd' :	move_block_2p(RIGHT,&x1,&y_1,&block_state1,&block_number1,tetris_table1);
							  	break;
			case 's' :	move_block_2p(DOWN,&x1,&y_1,&block_state1,&block_number1,tetris_table1);
									break;
			case 'w' :	move_block_2p(ROTATE,&x1,&y_1,&block_state1,&block_number1,tetris_table1);
									break;
			case ' '  :	drop_2p(&x1,&y_1,&block_state1,&block_number1,tetris_table1);
									break;
	 		case 'q' :	downcount1 = 0;
	 								setcount1 = 0;
	 								speedcount1 = 0;
	 								speed1 = 5;
	 								firststart1 = 0;
									downcount2 = 0;
	 								setcount2 = 0;
	 								speedcount2 = 0;
	 								speed2 = 5;
	 								firststart2 = 0;
	 								game = GAME_END;
	 								break;
	 		default : 	break;
		}
	}
	if(game==GAME_START || game==GAME_PLAYER1_END){
		if(firststart2 == 0)
		{
			block_number2= rand()%7;
			firststart2++;
		}

	//	printw("\n Score : %ld | Speed : %d | Best Score : %d", point, speed, best_point);
	//	refresh();	

	
	//	check_one_line();

	

	
		if(downcount2 == speed2-1)
		{
			point2 += 1;
			move_block_2p(DOWN,&x2,&y2,&block_state2,&block_number2,tetris_table2);
		}

		if(speedcount2 == 499)
		{
			if(speed2 != 1)
				speed2--;
		}

		downcount2++;
		downcount2 %= speed2;
		speedcount2++;
		speedcount2 %= 500;

		if(x2 == 3 && y2 == 0)
		{
			if(collision_test_2p(LEFT,&x2,&y2,&block_state2,&block_number2,tetris_table2) || collision_test_2p(RIGHT,&x2,&y2,&block_state2,&block_number2,tetris_table2) || collision_test_2p(DOWN,&x2,&y2,&block_state2,&block_number2,tetris_table2) || collision_test_2p(ROTATE,&x2,&y2,&block_state2,&block_number2,tetris_table2))
			{
				if(game==GAME_PLAYER1_END) game = GAME_END;
				else game = GAME_PLAYER2_END;
				downcount2 = 0;
				setcount2 = 0;
				speedcount2 = 0;
				speed2 = 5;
				firststart2 = 0;
			}
		}

	
	
		if(collision_test_2p(DOWN,&x2,&y2,&block_state2,&block_number2,tetris_table2))
		{
			if(setcount2 == 9)
			{
				check_one_line_2p(tetris_table2,&point2);
				block_number2= next_block_number2;
				next_block_number2 = rand()%7;
				block_state2 = 0;
				x2 = 3;
				y2 = 0;
			}
			setcount2++;
			setcount2 %= 10;
		}
		switch(ch)
		{
			case 'j' :	move_block_2p(LEFT,&x2,&y2,&block_state2,&block_number2,tetris_table2);
						  		break;
			case 'l' :	move_block_2p(RIGHT,&x2,&y2,&block_state2,&block_number2,tetris_table2);
							  	break;
			case 'k' :	move_block_2p(DOWN,&x2,&y2,&block_state2,&block_number2,tetris_table2);
									break;
			case 'i' :	move_block_2p(ROTATE,&x2,&y2,&block_state2,&block_number2,tetris_table2);
									break;
			case ']'  :	drop_2p(&x2,&y2,&block_state2,&block_number2,tetris_table2);
									break;
	 		case 'q' :	downcount1 = 0;
	 								setcount1 = 0;
	 								speedcount1 = 0;
	 								speed1 = 5;
	 								firststart1 = 0;
									downcount2 = 0;
	 								setcount2 = 0;
	 								speedcount2 = 0;
	 								speed2 = 5;
	 								firststart2 = 0;
	 								game = GAME_END;
	 								break;
	 		default : 	break;
		}
	}

	

	
	return 0;
}

/* 현재의 테트리스판을 보여준다. 블록이 놓이고 쌓인 현재 상태를 보여줌*/
int display_tetris_table_2p(int speed1,int speed2)
{
	int i, j;
	char (*block_pointer1)[4][4][4] = NULL;
	char (*block_pointer2)[4][4][4] = NULL;

	switch(next_block_number1)
	{
		case I_BLOCK :	block_pointer1 = &i_block; break;
		case T_BLOCK :	block_pointer1 = &t_block; break;
		case S_BLOCK :  block_pointer1 = &s_block; break;
		case Z_BLOCK : 	block_pointer1 = &z_block; break;
		case L_BLOCK : 	block_pointer1 = &l_block; break;
		case J_BLOCK : 	block_pointer1 = &j_block; break;
		case O_BLOCK :	block_pointer1 = &o_block; break;
	}

	switch(next_block_number2)
	{
		case I_BLOCK :	block_pointer2 = &i_block; break;
		case T_BLOCK :	block_pointer2 = &t_block; break;
		case S_BLOCK :  block_pointer2 = &s_block; break;
		case Z_BLOCK : 	block_pointer2 = &z_block; break;
		case L_BLOCK : 	block_pointer2 = &l_block; break;
		case J_BLOCK : 	block_pointer2 = &j_block; break;
		case O_BLOCK :	block_pointer2 = &o_block; break;
	}


//	system("clear");
	clear();

	move(1,23);
	printw("< Player1 >");
	move(2,23);
	printw("Next Block");


	for(i = 0 ; i < 4 ; i++)
	{
		move(i+3,23);
		for(j = 0 ; j < 4 ; j++)
		{
			if((*block_pointer1)[0][i][j] == 1)
				//addstr("▣ ");
				printw("▣ ");
			else if((*block_pointer1)[0][i][j] == 0)
				printw("  ");
		}
	}
	move(7,23);
	printw("Score : %ld",point1);
	
	move(8,23);
	printw("Speed : %d", speed1);

	if(game==GAME_PLAYER1_END){
		move(10,23);
		printw("Player1 Game End!");
	}

	for(i = 2 ; i < 21 ; i++)
	{
		move(i-1,1);
		for(j = 0 ; j < 10 ; j++)
		{
			if(j == 0 || j == 9|| (i == 20 && (j > 1 || j < 9)))
			{
				printw("■ ");
			}
			else if(tetris_table1[i][j] == 1)
				//addstr("▣ ");
				printw("▣ ");
			else if(tetris_table1[i][j] == 0)
				printw("  ");
		}
	}

	move(1,38);
	printw("< Player2 >");
	move(2,38);
	printw("Next Block");

	for(i = 0 ; i < 4 ; i++)
	{
		move(i+3,38);
		for(j = 0 ; j < 4 ; j++)
		{
			if((*block_pointer2)[0][i][j] == 1)
				//addstr("▣ ");
				printw("▣ ");
			else if((*block_pointer2)[0][i][j] == 0)
				printw("  ");
		}
	}
	move(7,38);
	printw("Score : %ld",point2);
	
	move(8,38);
	printw("Speed : %d", speed2);
	
	if(game==GAME_PLAYER2_END){
		move(11,23);
		printw("Player2 Game End!");
	}

	for(i = 2 ; i < 21 ; i++)
	{
		move(i-1,50);
		for(j = 0 ; j < 10 ; j++)
		{
			if(j == 0 || j == 9|| (i == 20 && (j > 1 || j < 9)))
			{
				//addstr("■ ");
				printw("■ ");
			}
			else if(tetris_table2[i][j] == 1)
				//addstr("▣ ");
				printw("▣ ");
			else if(tetris_table2[i][j] == 0)
				printw("  ");
		}
	}
	refresh();	

	return 0;
}

/*이동, 회전키가 입력되면, 충돌검사후 이동시킨다*/
int move_block_2p(int command,int *x,int *y,int *block_state,int *block_number,char tetris_table[21][10])
{
	int i, j;
	int newx, newy;
	int oldx, oldy;
	int old_block_state;
	char (*block_pointer)[4][4][4] = NULL;

	newx = (*x);
	newy = (*y);

	old_block_state = (*block_state);

	if(collision_test_2p(command,x,y,block_state,block_number,tetris_table) == 0)
	{
		switch(command)
		{
			case	LEFT :	newx--;
										break;
			case	RIGHT :	newx++;
										break;
			case	DOWN :	newy++;
										break;
			case ROTATE :	(*block_state)++;
										(*block_state) %= 4;
										break;
		}
	}
	else
	{
		return 1;
	}

	switch(*block_number)
	{
		case I_BLOCK :	block_pointer = &i_block;
								  	break;
		case T_BLOCK :	block_pointer = &t_block;
										break;
		case S_BLOCK :  block_pointer = &s_block;
										break;
		case Z_BLOCK : 	block_pointer = &z_block;
										break;
		case L_BLOCK : 	block_pointer = &l_block;
										break;
		case J_BLOCK : 	block_pointer = &j_block;
										break;
		case O_BLOCK :	block_pointer = &o_block;
										break;
	}

	for(i = 0, oldy = (*y) ; i < 4 ; i++, oldy++)
	{
		for(j = 0, oldx = (*x) ; j < 4 ; j++, oldx++)
		{
			if(oldx > 0 && oldx < 9 && oldy < 20 && oldy > 0)
				if((*block_pointer)[old_block_state][i][j] == 1)
						tetris_table[oldy][oldx] = 0;

		}
	}

	(*x) = newx;
	(*y) = newy;

	for(i = 0, newy = (*y) ; i < 4 ; i++, newy++)
	{
		for(j = 0, newx = (*x) ; j < 4 ; j++, newx++)
		{
			if(newx > 0 && newx < 9 && newy < 20 && newy > 0)
				if((*block_pointer)[*block_state][i][j] == 1)
					tetris_table[newy][newx] = (*block_pointer)[*block_state][i][j];
		}
	}

	return 0;
}

/* 블록이 이동, 회전하기 전에 충돌되는 블록이나 벽이 없는지 확인하는 함수*/
int collision_test_2p(int command,int *x,int *y,int *block_state,int *block_number,char tetris_table[21][10])
{
	int i, j;
	int tempx, tempy;
	int oldx, oldy;
	int temp_block_state;
	char (*block_pointer)[4][4][4];
	char temp_tetris_table[21][10];

	oldx = tempx = (*x);
	oldy = tempy = (*y);
	temp_block_state = (*block_state);

	switch(command)
	{
		case	LEFT :	tempx--; break;
		case	RIGHT :	tempx++; break;
		case	DOWN :	tempy++; break;
		case	ROTATE :
				temp_block_state++; temp_block_state %=  4; break;
	}

	switch(*block_number)
	{
		case I_BLOCK :	block_pointer = &i_block; break;
		case T_BLOCK :	block_pointer = &t_block; break;
		case S_BLOCK :  block_pointer = &s_block; break;
		case Z_BLOCK : 	block_pointer = &z_block; break;
		case L_BLOCK : 	block_pointer = &l_block; break;
		case J_BLOCK : 	block_pointer = &j_block; break;
		case O_BLOCK :	block_pointer = &o_block; break;
	}

	for(i = 0 ; i < 21 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			temp_tetris_table[i][j] = tetris_table[i][j]; //테이블 복사
		}
	}

	for(i = 0, oldy = (*y) ; i < 4 ; i++, oldy++)
	{
		for(j = 0, oldx = (*x) ; j < 4 ; j++, oldx++)
		{
			if(oldx > 0 && oldx < 9 && oldy < 20 && oldy > 0)
			{
				if((*block_pointer)[*block_state][i][j] == 1)
						temp_tetris_table[oldy][oldx] = 0;
			}
		}
	}

	for(i = 0 ; i < 4 ; i++)
	{
		for(j = 0 ; j < 4 ; j++)
		{

			if(temp_tetris_table[tempy+i][tempx+j] == 1 && (*block_pointer)[temp_block_state][i][j] == 1)
					return 1;
		}
	}

	return 0;
}

/* 충돌되기 전까지 블록을 다운시킨다.*/
int drop_2p(int *x,int *y,int *block_state,int *block_number,char tetris_table[21][10])
{
	while(!collision_test_2p(DOWN,x,y,block_state,block_number,tetris_table))
		move_block_2p(DOWN,x,y,block_state,block_number,tetris_table);

	return 0;
}

/* 한줄이 완성되었는지 확인하는 함수. 완성되면 한줄을 지우고, 점수에 1000점을 더한다*/
int check_one_line_2p(char tetris_table[21][10],long *point)
{
	int i, j;
	int ni, nj;
	int line_hole;

	for(i = 19 ; i > 0 ; i--)
	{
		line_hole = 0;
		for(j = 1 ; j < 9 ; j++)
		{
			if(tetris_table[i][j] == 0)
			{
				line_hole = 1;
			}
		}

		if(line_hole == 0)
		{
			(*point) += 100;
			for(ni = i ; ni > 0 ; ni--)
			{
				for(nj = 1 ; nj < 9 ; nj++)
				{
					tetris_table[ni][nj] = tetris_table[ni-1][nj];
				}
			}
		}
	}

	return 0;
}


void game_end_2p(){
	if(set_ticker(game)==-1)
		perror("set_ticker");

	x1 = 3, y_1 =0;
	point1 = 0;

	x2 = 3, y2 =0;
	point2 = 0;
	move(10,23);
	printw("Player1 Game End!");
	move(11,23);
	printw("Player2 Game End!");

	while(1){
		move(13,22);
		printw("Press Any key to go to menu..");
		refresh();
		getch();
		break;
	}
}
