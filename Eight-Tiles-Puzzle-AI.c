//Sudhirkumar Sawarbandhe
//Artificial Intelligence Assignment

/*The 8 puzzle consists of eight numbered, movable tiles set in a 3x3 frame.
One cell of the frame is always empty thus making it possible to move an adjacent numbered tile into the empty cell.
The program is to change the initial configuration into the goal configuration.*/

#include<stdio.h>
#include<conio.h>

#define NONE 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int path[50];
int top = 0;

int check_goal (int a[][3])
{
	// Goal state :
	/*
		1 2 3
		4 5 6
		7 8 9
	*/
	
	int i, j;
	int goal = 1;
	
	for (i=0; i<3 && goal; i++)
	{
		for (j=0; j<3 && goal; j++)
		{
			if (a[i][j] != i*3+j+1)
			{
				goal = 0;
			}
		}
	}
	
	return goal;
}


void swap (int *a, int *b)
{
	int t;
	
	t = *a;
	*a = *b;
	*b = t;
	
	return;
}


void print (int a[][3])
{
	int i, j;
	for (i=0; i<3; i++)
	{
		printf("\t");
		for (j=0; j<3; j++)
		{
			if (a[i][j] == 9)
				printf("  ");
			else
				printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


// a - current state
// cur_level - current level
// level - max level for this iteration
// i - row pos of blank
// j - col pos of blank
// action - action of parent state leading to current state (up, down, left, or right)


int search (int a[][3], int cur_level, int level, int i, int j, int action)
{
	if (cur_level == level)
	{
		return check_goal(a);
	}
	
	else
	{
		int found = 0;
		
		if (action != UP && i < 2)
		{
			swap(&a[i][j], &a[i+1][j]);
			path[top++] = DOWN;
			
			found = search(a, cur_level+1, level, i+1, j, DOWN);
			
			if (found)
				return found;
			else
			{
				swap(&a[i][j], &a[i+1][j]);
				top--;
			}
		}
		
		if (action != DOWN && i > 0)
		{
			swap(&a[i][j], &a[i-1][j]);
			path[top++] = UP;
			
			found = search(a, cur_level+1, level, i-1, j, UP);
			if (found)
				return found;
			else
			{
				swap(&a[i][j], &a[i-1][j]);
				top--;
			}
		}
		
		if (action != LEFT && j < 2)
		{
			swap(&a[i][j], &a[i][j+1]);
			path[top++] = RIGHT;
			
			found = search(a, cur_level+1, level, i, j+1, RIGHT);
			if (found)
				return found;
			else
			{
				swap(&a[i][j], &a[i][j+1]);
				top--;
			}
		}
		
		if (action != RIGHT && j > 0)
		{
			swap(&a[i][j], &a[i][j-1]);
			path[top++] = LEFT;
			
			found = search(a, cur_level+1, level, i, j-1, LEFT);
			if (found)
				return found;
			else
			{
				swap(&a[i][j], &a[i][j-1]);
				top--;
			}
		}
		
		return 0;
	}
}



int main()
{
	int input[3][3], in2[3][3];
	int inv_count, level, pos_i, pos_j;
	int solvable, found;
	int i, j, k, l;
	
	printf("Enter any random state:\n(Enter blank as 9)\n\n");
	
	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			scanf("%d", &input[i][j]);
			in2[i][j] = input[i][j];
			
			if (input[i][j] == 9)
			{
				pos_i = i;
				pos_j = j;
			}
		}
	}

	
	//check if solvable
	
	inv_count = 0;
	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			if (input[i][j] != 9)
			{
				for (k=i; k<3; k++)
				{
					if (k == i)
						l = j+1;
					else
						l = 0;
						
					for (; l<3; l++) 
					{
						if (input[k][l] != 9 && input[k][l] < input[i][j])
						{
							inv_count++;
						}
					}
				}
			}
		}
	}
	
	if (inv_count % 2 == 0)
		solvable = 1;
	
	else
		solvable = 0;
	

	
	//iterative deepening search
	
	if (solvable)
	{
		found = 0;
		
		level = 0;
		while (!found)
		{
			found = search(in2, 0, level, pos_i, pos_j, NONE);
			level++;
		}
		
		printf("\n\nSolution found at level %d\n\n", level-1);
		printf("Steps to goal state:\n\n");
		
		print(input);
		for (i=0; i<top; i++)
		{
			if (path[i] == UP)
			{
				swap(&input[pos_i][pos_j], &input[pos_i-1][pos_j]);
				pos_i--;
				print(input);
			}
			else if (path[i] == DOWN)
			{
				swap(&input[pos_i][pos_j], &input[pos_i+1][pos_j]);
				pos_i++;
				print(input);
			}
			else if (path[i] == LEFT)
			{
				swap(&input[pos_i][pos_j], &input[pos_i][pos_j-1]);
				pos_j--;
				print(input);
			}
			else if (path[i] == RIGHT)
			{
				swap(&input[pos_i][pos_j], &input[pos_i][pos_j+1]);
				pos_j++;
				print(input);
			}
		}
	}
	
	else
	{
		printf("This configuration is not solvable");
	}
	
	getch();
	
}


