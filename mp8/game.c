#include "game.h"
// main asks for dimensions of board and set restrictions.     game * cur_game = make_game(rows,cols); //make new game entity called cur_game and insert the first random tile
/*
MP8 by Ashis Pandey
netid: Ashisp2
This program implements the game 2048 in the terminal.
 The program asks the user to input a board size and dynamically
 allocates memory to create a custom data struct to store the game
 state. The user may then press w,a,s,d to slide the 2048 tiles
 around; q to quit the game; or n to generate a fresh game. */

/* The game begins with a random value tile of either 2 or 4 placed
 * at a random location on the board. The player controls the game
 * using the direction keys w, a, s, and d. Whenever a direction is
 * pressed, all tiles will first slide in that direction for as far
 * as possible. As they slide, if two numbers of the same value
 * collide, they merge into a single tile whose value is the sum of
 * of the two values. The resulting tile cannot merge with another
 * tile again in the same move. Additionally, when sliding a row with
 * more than two like terms, merging occurs first based on the direction
 * of sliding. Finally, whenever a direction is pressed that results
 * in at least 1 tile changing position, a new random value tile of
 * either 2 or 4 placed at a random empty location on the board.
 * The score is shown at the top of the game.  Whenever 2 tiles merge,
 * their sum is added to the total score.
*/

game * make_game(int rows, int cols) //make game is a pointer
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame -> rows = rows; // overwrite any garbage into rows entered by user we want to use arrows instead of * because ....
  mygame -> cols = cols;
  mygame -> score = 0;
 

    int a;
      for(a = 0; a < rows*cols; a++){
	mygame -> cells [a] = -1; // i initially did cell[], but this is wrong becuase, just writing cell is not defined here, it is not a variable, it wont recognize it, so we cant even create new cell variable because we need to worry about pointers and stuff, to not violate the overall structure of the game. and it is not cell but its cells because cell is a value like 2, 4, 0,8.......
      }                 
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows;
	(*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)-> score = 0;

	int a;
      for(a = 0; a < new_rows*new_cols; a++){
	(*_cur_game_ptr) -> cells [a] = -1;
      }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
/*
{
    //YOUR CODE STARTS HERE return curr_game pointer to the specific cell, which pointer are we talking about, whats the difference between using else and without else.
  //for (i = 0; i< row; row++;){ // we dont wanna access any variables yet.
    if(i < 0 || i >= row){   //return num is when the cells dont have a number, thats when its out of bounds of game dimension matrix.
      return NULL;}
    
    for (i = 0; i < row; row++;)
        for(j = 0; j< col; col++;)

    pointer = &(cur_game->cells[i*col + j]); // it is like doing pointer = &cells[] [ ] is for which cell?, we wanna use curr_cell to specify board difference between pointer and cells which is also a pointer, it is like sub sub..... but idk why we do this why cant we just have cells as a pointer? why do we need to create a poointer?
    return pointer;
    
  
    //for (j = 0; j< col; col++;){
      if(j < 0 || j >= col){
	return NULL;
}
for (i = 0; i < row; row++;)
        for(j = 0; j< col; col++;)
    pointer = &(cur_game->cells[i*col+ j]);
    return pointer; */

