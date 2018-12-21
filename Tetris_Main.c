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
#include<locale.h>
#include<ncursesw/curses.h>
#include "Tetris_GameStart2P.h"
#include "Tetris_GameStart.h"
#include "Tetris_Result.h"
#include "Tetris_Search.h"

int game = GAME_END; /*게임 상태 변수, 게임이 시작되거나 종료됨에 따라 변한다*/
char i_block[4][4][4] =
	{
			{0, 0, 0, 0,
			 0, 0, 0, 0,
			 1, 1, 1, 1,
			 0, 0, 0, 0},

			{0, 0, 1, 0,
			 0, 0, 1, 0,
			 0, 0, 1, 0,
			 0, 0, 1, 0},

			{0, 0, 0, 0,
			 0, 0, 0, 0,
			 1, 1, 1, 1,   
			 0, 0, 0, 0},

			{0, 0, 1, 0,
			 0, 0, 1, 0,
			 0, 0, 1, 0,
			 0, 0, 1, 0}
	};

char t_block[4][4][4] =

	{
			{0, 1, 0, 0,
			 0, 1, 1, 0,
			 0, 1, 0, 0,
			 0, 0, 0, 0},

			{0, 0, 0, 0,
			 1, 1, 1, 0,
			 0, 1, 0, 0,
			 0, 0, 0, 0},

			{0, 1, 0, 0,
			 1, 1, 0, 0,
			 0, 1, 0, 0,
			 0, 0, 0, 0},

			{0, 1, 0, 0,
			 1, 1, 1, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0}
	};

char s_block[4][4][4] =
	{
			{1, 0, 0, 0,
			 1, 1, 0, 0,
			 0, 1, 0, 0,
			 0, 0, 0, 0},

			{0, 1, 1, 0,
			 1, 1, 0, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0},

			{0, 1, 0, 0,
			 0, 1, 1, 0,
			 0, 0, 1, 0,
			 0, 0, 0, 0},

			{0, 0, 0, 0,
			 0, 1, 1, 0,
			 1, 1, 0, 0,
			 0, 0, 0, 0}
	};

char z_block[4][4][4] =
	{
			{0, 1, 0, 0,
			 1, 1, 0, 0,
			 1, 0, 0, 0,
			 0, 0,0, 0},

			{1, 1, 0, 0,
			 0, 1, 1, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0},

			{0, 0, 1, 0,
			 0, 1, 1, 0,
			 0, 1, 0, 0,
			 0, 0, 0, 0},

			{0, 0, 0, 0,
			 1, 1, 0, 0,
			 0, 1, 1, 0,
			 0, 0, 0, 0}
	};

char l_block[4][4][4] =
	{
			{0,1, 0, 0, 
			 0,1, 0, 0, 
			 0,1, 1, 0, 
			 0,0, 0, 0},

			{0, 0, 0, 0,
			 1, 1, 1, 0,
			 1, 0, 0, 0,
			 0, 0, 0, 0},

			{1, 1, 0,0,
			 0, 1, 0,0,
			 0, 1, 0,0,
			 0, 0, 0,0},

			{0, 0, 1, 0,
			 1, 1, 1, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0}
	};

char j_block[4][4][4] =
	{
			{0, 1, 0, 0,
			 0, 1, 0, 0,
			 1, 1, 0, 0,
			 0, 0, 0, 0},

			{1, 0, 0, 0,
			 1, 1, 1, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0},

			{0,1, 1, 0, 
			 0,1, 0, 0, 
			 0,1, 0, 0, 
			 0,0, 0, 0},

			{0, 0, 0, 0,
			 1, 1, 1, 0,
			 0, 0, 1, 0,
			 0, 0, 0, 0}
	};

char o_block[4][4][4] =
	{
			{1, 1, 0, 0,
			 1, 1, 0, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0},

			{1, 1, 0, 0,
			 1, 1, 0, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0},

			{1, 1, 0, 0,
			 1, 1, 0, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0},

			{1, 1, 0, 0,
			 1, 1, 0, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0}
	};
int display_menu(void); /* 메뉴를 보여줌 */

int main(void)
{
	int menu = 1;
	setlocale(LC_CTYPE, "ko_KR.utf-8");

	while(menu)
	{
		menu = display_menu();

		if(menu == 1)
		{
			game = GAME_START;
			menu = game_start();
		}
		else if(menu == 2)
		{
			game = GAME_START;
			menu = game_start_2p();
		}
		else if(menu == 3)
		{
			search_result();
		}
		else if(menu == 4)
		{
			print_result();
		}
		else if(menu == 5)
		{
			clear();
			endwin();
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
		printw("\n\t\t\t  △   : 1p - w, 2p - i");
		printw("\n\t\t\t◁   ▷ : 1p - a/d, 2p - j/l");
		printw("\n\t\t\t  ▽   : Soft Drop");
		printw("\n\t\t\tspace bar : Hard Drop");
		printw("\n\n\t\t\t1) 혼자서 하기");
		printw("\n\t\t\t2) 둘이서 하기");
		printw("\n\t\t\t3) 기록 검색");
		printw("\n\t\t\t4) 기록 출력");
		printw("\n\t\t\t5) 종료");
		printw("\n\n\t\t\t\t\t 선택 : ");

		scanw("%d",&menu);
		if(menu < 1 || menu > 5)
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

/*문자를 바로 입력 받을 수 있는 함수*/
int _getch(void)
{
             char   ch;
             int   error;
             static struct termios Otty, Ntty;

             fflush(stdout);
             tcgetattr(0, &Otty);
             Ntty = Otty;
             Ntty.c_iflag  =  0;
             Ntty.c_oflag  =  0;
             Ntty.c_lflag &= ~ICANON;
#if 1
            Ntty.c_lflag &= ~ECHO;
#else
            Ntty.c_lflag |=  ECHO;
#endif
            Ntty.c_cc[VMIN]  = CCHAR;
            Ntty.c_cc[VTIME] = CTIME;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

            if (0 == (error = tcsetattr(0, FLAG, &Ntty)))
            {
                       error  = read(0, &ch, 1 );
                       error += tcsetattr(0, FLAG, &Otty);
            }

            return (error == 1 ? (int) ch : -1 );
}


int set_ticker(int game_state)
{
        struct itimerval new_timeset;
	
	if(game_state==GAME_START){
		new_timeset.it_interval.tv_sec  = 0;        /* set reload  */
		new_timeset.it_interval.tv_usec = 1;      /* new ticker value */
		new_timeset.it_value.tv_sec     = 0  ;      /* store this   */
		new_timeset.it_value.tv_usec    = 1 ;     /* and this     */
	}
	else if(game_state==GAME_END){
		new_timeset.it_interval.tv_sec  = 0;        /* set reload  */
		new_timeset.it_interval.tv_usec = 0;      /* new ticker value */
		new_timeset.it_value.tv_sec     = 0  ;      /* store this   */
		new_timeset.it_value.tv_usec    = 0 ;     /* and this     */
	}
	else return 1;

	return setitimer(ITIMER_VIRTUAL, &new_timeset, NULL);
}
