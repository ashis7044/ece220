#include "sudoku.h"

/* Intro Paragraph: In this MP, we need to implement sudoku game on a 9x9 standard board using recursive backtracking method. Wecan use numbers from 1-9 to fill in an unfilled location at the board, the three restrictions for it to be allowed to be placed in a  board is same number cannot be appeared in row, column and 3x3 matrix it belongs to. These are used as helper functions to check if the entered number in the cell is valid to be placed or not.  */
// Ashisp2, 668368464

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.
//main function already declares sudoku[9][9]
// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int j;//declare the iteration variable
  for(j = 0; j < 9; j++)
  {
    if(sudoku[i][j] == val)//check the value on the same row, if found, then return 0, losing sudoku
    {
      return 1; // not 0 because, function says return if there is value in row? yes if condition satisfies
    }
  }
  return 0; 
  // BEG TODO
    // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
    int i;//declare the iteration variable
  for(i = 0; i < 9; i++)
  {
    if(sudoku[i][j] == val)
    {
      return 1;//check the value on the same col, if found, then return 1
    }
  }
  return 0;//if not, return 0
  // END TODO
}
  // END TODO


// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
 
  int row, column; //I used i/3 *3 in order to restrict entered cell to be checked under  address of 3 by 3 matrix.  looping of i and j from 1 to 9 will b done by sudoku_solve
     for(row=(i/3)*3;   row < (i/3)*3+3;row++){

       
       //r(i=0; i<9, i++)
	for(column=(j/3)*3   ; column < (j/3)*3+3;column++){
	    

	  if(sudoku[row][column] == val){
	    return 1;}
	}
      }
     return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9); // restricts sudoku game to 9 by 9
  int x, y, z;

  x = is_val_in_row(val, i ,sudoku);
  y =is_val_in_col(val, j, sudoku);
  z =is_val_in_3x3_zone(val, i, j, sudoku);

  if(x == 0 && y == 0 && z == 0){   // if all variable return 0, that means number cannot be placed into the cell.
      
  // BEG TODO
      return 1;}
    else{return 0;
  // END TODO
}
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
    int solve_sudoku(int sudoku[9][9]) { //length max of sudoku lets first look for unfilled cell here which contains 0, if you find it then assign the matrix dimentions to i and j, otherwise, return 1.
          int i=-1;
         int j = -1;
         int found = 0;

  for(int a = 0; a< 9 && !found; a++){
    for(int b = 0; b< 9 && !found; b++){
      if(sudoku[a][b] == 0){// if you find any empty cell to be filled in sudoku when starting a game, retun 0, if you find it, then return 1
	i = a;
	j = b;
        found = 1; // Mark that we found an empty cell
	  }// if (cell (i, j) can be filled with num) 
    }
   
  }
  if(i ==-1 || j == -1){ //u dont need curly bracket for just one statement
    return 1;
  }
  for (int num = 1; num < 10; num++){
    int w = is_val_valid(num, i, j, sudoku); // we use helper function here and if the return value is 1, we know that number can be placed on the board.
    if (w == 1){   
      sudoku[i][j] = num;
      if(solve_sudoku(sudoku)==1){    // helper function here to do the backtracking.
	return 1;
      }
      sudoku[i][j] = 0;
    }
    
  }
  return 0;
    }
   



// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