{
	int rows, cols;

	rows = cur_game -> rows;
	cols = cur_game -> cols;
		
	cell *ptr;
	
	if(row < 0 || col < 0 || row*cols + col < 0 || row*cols + col >= rows*cols)
	{
		return NULL;
	}
	else
	{
		ptr = &(cur_game->cells[row*cols + col]);
		return ptr;
	}
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE does game*cur_game define row cols since we used cur game to point at a cell which has rows and columns...?


	
	int i, j, rows, cols;
	int flag = 0; //used to indicate if sliding has caused any values to change, tells if a key press was a valid move.

	rows = cur_game -> rows; // getting the game data now so we can reference values later.
	cols = cur_game -> cols;

	for(i = 0; i < cols; i++) //then loop through each cell to see if it can slide/merge
	{

		int l = -1; //initialises last combined row

		for(j = 1; j < rows; j++) //first spot doesn't need to be moved as it's already at the top
		{
			if(cur_game->cells[j*cols + i] != -1) 
			{
				int k = 0;
				
				while(k < j)
				{
					if(cur_game->cells[k*cols + i] == -1) // check if cell is empty
					{
						break;
					}
					k++;
				}

				if(k < j) //move values
				{
					cur_game->cells[k*cols + i] = cur_game->cells[j*cols + i]; // if two cells are equal, then they can be merged.
					cur_game->cells[j*cols + i] = -1; //clear the target cell
					flag = 1; 
				}

				if(k-1 != l)
				{
					if(cur_game->cells[(k-1)*cols + i] == cur_game->cells[k*cols + i])
					{
						cur_game->cells[(k-1)*cols + i] += cur_game->cells[k*cols + i];
						cur_game->cells[k*cols + i] = -1;   // resetting target cell
						cur_game->score += cur_game->cells[(k-1)*cols + i]; //add the combined value to the score, and set the cell moved flag
						l = k-1;   //// Update the last merged variable to prevent merging this cell again,
						flag = 1; // a cell has changed value
					} 
				} 
			}
		}
	}

	if(flag == 0) //If sliding the tiles up does not cause any cell to change value, w is an invalid move and return 0, is when flag remains 0
	{
		return 0;
	}
	else
	{
		return 1; // we have a legal move
	}

}

