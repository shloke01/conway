/*
To implement Conway's Game of Life.

Preconditions: User must input a valid choice among characters 'R', 'S', 'O', 'P', as well as a valid integer for max_iter (the number if iterations)
Postconditions: Output is an animation of max_iter number of simulations of Conway's Game of Life for the selected array initialization
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define ROW 20
#define COL 20

void
chooseArray (int array[ROW][COL], char choice);

int 
valid (int array[ROW][COL], int r, int c);

int 
checkn (int array[ROW][COL], int r, int c);

void
printIntro()
{
  printf ("Hello! Welcome to a simulation of Conway's Game of Life. This program will take a 20x20 grid of your choice and apply the rules of Conway's Game of Life to arrive at a final outcome.\n\n");
  printf ("For a randomly initialized pattern, enter 'R'\n");
  printf ("For a still life pattern, enter 'S'\n");
  printf ("For an oscillatory pattern, enter 'O'\n");
  printf ("For a spaceship pattern, enter 'P'\n");
}

int 
main ()
{
  char entry; // store user input
  int array[ROW][COL]; // array to store grid
  int neighbours[ROW][COL]; // array to store number of neighbours for each cell
  int max_iter; // store number of iterations

  printIntro(); // print introduction
  
  printf ("Enter your selection here: ");
  scanf ("%c", &entry);
  printf ("Enter the number of iterations here: ");
  scanf ("%d", &max_iter);

  chooseArray (array, entry); // choose appropriate array based on user input

 
  int iteration = 0;
  while (iteration < max_iter)
  {

    sleep(1);
    puts ("\033[H\033[J"); // clear screen

  
    for (int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < COL; c++)
      {
        if (array[r][c] == 1) // print gameboard
        printf (" X ");
        else printf (" - ");

        neighbours[r][c] = checkn (array, r, c); // check the neighbours of each element in the array
      }
    printf ("\n");
    }

    // edit subsequent array based on neighbours
    for (int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < COL; c++)
      {
        // live cell with 2 or 3 neighbours survives
        if ((array [r][c] == 1) && (neighbours[r][c] == 2 || neighbours[r][c] == 3)) 
        array [r][c] = 1;

        // every other live cell dies
        else if (array [r][c] == 1)
        array [r][c] = 0;

        // dead cell with 3 neighbours comes alive
        else if ((array [r][c] == 0) && (neighbours[r][c] == 3))
        array [r][c] = 1; 
      }
    }
    
    iteration++;
  }

  return 0;
}


//-----------------------------------------------------------------------

// function to choose an array initialization based on user input
void
chooseArray (int array[ROW][COL], char choice)
{
  srand((unsigned) time(NULL));  // seed rand() with the current time

  if (choice == 'R') // random array
  {
    int random = 0;
	  int div = 2;

    for (int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < COL; c++)
      {
        random = (rand() % div);  // mod the large number by the end of the range
        array[r][c] = random;
      }
    }
  }

  else if (choice == 'S') // still life array
  {
    for (int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < COL; c++)
      {
        array[r][c] = 0;
      }
    }
    array[8][9] = 1;
    array[8][10] = 1;
    array[10][9] = 1;
    array[10][10] = 1;
    array[9][8] = 1;
    array[9][11] = 1;
  }

  else if (choice == 'O') // oscillatory array 
  {
    for (int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < COL; c++)
      {
        if ((r == 9) && ((8 < c) && (c < 12)))
        array[r][c] = 1;
        else array[r][c] = 0;
      }
    }
  }

  else if (choice == 'P') // spaceship array
  {
    for (int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < COL; c++)
      {
        array[r][c] = 0;
      }
    }
    array[2][1] = 1;
    array[2][3] = 1;
    array[3][2] = 1;
    array[3][3] = 1;
    array[4][2] = 1;
  }
}

// function to check if a given cell is valid (exists)
int 
valid (int array[ROW][COL], int r, int c)
{
  if ((0 <= r) && (r < ROW) && (0 <= c) && (c < COL))
  {return 1;}

  else 
  {return 0;}
}

// function to check bounds and return the number of live neighbours for a given cell
int 
checkn (int array[ROW][COL], int r, int c)
{
  int up, down, left, right, uleft, uright, dleft, dright;

  if (valid (array, r-1, c)) 
  up = array[r-1][c];
  else up = 0;

  if (valid (array, r+1, c)) 
  down = array[r+1][c];
  else down = 0;

  if (valid (array, r, c-1)) 
  left = array[r][c-1];
  else left = 0;

  if (valid (array, r, c+1)) 
  right = array[r][c+1];
  else right = 0;

  if (valid (array, r-1, c-1))
  uleft = array[r-1][c-1];
  else uleft = 0;

  if (valid (array, r-1, c+1)) 
  uright = array[r-1][c+1];
  else uright = 0;

  if (valid (array, r+1, c-1)) 
  dleft = array[r+1][c-1];
  else dleft = 0;

  if (valid (array, r+1, c+1)) 
  dright = array[r+1][c+1];
  else dright = 0;
  
  int sum = up + down + left + right + uleft + uright + dleft + dright;

  return sum;
}
