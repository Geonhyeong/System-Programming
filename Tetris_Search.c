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

/*메뉴에서 기록검색시 호출되어 기러고을 검색하는 함수*/
int search_result(void)
{
	FILE *fp = NULL;
	char name[30];
	char ch;
	int find = 0;

	fp = fopen("result", "rb");

	if(fp == NULL)
		return 0;

	system("clear");

	printf("\n\n\t\t검색할 이름을 입력하세요.  : ");
	scanf("%s%*c", name);

	printf("\n\t\t\t\tText Tetris");
	printf("\n\t\t\t\t 게임 기록\n\n");
	printf("\n\t\t이름\t\t점수\t   날짜\t\t 시간");

	while(1)
	{
		fread(&temp_result, sizeof(struct result), 1, fp);
		if(!feof(fp))
		{
			if(!strcmp(temp_result.name, name))
			{
				find = 1;
				printf("\n\t========================================================");
				printf("\n\t\t%s\n\t\t\t\t%ld\t%d. %d. %d.  |  %d : %d\n", temp_result.name, temp_result.point, temp_result.year, temp_result.month, temp_result.day, temp_result.hour, temp_result.min);
			}
		}
		else
		{
			break;
		}
	}

	if(find == 0)
		printf("\n\n\n\t\t검색된 이름이 없습니다.");

	printf("\n\n\n\t\t게임 메뉴로 돌아가기 : M");
	while(1)
	{
		ch = getch();
		if(ch == 77 || ch == 109)
			break;
	}

	return 0;
}
