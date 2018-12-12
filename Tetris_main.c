#include<unistd.h>
#include<stdio.h>
#include<ncursesw/curses.h>
#include<signal.h>
#include<aio.h>
#include<string.h>
#include<termios.h>
#include<stdlib.h>
#include<locale.h>
#include"Tetris_game_mode.h"

int done=0;


void main(){
	setlocale(LC_CTYPE, "ko_KR.utf-8");
	void on_alarm(int);
	void on_input(int);
	void setup_aio_buffer();

	initscr();
	crmode();
	noecho();
	clear();

	mvaddstr(0,0,"■ □ □ □ ■ ■ ■ □ □ ■ ■ □ ■ ■ "); 
	mvaddstr(1,0,"■ ■ ■ □ □ ■ □ □ □ ■ ■ □ □ ■ "); //sleep(1);refresh();
	mvaddstr(2,0,"□ □ □ ■ □ □ □ □ □ □ □ ■ □ ■ ");
	mvaddstr(3,0,"■ ■ □ ■ ■ □ □ ■ □ □ □ ■ □ □ "); 
	mvaddstr(4,0,"■ ■ □ ■ □ □ □ ■ ■ ■ □ ■ ■ □ ");//sleep(1);refresh();
	mvaddstr(6,0,"T E T R I S"); 
	mvaddstr(7,0,"Please Enter Any Key to Start..");
	mvaddstr(8,0,"  △   : Shift");
	mvaddstr(9,0, "◁   ▷ : Left / Right");
	mvaddstr(10,0,"  ▽   : Soft Drop");
	mvaddstr(11,0,"  ESC  : Quit");
	sleep(1);refresh();

	signal(SIGIO,on_input);
	setup_aio_buffer();
	aio_read(&kbcbuf);

	while(!done)
		pause();
	endwin();
}

void on_input(int signum)
{
	int c;
	char *cp=(char*)kbcbuf.aio_buf;

	if(aio_error(&kbcbuf)!=0)
		perror("reading failed");
	else
		if(aio_return(&kbcbuf)==1){
			game_mode();
			done=0;
		}
	aio_read(&kbcbuf);

}
