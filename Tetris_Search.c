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
#include "Tetris_Search.h"
#include <locale.h>
#include <ncursesw/curses.h>

/*메뉴에서 기록검색시 호출되어 기러고을 검색하는 함수*/
int search_result(void)
{
	FILE *fp = NULL;
	char name[30];
	char ch = 1;
	int find = 0;
	setlocale(LC_CTYPE, "ko_KR.utf-8");

	fp = fopen("result.txt", "r");

	if(fp == NULL)
		return 0;

	initscr();
	clear();

	printw("\n\n\t\t검색할 이름을 입력하세요.  : ");
	scanw("%s%*c", name);

	printw("\n\t\t\t\tText Tetris");
	printw("\n\t\t\t\t 게임 기록\n\n");
	printw("\n\t\t이름\t\t점수\t   날짜\t\t 시간");

	while(!feof(fp))
	{
		//fread(&temp_result, sizeof(struct result), 1, fp);
		fscanf(fp, "%s %ld %d %d %d %d %d\n", temp_result.name, &temp_result.point,&temp_result.year, &temp_result.month, &temp_result.day, &temp_result.hour, &temp_result.min);
		if(!strcmp(temp_result.name, name))
		{
			find = 1;
			printw("\n\t========================================================");
			printw("\n\t\t%s\n\t\t\t\t%ld\t%d. %d. %d.  |  %d : %d\n", temp_result.name, temp_result.point, temp_result.year, temp_result.month, temp_result.day, temp_result.hour, temp_result.min);
		}
	}
	printw("\n\t========================================================");

	if(find == 0)
		printw("\n\n\n\t\t검색된 이름이 없습니다.");

	printw("\n\n\n\t\t게임 메뉴로 돌아가기 : M");
	refresh();
	while(1)
	{
		ch = _getch();
		if(ch == 77 || ch == 109)
		{
			break;
		}
	}
	return 0;
}