int move_s(game * cur_game) //slide down i will first do merging and sliding..
{
	int i, j, rows, cols;
	int flag = 0; //used to indicate if sliding has caused any values to change

	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for(i = 0; i < cols; i++)
	{

		int l = -1; //initialises last combined row

		for(j = rows-1; j >= 0; j--) 
		{
			if(cur_game->cells[j*cols + i] != -1)
			{
				int k = rows-1;
				
				while(k > j)
				{
					if(cur_game->cells[k*cols + i] == -1)
					{
						break;
					}
					k--;
				}

				if(k > j) //move stuff
				{
					cur_game->cells[k*cols + i] = cur_game->cells[j*cols + i];
					cur_game->cells[j*cols + i] = -1; //clear it
					flag = 1;
				}

				if(k+1 != l)
				{
					if(cur_game->cells[(k+1)*cols + i] == cur_game->cells[k*cols + i])
					{
						cur_game->cells[(k+1)*cols + i] += cur_game->cells[k*cols + i];
						cur_game->cells[k*cols + i] = -1;
						cur_game->score += cur_game->cells[(k+1)*cols + i];
						l = k+1;
						flag = 1; // a cell has changed value
					} 
				} 
			}
		}
	}

	if(flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int move_a(game * cur_game) //slide left
{
	int i, j, rows, cols;
	int flag = 0; //used to indicate if sliding has caused any values to change

	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for(i = 0; i < rows; i++)
	{

		int l = -1; //initialises last combined column

		for(j = 1; j < cols; j++) //first spot doesn't need to be moved as it's already in the left-most position
		{
			if(cur_game->cells[i*cols + j] != -1)
			{
				int k = 0;
				
				while(k < j)
				{
					if(cur_game->cells[i*cols + k] == -1)
					{
						break;
					}
					k++;
				}

				if(k < j) //move stuff
				{
					cur_game->cells[i*cols + k] = cur_game->cells[i*cols + j]; 
					cur_game->cells[i*cols + j] = -1; //clear it
					flag = 1;
				}

				if(k-1 != l) 
				{
					if(cur_game->cells[i*cols + (k-1)] == cur_game->cells[i*cols + k]) 
					{
						cur_game->cells[i*cols + (k-1)] += cur_game->cells[i*cols + k];
						cur_game->cells[i*cols + k] = -1;
						cur_game->score += cur_game->cells[i*cols + (k-1)];
						l = k-1;
						flag = 1; // a cell has changed value
					} 
				} 
			}
		}
	}

	if(flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

	int i, j, rows, cols;
	int flag = 0; //used to indicate if sliding has caused any values to change

	rows = cur_game -> rows;
	cols = cur_game -> cols;

	for(i = 0; i < rows; i++)
	{

		int l = -1; //initialises last combined column

		for(j = cols-1; j >= 0; j--) 
		{
			if(cur_game->cells[i*cols + j] != -1)
			{
				int k = cols-1;
				
				while(k > j)
				{
					if(cur_game->cells[i*cols + k] == -1)
					{
						break;
					}
					k--;
				}

				if(k > j) //move stuff
				{
					cur_game->cells[i*cols + k] = cur_game->cells[i*cols + j];
					cur_game->cells[i*cols + j] = -1; //clear it
					flag = 1;
				}

				if(k+1 != l)
				{
					if(cur_game->cells[i*cols + (k+1)] == cur_game->cells[i*cols + k])
					{
						cur_game->cells[i*cols + (k+1)] += cur_game->cells[i*cols + k];
						cur_game->cells[i*cols + k] = -1;
						cur_game->score += cur_game->cells[i*cols + (k+1)];
						l = k+1;
						flag = 1; // a cell has changed value
					} 
				} 
			}
		}
	}

	if(flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
   /* //YOUR CODE STARTS HERE   just call the wsad functions, if they cannot move, call return0
    int i, j, rows, cols;

    row = cur_game -> rows;
    cols = cur_game -> cols;

    for(i = 0; i < rows; i++)
        for(j = 0; j< cols; j++;)
        int value = get_cell(cur_game, i ,j){
if(value == -1 or NULL??){
    return 1;}

if(move_w()=1 || move_a()=1|| move_s()=1|| move_d()=1 ) // i cantdo this because it will change the board if there are moves left, we dont want this function to do that.if you want to do this  , you need to use deep copy of the board
  return 0;
 else{
   return 1; }*/


    
  
  /*
    int i, j, rows, cols;

    row = cur_game -> rows;
    cols = cur_game -> cols;

    for(i = 0; i < rows; i++)
        for(j = 0; j< cols; j++;)
        int value = get_cell(cur_game, i ,j){
if(value == -1 or NULL??){
    return 1;}
}
left = get_cell (cur_game, i-1, j)
right = get_cell (cur_game, i+1,j)
up = get_cell (cur_game, i, j+1)
down = get_cell (cur_game, i, j-1)

if(left == value || right == value || up == value|| down == value){
    return 0;
}
else{return 1;}*/
/*! code below is provided and should not be changed */


    int width = cur_game->cols;         // Get the game data now so we can reference the values
    int height = cur_game->rows;        // more easily later

    for (int y = 0; y < height; y ++) {
        for (int x = 0; x < width; x ++) {
            int value = *get_cell(cur_game, y, x);  // store the current cell's value for comparison

            // if the current cell is empty, there must be a legal move
            if (value == -1) {
                return 1;
            }

            // If any of the adjacet cells have the same value,
            // a merge is possible and a legal move remains.
            cell* left  = get_cell(cur_game, y, x - 1);     // Start by getting the addresses of each
            cell* right = get_cell(cur_game, y, x + 1);     //    adjacent cell, meaning the non- diagonals  If these are null,
            cell* up    = get_cell(cur_game, y - 1, x);     //    then the cell is out of bounds.
            cell* down  = get_cell(cur_game, y + 1, x);

            if (left != NULL && *left == value) {           // Assuming 'left' is valid, compare its value
                return 1;
            }
            if (right != NULL && *right == value) {         // Assuming 'right' is valid, compare its value
                return 1;
            }
            if (up != NULL && *up == value) {               // Assuming 'up' is valid, compare its value
                return 1;
            }
            if (down != NULL && *down == value) {           // Assuming 'down' is valid, compare its value
                return 1;
            }
        }
    }
    return 0;   // If we didn't return 1, then there are no legal moves remaining, so return 0
}



void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		break;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
        break;
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
