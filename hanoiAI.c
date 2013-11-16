#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

#define MAXSTACK 9
#define EMPTYSTACK -1

typedef struct
{
	int size;
} Disk;

Disk pegs[3][MAXSTACK];

void initPegs(int height, int *top);
void displayPegs();
void push(int peg, int *top, Disk value);
Disk pop(int peg, int *top);
int peek(int peg, int top);
int isEmpty(int top);
void AISolver(int height);
int checkWin(int height);
void clearPegs();

int main(void)
{
	srand(time(NULL));
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);

	int turn = 0;
	int top1, top2, top3;
	int running = 1;
	int disks = rand() % 7 + 3;
	Disk holder = {0};

	top1 = top2 = top3 = EMPTYSTACK;

	initPegs(disks, &top1);

	while(running)
	{
		erase();
		printw("    %d\n\n", holder.size);
		displayPegs();
		printw("\n %d  %d  %d\n", top1+1, top2+1, top3+1);

		running = checkWin(disks);

		switch(getch())
		{
			case KEY_F(1):
				running = 0;
				break;
			case KEY_F(2):
				AISolver(disks);
				top1 = top2 = top3 = EMPTYSTACK;
				initPegs(disks, &top1);
				break;
			case KEY_LEFT:
				if(turn)
				{
					if((!(isEmpty(top1)) && holder.size < pegs[0][top1].size) || isEmpty(top1))
						push(0, &top1, holder);
					else break;
				}
				else if(isEmpty(top1)) break;
				else
				{
					holder = pop(0, &top1);
					pegs[0][top1+1].size = 0;
				}

				if(turn == 1) turn = 0;
				else turn = 1;

				break;
			case KEY_UP:
				if(turn)
				{
					if((!(isEmpty(top2)) && holder.size < pegs[1][top2].size) || isEmpty(top2))
						push(1, &top2, holder);
					else break;
				}
				else if(isEmpty(top2)) break;
				else
				{
					holder = pop(1, &top2);
					pegs[1][top2+1].size = 0;
				}

				if(turn == 1) turn = 0;
				else turn = 1;

				break;
			case KEY_RIGHT:
				if(turn)
				{
					if((!(isEmpty(top3)) && holder.size < pegs[2][top3].size) || isEmpty(top3))
						push(2, &top3, holder);
					else break;
				}
				else if(isEmpty(top3)) break;
				else
				{
					holder = pop(2, &top3);
					pegs[2][top3+1].size = 0;
				}

				if(turn == 1) turn = 0;
				else turn = 1;

				break;
		}

		refresh();
	}

	endwin();
	return 0;
}

void initPegs(int height, int *top)
{
	int i;
	Disk holder;

	for(i = 0; i < height; i++)
	{
		holder.size = MAXSTACK - i;

		push(0, top, holder);
	}

	return;
}

void displayPegs()
{
	int i, j;

	for(i = 0; i < MAXSTACK; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if(pegs[j][(MAXSTACK-1)-i].size == 0) printw(" - ");
			else printw(" %d ", pegs[j][(MAXSTACK-1)-i].size);
		}
		printw("\n");
	}
}

void push(int peg, int *top, Disk value)
{
	pegs[peg][++*top] = value;

	return;
}


Disk pop(int peg, int *top)
{
	*top -= 1;

	return pegs[peg][*top+1];
}

int peek(int peg, int top)
{
	return pegs[peg][top].size;
}

int isEmpty(int top)
{
	if(top <= EMPTYSTACK) return 1;
	else return 0;
}

void AISolver(int height)
{
	return;
}

int checkWin(int height)
{
	int i;

	for(i = 0; i < height; i++)
	{
		if(pegs[2][i].size != MAXSTACK - i)
		{
			return 1;
		}
	}

	return 0;
}

void clearPegs()
{
	int i, j;
	Disk holder = {0};

	for(i = 0; i < 3; i++)
	{
		for(j = MAXSTACK; j > 0; j--)
		{
			pegs[i][j] = holder;
		}
	}

	return;
}
