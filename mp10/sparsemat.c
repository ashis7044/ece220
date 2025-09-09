#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
/* This program takes a sparse matrix from a text file and operates on it.
The load_tuples function takes the file, reads it, and creates a linked list
where each node represnts a non-zero cell in the matrix.*/
// The struct sp_tuples contains information about the number of columns and rows in the matrix, and the number of nonzero elements. It also has a pointer to the head of a sorted linked list called tuples_head. 


//still dont understand the relation between struct pointer and a tuples, linked list
sp_tuples * load_tuples(char* input_file)
{
FILE* fptr;
fptr = fopen(input_file, "r"); // Fixed: use input_file parameter instead of literal string

//sp_tuples *fptr this is not a file so u cant
// i want to pull out the data from the struct like dimensions of matrix and head of ll
if (fptr == NULL){ // check whether file is present or not
return NULL;} 

int rows, columns;
 fscanf(fptr, "%d %d", &rows, &columns); //gets dimensions if this is corect how do i know fscanf will scan rows and columns exactly outof all otther variable.
 sp_tuples * matrix= malloc(sizeof(sp_tuples)); //allocating memory for matrix what if we return void pointer


 //set parameters for matrix
 matrix->m=rows;
 matrix->n=columns;
 matrix->nz=0; 
 matrix->tuples_head=NULL; //LL is empty rn

   
 //traverse the file
 while(!feof(fptr)){  // feof will keep searching from start to finish... right? or is it just finish.
   double num;
     fscanf(fptr, "%d %d %lf\n", &rows, &columns, &num); //getting curr tuple //i aam confused with this line and next like like matrix is put in place of sp_tuples mat*
   set_tuples(matrix, rows, columns, num); //setting current tuple  
 }

fclose(fptr);
 return matrix;


}

  

//uptil now i successfully imported number of rows and columns

//i also want to import the matrix given by the file input_mat

// u need space to create matrix, do malloc(sizeof(???????)) care tutor is too vague... malloc to give space for matrix, now what comes inside, fptr? struct? input_matrix?, sparemat.c?

//lastly, close the file maybe fptr bcz i opened it in line 15? or is it input_mats bcz thats the fuile that i actuially opened? and return the matrix



//opens files could be any one of the matrix.txt i dk how struct is used instead of matrix.txt...
//RETURNS VALUE OF MATRIX, ROWS AND COLUMNS

//after done with above questions: initialize sp_tuples, it is like initializing registers at lc3 idea is move the pointer to the next linked list and initialize to NULL? or 0?

















double gv_tuples(sp_tuples * mat_t,int row,int col)




  {
    sp_tuples_node* current = mat_t->tuples_head;

    // Traverse the list until we reach the last node
    while(current != NULL){
        // if this node is the coordinate we want, return the value
        if (current->row == row && current->col == col) {
            return current->value;
        }
        // otherwise, move to the next node
        current = current->next;
    }
    // if we didn't find the right node, return 0
    return 0;
}



    ; // question says we want to access the value inside  the cell.
    //thats all the q says: but i learned from a caare tutor that, 
    //if no value, then we return 0, NULL?
    //IF THERE IS A VALUE, WE RETURN THAT CELL VALUE
//struct_node * temp = head

//struct sp_tuples_node * temp = haed sp tuples_node doesnt have a node so we have tpo do sp tuples

//struct sp_tuples_node * temp // where are you starting temp from?? // do i need to do malloc here ?
//struct sp_tuples_node * temp = mat_t->tuples_head; or sp_tuples ->tuples_head?? // we do ->tuples_head bcz we need to specify where yhe temp is located/starting at we cant do struct -> member we need to do struct pointer -> member

/*struct sp_tuples_node * temp = mat_t->tuples_head // we initialized the struct pointer to a specific matrix like mat1, matb depending on the user input

while(temp != NULL) // traverse ll to find the node whichever user asked for

  if(temp -> row(in struct) == row(arguement in function)  && temp -> col == col)//CHECK IF ROWS AND COLUMNS MATCH WITH THE ARGUEMENT ABOVE GIVEN IN FUNCTION INT ROW INT COL temp -> row == row lhs row is the row in the struct to see if it matches with the arguement in the function which is rhs row
//return sp_tuples_node (temp) -> value

    return temp -> value

    temp = temp -> next*/

// retruns row and column value according to the user, if user inputs matA, 1, 1  this function will return 4. function will go through all LL and finds the right one
//gv_tuples() will return 1(node 4) if i type 3,2


//return 0 or NULL ??// if we exit the loop and find none of the values... if it matters.



