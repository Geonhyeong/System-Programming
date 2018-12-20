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
#include "Tetris_Result.h"
#include <ncursesw/curses.h>
#include <locale.h>

/* 메뉴에서 기록출력시 호출되어 기록을 출력하는 함수*/
int print_result(void)
{
	FILE *fp = NULL;
	char ch = 1 ;
	setlocale(LC_CTYPE, "ko_KR.utf-8");
	
	fp = fopen("result.txt", "r");

	if(fp == NULL)
		return 0;

	initscr();
	clear();
	printw("\n\t\t\t\tText Tetris");
	printw("\n\t\t\t\t 게임 기록\n\n");
	printw("\n\t\t이름\t\t점수\t   날짜\t\t 시간");

	while(!feof(fp))
	{
//			fread(&temp_result, sizeof(struct result), 1, fp);
			fscanf(fp, "%s %ld %d %d %d %d %d\n", temp_result.name, &temp_result.point, &temp_result.year, &temp_result.month, &temp_result.day, &temp_result.hour, &temp_result.min);
			printw("\n\t========================================================");
			printw("\n\t\t%s\n\t\t\t\t%ld\t %d. %d. %d.  |  %d : %d\n", temp_result.name, temp_result.point, temp_result.year, temp_result.month, temp_result.day, temp_result.hour, temp_result.min);
	}

	fclose(fp);

	printw("\n\n\t게임 메뉴로 돌아가기 : M");
	refresh();
	while(1)
	{
		ch = _getch();
		if(ch == 77 || ch == 109)
			break;
	}
	endwin();
	return 1;

}



