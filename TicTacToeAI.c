/*********************************************************************
 * Tic-Tac-Toe game set up for experimentation of the AI player.
 * Not that fancy, nor that well made. Most effort was made in making
 * this work before being fancy.
 *
 * Problems:
 *	Game immediately shuts down on game end
 *	No chance to play again without program restart
 *	AI is not difficult or optimized
 *	Random nature is less strategic and more lucky
 *
 * Favorable Thoughts:
 *	AI was created without any prior experience or research
 *	Same for the game
 *
 * Compiled on Linux with gcc and libncurses5-dev
 * Created by: Austin Karn(synthVerity)
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

void setPiece(int x, int y, int turn);
void printBoard();
char pieceCheck(int *turn);
void AIPlayer();
int checkWin();

// Globals make me uncomfortable, but it was the best solution
int board[3][3] = {
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
		  };

// Obvious main is obvious
int main(int argc, char *argv[])
{
	// Basic set-up of the variables and screen
	srand(time(NULL));
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	// Whoever begins is random, to take away complete first move advantages
	int turn = rand() % 2 + 1;
	int x = 1, y = 0;
	int running = 1;

	// Main loop of the game
	while(running)
	{
		// Basic set-up of ascii board and text output
		erase();
		printBoard();
		printw("Please input grid location using arrow keys and Enter. F1 to exit.\n");
		printw("It's %c turn.", pieceCheck(&turn));
		move(y, x);

		// Used to check whether program should terminate or not.
		running = checkWin();

		// User input for movement and piece placement
		switch(getch())
		{
			case KEY_F(1):
				running = 0;
				break;
			case KEY_UP:
				if(y != 0)
					y -= 2;
				break;
			case KEY_DOWN:
				if(y < 4)
					y += 2;
				break;
			case KEY_LEFT:
				if(x > 1)
					x -= 4;
				break;
			case KEY_RIGHT:
				if(x < 8)
					x += 4;
				break;
			case 10:
				setPiece(x, y, turn);
				if(turn == 1) turn = 2;
				else turn = 1;
				break;
		}
	}

	// Cleanup of program and ncurses
	endwin();
	return 0;
}

// Function used to place piece according to where the cursor is located.
// Only can be used by human player
void setPiece(int x, int y, int turn)
{
	if(board[y/2][(x-1)/4] == 0)
	{
		board[y/2][(x-1)/4] = turn;
	}

	return;
}

// Prints out the board using the board[] array
void printBoard()
{
	int i, j;
	char piece;

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j< 3; j++)
		{
			if(board[i][j] == 0) piece = ' ';
			else if(board[i][j] == 1) piece = 'X';
			else piece = 'O';

			if(j < 2) printw(" %c |", piece);
			else printw(" %c ", piece);
		}
		if(i < 2) printw("\n-----------\n");
		else printw("\n");
	}

	return;
}

// Checks whose turn it is, calling on the AI when it's turn is up
char pieceCheck(int *turn)
{
	if(*turn == 1) return 'X';
	else
	{
		AIPlayer();
		*turn = 1;
		return ' ';
	}
}

// AI function, quite long, not optimized much, easily defeated
// Created without research on tic-tac-toe perfect games, or outside assistance
// Needs to be improved
void AIPlayer()
{
	int i, j;

	if(board[0][0] == board[1][1] && board[2][2] == 0 && board[0][0] != 0)
	{
		board[2][2] = 2;
		return;
	}
	else if(board[1][1] == board[2][2] && board[0][0] == 0 && board[1][1] != 0)
	{
		board[0][0] = 2;
		return;
	}
	else if(board[0][0] == board[2][2] && board[1][1] == 0 && board[0][0] != 0)
	{
		board[1][1] = 2;
		return;
	}
	else if(board[0][2] == board[1][1] && board[2][0] == 0 && board[0][2] != 0)
	{
		board[2][0] = 2;
		return;
	}
	else if(board[1][1] == board[2][0] && board[0][2] == 0 && board[1][1] != 0)
	{
		board[0][2] = 2;
		return;
	}
	else if(board[0][2] == board[2][0] && board[1][1] == 0 && board[0][2] != 0)
	{
		board[1][1] = 2;
		return;
	}

	for(i = 0; i < 3; i++)
	{
		if(board[i][0] == board[i][1] && board[i][2] == 0 && board[i][0] != 0)
		{
			board[i][2] = 2;
			return;
		}
		else if(board[i][1] == board[i][2] && board[i][0] == 0 && board[i][1] != 0)
		{
			board[i][0] = 2;
			return;
		}
		else if(board[i][0] == board[i][2] && board[i][1] == 0 && board[i][0] != 0)
		{
			board[i][1] = 2;
			return;
		}
		else if(board[0][i] == board[1][i] && board[2][i] == 0 && board[0][i] != 0)
		{
			board[2][i] = 2;
			return;
		}
		else if(board[1][i] == board[2][i] && board[0][i] == 0 && board[1][i] != 0)
		{
			board[0][i] = 2;
			return;
		}
		else if(board[0][i] == board[2][i] && board[1][i] == 0 && board[0][i] != 0)
		{
			board[1][i] = 2;
			return;
		}
	}

	// If no obvious winning moves or blocks to be done, takes the middle slot(if open)
	// If the middle slot is not possible, then take a random slot
	// While it's not useful, makes the game more interesting
	for(;;)
	{
		if(board[1][1] == 0)
		{
			board[1][1] = 2;
			break;
		}

		i = rand() % 3;
		j = rand() % 3;
		if(board[i][j] == 0)
		{
			board[i][j] = 2;
			break;
		}
	}

	return;
}

// Checks the board to see if there are winning conditions or a draw
int checkWin()
{
	int i, j;

	if(board[1][1] != 0)
	{
		if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
			return 0;

		if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
			return 0;
	}

	for(i = 0; i < 3; i++)
	{
		if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != 0)
			return 0;

		if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != 0)
			return 0;
	}

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if(board[i][j] == 0)
			{
				return 1;
			}
		}
	}

	return 0;
}
