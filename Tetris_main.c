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
#include "Tetris_GameStart.h"
#include "Tetris_Result.h"
#include "Tetris_Search.h"
#include <ncursesw/curses.h>
#include <locale.h>

int game = GAME_END; /*게임 상태 변수, 게임이 시작되거나 종료됨에 따라 변한다*/

int display_menu(void); /* 메뉴를 보여줌 */

int main(void)
{
	int menu = 1;

	while(1)
	{
		menu = display_menu();

		if(menu == 1)
		{
			game = GAME_START;
			game_start();
		}
		else if(menu == 2)
		{
			search_result();
		}
		else if(menu == 3)
		{
			print_result();
		}
		else if(menu == 4)
		{
			system("clear");
			exit(0);
		}
	}

	return 0;
}

/* 메뉴를 보여줌 */
int display_menu(void)
{
	int menu = 0;

	while(1)
	{
		initscr();
		clear();
		printw("\n\n\t\t\t■ □ □ □ ■ ■ ■ □ □ ■ ■ □ ■ ■ "); 
		printw("\n\t\t\t■ ■ ■ □ □ ■ □ □ □ ■ ■ □ □ ■ "); //sleep(1);refresh();
		printw("\n\t\t\t□ □ □ ■ □ □ □ □ □ □ □ ■ □ ■ ");
		printw("\n\t\t\t■ ■ □ ■ ■ □ □ ■ □ □ □ ■ □ □ "); 
		printw("\n\t\t\t■ ■ □ ■ □ □ □ ■ ■ ■ □ ■ ■ □ ");//sleep(1);refresh();
		printw("\n\t\t\t\tT E T R I S"); 
		printw("\n\t\t\tPlease Enter Any Key to Start..");
		printw("\n\t\t\t  △   : Shift");
		printw("\n\t\t\t◁   ▷ : Left / Right");
		printw("\n\t\t\t  ▽   : Soft Drop");
		printw("\n\t\t\tspace bar : Hard Drop");
		printw("\n\n\t\t\t1) 게임 시작");
		printw("\n\t\t\t2) 기록 검색");
		printw("\n\t\t\t3) 기록 출력");
		printw("\n\t\t\t4) 종료");
		printw("\n\n\t\t\t\t\t 선택 : ");

		scanw("%d",&menu);
		if(menu < 1 || menu > 4)
		{
			endwin();
			continue;
		}
		else
		{
			endwin();
			return menu;
		}
	}
	return 0;
}


