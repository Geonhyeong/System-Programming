#include<unistd.h>
#include<stdio.h>
#include<ncursesw/curses.h>
#include<signal.h>
#include<aio.h>
#include<string.h>
#include<termios.h>
#include<stdlib.h>
#include<locale.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

typedef struct _tetris{
int level;
int gameover;
int score;
int rotation;
int absX,absY;
int curX,curY;
int curblock;
int nextblock;
}Tetris;

struct aiocb kbcbuf;
int set_ticker(int);

void game_mode();
void game_setting();

int game_board[25][14];


