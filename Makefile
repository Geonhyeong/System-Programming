all : Tetris

Tetris : Tetris_Main.c Tetris_GameStart.c Tetris_GameStart2P.c Tetris_Result.c Tetris_Search.c
	cc Tetris_Main.c Tetris_GameStart.c Tetris_GameStart2P.c Tetris_Result.c Tetris_Search.c -lncursesw -o Tetris