void set_tuples(sp_tuples * mat_t, int row, int col, double value) 
{
    // If value is 0, we need to remove the node if it exists
    if(value == 0){
        if(mat_t->tuples_head == NULL) return;
        
        sp_tuples_node * current = mat_t->tuples_head;
        
        // Check if first node is the one to delete
        if(current->row == row && current->col == col){
            mat_t->tuples_head = current->next;
            free(current);
            mat_t->nz--;
            return;
        }
        
        // Look for the node to delete
        while(current->next != NULL){
            if(current->next->row == row && current->next->col == col){
                sp_tuples_node * nodeToDelete = current->next;
                current->next = nodeToDelete->next;
                free(nodeToDelete);
                mat_t->nz--;
                return;
            }
            current = current->next;
        }
        return; // Node not found
    }
    
    // If list is empty, create first node
    if(mat_t->tuples_head == NULL){
        sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
        node->value = value;
        node->row = row;
        node->col = col;
        node->next = NULL;
        mat_t->tuples_head = node;
        mat_t->nz = 1;
        return;
    }
    
    // Check if we need to update existing node
    sp_tuples_node * current = mat_t->tuples_head;
    while(current != NULL){
        if(current->row == row && current->col == col){
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    // Add new node at the beginning (simple insertion)
    sp_tuples_node * node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    node->value = value;
    node->row = row;
    node->col = col;
    node->next = mat_t->tuples_head;
    mat_t->tuples_head = node;
    mat_t->nz++;
}


  //here, i am creating ll of non -0 tuples.
  /*struct sp_tuples_node * temp = mat_t->tuples_head
  while(temp != NULL)
  if (mat_t -> value == 0)
  temp = tuples_head   //SAVE tuples_head previous value into temp
  tuples_head = tuples_head -> next //move tuples head to point to next node.
  free(temp) //remove the previous node ex node1, now node 2 is pointed by head*/



//if value is 0, it will need to find the node at row and col if it exists, and delete it from the list. Be sure to free the nodes from memory or they will be lost forever.
//For any other value, the function will need to find the correct location for the node within the sorted linked list. If the entry already exists, the function should replace the old value. If the entry doesn't exist, a node should be created and inserted into the linked list.
//You also need to update the 'nz' variable of the struct. 
  /*if (value == 0)
  struct sp_tuples_node * temp = mat_t->tuples_head
  while(temp != NULL)
  if(row = )*/
   

/*if(mat_t -> tuples_head == NULL && value != 0){ //CHECK IF LL HEAD IS EMPTY OR NOT 
 struct sp_tuples_node *new = malloc(sizeof(sp_tuples_node)) 
 mat_t -> tuples_head = new // set the new head to the newly created node
 mat_t->nz += 1;


 new-> row = row
 new->col = col 
 new -> value = value
 new -> next = NULL
}

if (gv_tuples(mat_t, row, col) != 0) {
  Zif(value == 0){
        delete_node(mat_t, row, col);
        return;
    }
*/
//WE DO SOME ITERATION





 








void save_tuples(char * file_name, sp_tuples * mat_t)
{
    //open file for writing
   // FILE * file = NULL;
    FILE * file = fopen(file_name, "w");

    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);

    //int i;
    sp_tuples_node *current = mat_t->tuples_head;
    //for(i=0; i<mat_t->nz; i++){
    while (current != NULL) {
        fprintf(file, "%d %d %lf\n", current->row, current->col, current->value);
        current = current->next;
    }


    fclose(file);
	return;
}


sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){ //we want to add ll of matrix a and matrix b
if((matA->m != matB->m) || (matA->n != matB->n)) {
 return NULL;
}
sp_tuples * retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
 retmat->m = matA->m;
 retmat->n = matA->n;
 retmat->nz = 0;
 retmat->tuples_head = NULL;
 sp_tuples_node * current1 = matA->tuples_head;
while(current1 != NULL){
set_tuples(retmat, current1->row, current1->col, current1->value);
 current1 = current1->next;
}
current1 = matB->tuples_head;
 while(current1 != NULL){
set_tuples(retmat, current1->row, current1->col, current1->value +
gv_tuples(retmat, current1->row, current1->col));
 current1 = current1->next;
}
return retmat;
}




// sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
   // return retmat;


	
void destroy_tuples(sp_tuples * mat_t){
  sp_tuples_node* temp = mat_t->tuples_head;
  sp_tuples_node* next;
  while(temp!=NULL){
    next = temp->next;
    free(temp);
    temp = next;
  }
  free(mat_t); // Free the matrix struct itself
  return;
}

	

 

/* p = head->next
if p == NULL;
DELETE P*/






