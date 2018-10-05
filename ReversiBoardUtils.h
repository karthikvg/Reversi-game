#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ReversiGame {
	char **board;	// char 'w' for whites, 'b' for blacks ' ' for empty 
	// do allocate memory for '\0' as it is character array.
	char *player1name;
	char *player2name;
	int whiteCount = 0;
	int blackCount = 0;
	int NumberofMoves = 0;
	int rows, cols;
	int turn = 1;   //1 for white, -1 for black
	int state = 0;  //0 for unfinished, 1 for game over
	int winner = 0; //1 for white, -1 for black
}ReversiGame;


void endGame(ReversiGame *game);
int hasMove(ReversiGame *game);
void modifyTurn(ReversiGame *game);

/*

Create a new ReversiGame By allocating memory from Heap , Let it be game;
Create a 2D Array from Heap(Dynamically) with specified number of rows and cols
and copy its reference to game->board;

Note : Return NULL for Invalid Inputs
Note : Copy Rows into newlyCreatedBoard->rows , and vice versa for cols ,
Also copy player1name,player2name.
*/

ReversiGame * createNewGame(int rows, int cols, char *player1, char *player2) {
	if (rows <= 1 || cols <= 1 || rows != cols || player1 == NULL || player2 == NULL)
		return NULL;
	ReversiGame *game = (struct ReversiGame*)malloc(sizeof(struct ReversiGame));
	game->rows = rows;
	game->cols = cols;
	game->player1name = player1;
	game->player2name = player2;
	game->NumberofMoves = 0;
	game->state = 0;
	game->winner = 0;
	game->board = (char**)malloc(sizeof(char*)*(rows));
	for (int i = 0; i < rows; i++)
		game->board[i] = (char*)malloc(sizeof(char)*(cols+1));
	
	return game;
}


/*
Copy the tobeCopied Array into game->board .
Learn how to Copy a 2D array when address of first row is given.
Note this function is called in the following way

Also Initialize the turn variable, whiteCount with no of white coins and same for black.

Do Nothing for Invalid Inputs
*/

void initializeReversiGame(ReversiGame *game, char *tobeCopiedBoard, int rows, int cols, int turn){
	if (game == NULL || tobeCopiedBoard == NULL || rows <= 1 || cols <= 1 || turn < -1 || turn>1 || turn == 0)
		return;
	//game->board = (char**)malloc(sizeof(char*)*(rows));
	game->turn = turn;
	int white = 0,black=0;
	for (int i = 0; i < rows; i++)
	{
		//game->board[i] = (char*)malloc(sizeof(char)*(cols + 1));
		game->board[i][cols] = '\0';
		for (int j = 0; j < cols; j++)
		{
			game->board[i][j] = tobeCopiedBoard[i*cols+j+i];
			if (game->board[i][j] == 'w')
				white++;
			if (game->board[i][j] == 'b')
				black++;
			//printf("%2d ", game->board[i][j]);
		}
	}
	game->blackCount = black;
	game->whiteCount = white;
	if (black + white == rows*cols)
	{
		endGame(game);
	}
	if (!hasMove(game))
		modifyTurn(game);
	return;
}

/*
Check if the Current board is in End Position . Return 0 if the game is Ended, 1 if not .
Win Condition : Either all the squares are filled or a stalemate position (No one can Move)

*/
bool isBoardFull(ReversiGame* game)
{
	int rows = game->rows, cols = game->cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			if (game->board[i][j] == ' ')
				return false;
	}
	return true;
}
int checkReversiGameOver(ReversiGame *game){
	if (isBoardFull(game))
	{
		game->state = 1;
		endGame(game);
		return false;
	}
	if (hasMove(game))
		return true;
	modifyTurn(game);
	if (hasMove(game))
		return true;
	modifyTurn(game);
	game->state = 1;
	endGame(game);
	return false;
}

void printMoves(ReversiGame *game){
	/*
	Sample output :
	Whites Count : 5
	Black Count : 4
	Move Count : 9
	*/
	printf("Whites Count : %d  ", game->whiteCount);
	printf("Black Count : %d  ", game->blackCount);
	printf("Move Count : %d\n\n\n", game->NumberofMoves);
	return;
}

/*
Print the Board in a Good Way.Make sure Each Number is properly formatted and Seperated, and Row lines too .
Print Empty Space when you encounter 0.Also make sure your board looks good for 5x5 or 7x7 boards too .
Use your Thinking / UI Skills .
See the link we shared for sample screenshots for inspiration.
*/

void drawBoardOnScreen(ReversiGame *game) {
	for (int i = 0; i < game->rows; i++)
	{
		for (int j = 0; j < game->cols; j++)
		{
			if (game->board[i][j] == ' ')
				printf(" . ");
			else
			printf("%2c ", game->board[i][j]);
		}
		printf("\n");
	}
	return;
}

/*
Clear The Screen , So that we can redraw the Board (which has modified values )
*/

void clearScreen(ReversiGame *game){
	//system("cls");
	drawBoardOnScreen(game);
}

/*
Clear the Screen and ReDraw the Board ,Call above two functions
*/

void clearAndRedrawScreen(ReversiGame *game){
	clearScreen(game);
}



