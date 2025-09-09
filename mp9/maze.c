#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
// first we want to create a struct and assign parameters by importing txt files from different maze files given, we need to open that to store all the character data. Make sure to close to avoid memory leaks 
maze_t * createMaze(char * fileName) 
{
    int x;
    FILE*mazefile;
    mazefile = fopen(fileName, "r");
    
    if (mazefile == NULL) {
        printf("Error: Could not open file %s\n", fileName);
        return NULL;
    }

    maze_t * mazeptr =  malloc(sizeof(maze_t));
    if (mazeptr == NULL) {
        fclose(mazefile);
        return NULL;
    }
    
    fscanf(mazefile, "%d %d\n", &(mazeptr -> width), &(mazeptr->height));
    
    mazeptr->cells = (char**)malloc(mazeptr->height*sizeof(char*));
    for(x = 0; x< mazeptr->height; x++){
            mazeptr->cells[x] = (char*)malloc(mazeptr->width*sizeof(char));
    }

    //fileName = fopen("maze1.txt, maze2.txt, maze3.txt, maze4.txt", "r"); file name contains maze1.txt
    
    // Your code here. Make sure to replace following line with your own code. 
    char c;
    int i,j;
    for (i = 0; i < mazeptr->height; i++)
    {
        for (j = 0; j < mazeptr->width; j++)
        {
            c = fgetc(mazefile);
            
            // Skip newline characters
            if(c == '\n') {
                c = fgetc(mazefile);
            }
            
            mazeptr->cells[i][j] = c; //fill in the cells

            if(mazeptr->cells[i][j] == 'S') //identify start position
            {
                mazeptr->startColumn = j; 
                mazeptr->startRow = i;
            }
            if(mazeptr->cells[i][j] == 'E') //identify end position
            {
                mazeptr->endColumn = j;
                mazeptr->endRow = i;
            }
        }
        // Skip the newline at the end of each row
        if (i < mazeptr->height - 1) {
            fgetc(mazefile);
        }
    }

	fclose(mazefile);	
	
	return mazeptr;
	
    /*if(mazeptr == NULL){ //to keep track of whether memory allocation workbeing detected
        printf("invalid, maze allocation didnt work");
    return NULL;
}}*/
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int x;

    for(x= 0; x < maze->height; x++){
free(maze ->cells[x]); // Your code here.
}

free(maze->cells);
free(maze);}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i;
    int j;

    for(i= 0; i < maze->height; i++)
{for(j = 0; j < maze->width; j++ ){  // print each cell value in row major style
    printf("%c", maze->cells[i][j]);
} 
printf("\n");
}}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
     if (col<0 || row<0 || row>=maze->height || col>=maze->width){ //check if the maze is outside of range
        return 0;
    }
    if (maze->cells[row][col]!='S' && maze->cells[row][col]!='E'){ //check if we at the start or the end
        if (maze->cells[row][col]!= ' '){ //return false if not empty
            return 0;
        }
    }

    if (maze->cells[row][col]=='E'){ //if we have reached the end, we done
        maze->cells[maze->startRow][maze->startColumn]='S';//restore starting position
        return 1;
    }

    maze->cells[row][col]='*'; //mark location as part of solution
    
    

    if (solveMazeDFS(maze, col-1, row)){
        return 1;
    }
    if (solveMazeDFS(maze, col+1, row)){
        return 1;
    }
    if (solveMazeDFS(maze, col, row+1)){
        return 1;
    }
    if (solveMazeDFS(maze, col, row-1)){
        return 1;
    }
    
    maze->cells[row][col]='~'; //mark as visited
    
    
    return 0;
}
