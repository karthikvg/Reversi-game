/*
This struct denotes the move played by user, X means the x cordinate and Y means y cordinate.
*/
typedef struct ReversiMove {
	int x, y;
}ReversiMove;

/*
Create a ReversiMove struct (malloc/calloc etc) and return it.
Assign parameters x and y to its fields.
*/
char charAt(ReversiGame* board, int x, int y)
{
	if (x > board->rows || y > board->cols || x <= 0 || y <= 0)
		return '*';
	return board->board[x - 1][y - 1];
}
void setChar(ReversiGame* board, int x, int y,char ch)
{
	if (x > board->rows || y > board->cols || x <= 0 || y <= 0)
		return ;
	board->board[x - 1][y - 1]=ch;

}
ReversiMove *createMove(int x, int y) {
	ReversiMove* move = (ReversiMove*)malloc(sizeof(struct ReversiMove));
	if (x <= 0 || y <= 0)
		return NULL;
	move->x = x;
	move->y = y;
	return move;
}

/*
	Take Only Valid Input x, y two integers . If Invalid input is entered ,Take input again . Keep Taking input until its valid
	Hint : Use While Loop and isValidInput function
	Cordinates are 1 indexed. Ie first row/column is denoted by 1 while giving input.
*/
/*
To check the validity of coordinate on the board
*/
int isvalidCoordinate(ReversiGame *game, int x, int y) {
	if (game == NULL || x < 1 || y < 1||x>game->rows||y>game->cols)
	return 0;
	return 1;
}

ReversiMove *inputMove(ReversiGame *game) {
	return NULL;
}

/*
Check if the move can be placed, if its going to make a valid capture to the opponent coins
*/
int checking(ReversiGame* game, int x, int y, int a, int b, int search, int curr)
{
	int i, j;
	for (i = x + a, j = y + b; charAt(game, i, j) == curr; i += a, j += b);
	return charAt(game, i, j) == search ? 1 : 0;
}
int isValidMove(ReversiGame *game, ReversiMove *move) {
	if (game == NULL || move == NULL)
		return false;
	//printf("reached");
	int x = move->x;
	int y = move->y;
	int rows = game->rows;
	int cols = game->cols;
	//printf("%d %d %c\n",x,y,charAt(game, x, y));
	if (x <= 0 || y <= 0 || x > rows || y > cols||charAt(game,x,y)!=' ')
		return 0;
	//printf("reached");
	char currentChar = game->turn == 1 ? 'w' : 'b';
	char searchingChar = currentChar == 'w' ? 'b' : 'w';
	if (!isvalidCoordinate(game, move->x, move->y))
		return 0;
	
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;
			if (charAt(game, x + i, y + j) == searchingChar)
			{
				int ans=checking(game, x, y, i, j, currentChar, searchingChar);
				if (ans == 1)
					return true;
			}
		}
	}
	return 0;
}

/*
Check if the player can move , if the player is not able to move, he looses the turn
and the opponent gets the chance to play.
If both players are not able to make a move, then the game ends.
*/

int hasMove(ReversiGame *game){
	//char currentChar = game->turn==1?'w':'b';
	//char searchingChar = currentChar=='w'?'b':'w';
	int rows = game->rows;
	int cols = game->cols;
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= cols; j++)
		{
			if (charAt(game,i, j) == ' '&&isValidMove(game,createMove(i,j)))
			{
				return true;
			}
		}
	}
	return 0;
}

/*
Increment the number of moves in ReversiGame struct.
*/
void incrementMoves(ReversiGame *game) {
	game->NumberofMoves++;
	return;
}

/*
Toggle the turn in Reversi Game.
This function is to be called when you want to change the turn.
*/
void modifyTurn(ReversiGame *game) {
	game->turn = game->turn == 1?-1 : 1;
	return;
}

/*
End Reversi Game.
Populate game->winner field accordingly with who won. 1 for white, -1 for black.
This function is to be called when the game is ended.
*/
void endGame(ReversiGame *game) {
	int white = 0, black = 0;
	for (int i = 0; i < game->rows; i++)
	{
		for (int j = 0; j < game->cols; j++)
		{
			if (game->board[i][j] == 'w')
				white++;
			if (game->board[i][j] == 'b')
				black++;
		}
	}
	if (white > black)
		game->winner = 1;
	else if (black > white)
		game->winner = -1;
	else
		game->winner = 0;
	game->state = 1;
	return;
}

/*
	Wrapper function you will call only modify to increment moves and modify the turn.
*/

void modify(ReversiGame *game) {
	incrementMoves(game);
	modifyTurn(game);
}


/*
	This function performs move action on the board
	Note : call validity check performs using above functions before making a move
	returns :
	true on move sucess
	false if move is invalid
*/
void filler(ReversiGame* game, int x, int y, int a, int b, int changingChar)
{
	int i, j;
	char currentChar = changingChar == 'w' ? 'b' : 'w';
	for (int i = x + a, j = y + b; charAt(game,i, j) == changingChar; i += a, j += b)
	{
		setChar(game, i, j, currentChar);
		if (currentChar == 'w')
		{
			//printf("eeeeeee\n");
			game->whiteCount++;
			game->blackCount--;
		}
		else
		{
			//printf("ccccc\n");
			game->blackCount++;
			game->whiteCount--;
		}
	}
}
void play(ReversiGame* game, ReversiMove* move)
{
	int x = move->x;
	int y = move->y;
	char currentChar = game->turn == 1 ? 'w' : 'b';
	char changingChar = currentChar == 'w' ? 'b' : 'w';
	setChar(game, x, y, currentChar);
	if (currentChar == 'w')
		game->whiteCount++;
	else
		game->blackCount++;
	modify(game);
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;
			if (charAt(game, x + i, y + j) == changingChar&&checking(game, x, y, i, j, currentChar, changingChar))
			{
				filler(game, x, y, i, j, changingChar);

			}
		}
	}
}
bool playMove(ReversiGame *game, ReversiMove *move) {
	if (!isValidMove(game, move) || !checkReversiGameOver(game))
	{

		//modifyTurn(game);
		hasMove(game) ? 0:modifyTurn(game);
		return false;
	}
	if (isValidMove(game, move))
	{
		play(game, move);
	}
	else
	{
		modifyTurn(game);
		play(game, move);
	}
	hasMove(game) ? 0 : modifyTurn(game);
	return true;
}


void printWinner(ReversiGame *game) {
	if (game->winner == 1)
		printf("Result %s has won.\n", game->player1name);
	else if (game->winner == -1)
		printf("Result %s has won.\n", game->player2name);
	else
		printf("Result Game is Drawn\n");
	
	/*
	Sample output :
	Result Praveen has won. / Game is Drawn.
	*/
}