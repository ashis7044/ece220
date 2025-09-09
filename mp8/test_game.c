#include "game.h"
#include <time.h>

// Simple test program to check the game logic without getch functionality
int main() {
    printf("Testing 2048 Game Logic\n");
    printf("======================\n");
    
    // Initialize random seed
    srand(time(NULL));
    
    // Create a 4x4 game
    game* test_game = make_game(4, 4);
    if (test_game == NULL) {
        printf("Failed to create game\n");
        return 1;
    }
    
    printf("Created 4x4 game\n");
    printf("Initial score: %d\n", test_game->score);
    
    // Add first tile
    rand_new_tile(test_game);
    printf("Added first random tile\n");
    
    // Print the game state
    print_game(test_game);
    
    // Test some moves
    printf("\nTesting move_w (up):\n");
    int result = move_w(test_game);
    printf("Move result: %d\n", result);
    
    if (result == 1) {
        rand_new_tile(test_game);
        print_game(test_game);
    }
    
    printf("\nTesting legal_move_check:\n");
    int legal = legal_move_check(test_game);
    printf("Legal moves available: %d\n", legal);
    
    // Clean up
    destroy_game(test_game);
    printf("Game destroyed successfully\n");
    
    return 0;
}
