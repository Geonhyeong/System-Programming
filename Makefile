all : Tetris

Tetris : Tetris_Main.c Tetris_GameStart.c Tetris_Result.c Tetris_Search.c
	cc Tetris_Main.c Tetris_GameStart.c Tetris_Result.c Tetris_Search.c -lncursesw -o Tetris
