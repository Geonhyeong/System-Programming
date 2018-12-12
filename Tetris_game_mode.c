
#include"Tetris_game_mode.h"

void game_on_input(int signum);
int done2=0;
int level=1;
int score=0;

void game_mode(){
	setlocale(LC_CTYPE, "ko_KR.utf-8");
	void on_alarm(int);
	void on_input(int);
	void setup_aio_buffer();

	clear();
	game_setting();

	//signal(SIGALRM,on_alarm);
	//set_ticker(delay);
	signal(SIGIO,game_on_input);
	setup_aio_buffer();
	aio_read(&kbcbuf);

	while(!done2)
		pause();
	endwin();

}

void game_setting(){
	int i, j;
	for(i=0;i<25;i++){	
		for(j=0;j<14;j++){
			if(i==24 || j==0 || j==13)
				game_board[i][j]=1;
		}
	}
	
	for(i=0;i<25;i++){	
		for(j=0;j<14;j++){
			if(!game_board[i][j])
				mvaddstr(i,j*2+1," ");
			else
				mvaddstr(i,j*2+1,"■");
		}
	}
	for(i=14;i<21;i++){
		mvaddstr(0,i*2+1,"■");
		mvaddstr(7,i*2+1,"■");	
	}
	for(i=1;i<7;i++){
		mvaddstr(i,20*2+1,"■");
	}
	
	mvaddstr(10,15*2+1,"Level :");
	mvaddstr(12,15*2+1,"Score :");

	mvaddstr(21,15*2+1,"  △   : Shift");
	mvaddstr(22,15*2+1, "◁   ▷ : Left / Right");
	mvaddstr(23,15*2+1,"  ▽   : Soft Drop");
	mvaddstr(24,15*2+1,"  ESC  : Quit");
	
	refresh();
	
	
}
void game_on_input(int signum)
{
	int c;
	char *cp=(char*)kbcbuf.aio_buf;

	if(aio_error(&kbcbuf)!=0)
		perror("reading failed");
	else
		if(aio_return(&kbcbuf)==1){
			return;
		}
	aio_read(&kbcbuf);

}
/*
void on_alarm(int signum){
	signal(SIGALRM,on_alarm);
	
}*/

void setup_aio_buffer(){
	static char input[1];

	kbcbuf.aio_fildes=0;
	kbcbuf.aio_buf=input;
	kbcbuf.aio_nbytes=1;
	kbcbuf.aio_offset=0;

	kbcbuf.aio_sigevent.sigev_notify=SIGEV_SIGNAL;
	kbcbuf.aio_sigevent.sigev_signo=SIGIO;
}

