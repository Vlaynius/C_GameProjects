#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 52
#define PLAYER_COUNT 4

// Function to roll a die and return a random number between 1 and 6
int rollDie() {
    return rand() % 6 + 1;
}

// Function to display the current state of the board
void displayBoard(int board[], int players[]) {
    printf("\nCurrent Board:\n");
    printf("_____________________\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (i % 13 == 0) {
            printf("\n");
        }

        if (i % 13 == 0 && i < 39) {
            printf("|");
        }

        if (i % 13 == 0 && i >= 39) {
            printf("_____________________\n");
        }

        if (i == 0 || i == 12 || i == 39 || i == 51) {
            printf("|");
        }

        if (board[i] == -1) {
            printf("  ");
        } else {
            printf("%d ", board[i]);
        }

        if (i == 12 || i == 25 || i == 38) {
            printf("|");
        }
    }
    printf("\n");

    printf("\nPlayer Positions:\n");
    for (int i = 0; i < PLAYER_COUNT; i++) {
        printf("Player %d: %d  ", i + 1, players[i]);
    }
    printf("\n");
}

// Function to update player positions based on the dice roll
void movePlayer(int board[], int players[], int player, int dice) {
    int currentPosition = players[player - 1];

    // Move the player on the board
    board[currentPosition] = -1;
    currentPosition += dice;

    // Check for the completion of a round and update player positions accordingly
    if (currentPosition >= BOARD_SIZE) {
        currentPosition -= BOARD_SIZE;
    }

    // Update the player position on the board
    players[player - 1] = currentPosition;
    board[currentPosition] = player;
}

int main() {
    srand(time(NULL));

    // Initialize the board and player positions
    int board[BOARD_SIZE];
    int players[PLAYER_COUNT];

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = -1;
    }

    // Starting positions for each player
    for (int i = 0; i < PLAYER_COUNT; i++) {
        players[i] = i * (BOARD_SIZE / PLAYER_COUNT);
    }

    // Main game loop
    while (1) {
        // Display the board
        displayBoard(board, players);

        // Simulate dice roll
        printf("\nPress Enter to roll the die...\n");
        getchar();
        int dice = rollDie();
        printf("You rolled a %d!\n", dice);

        // Move the current player
        int currentPlayer = 1; // For simplicity, assuming a two-player game
        movePlayer(board, players, currentPlayer, dice);

        // Check for a winner (assuming one lap around the board is a win)
        if (players[currentPlayer - 1] >= BOARD_SIZE) {
            printf("\nPlayer %d wins!\n", currentPlayer);
            break;
        }

        // Switch to the next player
        currentPlayer = (currentPlayer % PLAYER_COUNT) + 1;
    }

    return 0;
}

