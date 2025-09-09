#include "sudoku.h"

// Function to validate a completed sudoku solution
int validate_sudoku(int sudoku[9][9]) {
    // Check rows
    for (int i = 0; i < 9; i++) {
        int used[10] = {0}; // index 0 unused, 1-9 for numbers 1-9
        for (int j = 0; j < 9; j++) {
            int num = sudoku[i][j];
            if (num < 1 || num > 9 || used[num]) {
                printf("Invalid row %d\n", i + 1);
                return 0;
            }
            used[num] = 1;
        }
    }
    
    // Check columns
    for (int j = 0; j < 9; j++) {
        int used[10] = {0};
        for (int i = 0; i < 9; i++) {
            int num = sudoku[i][j];
            if (num < 1 || num > 9 || used[num]) {
                printf("Invalid column %d\n", j + 1);
                return 0;
            }
            used[num] = 1;
        }
    }
    
    // Check 3x3 boxes
    for (int box_row = 0; box_row < 3; box_row++) {
        for (int box_col = 0; box_col < 3; box_col++) {
            int used[10] = {0};
            for (int i = box_row * 3; i < box_row * 3 + 3; i++) {
                for (int j = box_col * 3; j < box_col * 3 + 3; j++) {
                    int num = sudoku[i][j];
                    if (num < 1 || num > 9 || used[num]) {
                        printf("Invalid 3x3 box at (%d,%d)\n", box_row + 1, box_col + 1);
                        return 0;
                    }
                    used[num] = 1;
                }
            }
        }
    }
    
    printf("Sudoku solution is VALID!\n");
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./validate sudoku_solution.txt\n");
        return 1;
    }
    
    int sudoku[9][9];
    parse_sudoku(argv[1], sudoku);
    
    printf("Validating sudoku solution:\n");
    print_sudoku(sudoku);
    printf("\n");
    
    validate_sudoku(sudoku);
    
    return 0;
}
