#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 10
#define HEIGHT 20

int board[WIDTH][HEIGHT] = {0};
int currentPiece[4][4] = {0};
int currentPieceX, currentPieceY, currentPieceRotation;

void drawBoard();
void drawPiece(int x, int y);
void erasePiece(int x, int y);
int checkCollision(int x, int y, int rotation);
void rotatePiece();
void movePiece(int direction);
void placePiece();
void clearLines();
void gameOver();

int main()
{
    int gameover = 0;
    int key;

    // Set up console
    system("cls");
    system("color 0F");
    CONSOLE_CURSOR_INFO cursor = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    // Game loop
    while (!gameover)
    {
        drawBoard();
        drawPiece(currentPieceX, currentPieceY);

        if (_kbhit())
        {
            key = _getch();
            erasePiece(currentPieceX, currentPieceY);

            switch (key)
            {
            case 'a':
                movePiece(-1);
                break;
            case 'd':
                movePiece(1);
                break;
            case 's':
                if (!checkCollision(currentPieceX, currentPieceY + 1, currentPieceRotation))
                    currentPieceY++;
                break;
            case 'w':
                rotatePiece();
                break;
            case 'q':
                gameover = 1;
                break;
            }
        }

        // Gravity
        if (!checkCollision(currentPieceX, currentPieceY + 1, currentPieceRotation))
            currentPieceY++;
        else
        {
            placePiece();
            clearLines();
            currentPieceX = WIDTH / 2 - 2;
            currentPieceY = 0;
            currentPieceRotation = 0;

            // Check for game over
            if (checkCollision(currentPieceX, currentPieceY, currentPieceRotation))
            {
                gameover = 1;
                gameOver();
            }
        }

        Sleep(100);
        system("cls");
    }

    return 0;
}

void drawBoard()
{
    int i, j;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            if (board[j][i] == 0)
                printf(" ");
            else
                printf("*");
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH; i++)
        printf("-");
    printf("\n");
}

void drawPiece(int x, int y)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (currentPiece[i][j] != 0)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void erasePiece(int x, int y)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (currentPiece[i][j] != 0)
                printf(" ");
        }
        printf("\n");
    }
}

int checkCollision(int x, int y, int rotation)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (currentPiece[i][j] != 0)
            {
                int newX = x + j;
                int newY = y + i;

                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && board[newX][newY] != 0))
                    return 1;
            }
        }
    }

    return 0;
}

void rotatePiece()
{
    erasePiece(currentPieceX, currentPieceY);

    // Save the current piece state
    int tempPiece[4][4];
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tempPiece[i][j] = currentPiece[i][j];
        }
    }

    // Rotate the piece
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            currentPiece[i][j] = tempPiece[3 - j][i];
        }
    }

    // Check for collisions with the new rotation
    if (checkCollision(currentPieceX, currentPieceY, currentPieceRotation))
    {
        // Restore the original piece state if there's a collision
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                currentPiece[i][j] = tempPiece[i][j];
            }
        }
    }
    else
    {
        // Update the rotation if there's no collision
        currentPieceRotation = (currentPieceRotation + 1) % 4;
    }
}

void movePiece(int direction)
{
    erasePiece(currentPieceX, currentPieceY);

    if (!checkCollision(currentPieceX + direction, currentPieceY, currentPieceRotation))
        currentPieceX += direction;
}

void placePiece()
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (currentPiece[i][j] != 0 && currentPieceY + i >= 0)
                board[currentPieceX + j][currentPieceY + i] = 1;
        }
    }
}

void clearLines()
{
    int i, j;
    int linesCleared = 0;

    for (i = HEIGHT - 1; i >= 0; i--)
    {
        int lineComplete = 1;
        for (j = 0; j < WIDTH; j++)
        {
            if (board[j][i] == 0)
            {
                lineComplete = 0;
                break;
            }
        }

        if (lineComplete)
        {
            // Clear the line
            for (j = 0; j < WIDTH; j++)
            {
                board[j][i] = 0;
            }

            // Move lines above down
            for (int k = i; k > 0; k--)
            {
                for (j = 0; j < WIDTH; j++)
                {
                    board[j][k] = board[j][k - 1];
                }
            }

            linesCleared++;
            i++; // Recheck the same line since it has been shifted down
        }
    }

    // Update score or perform other actions based on lines cleared
}

void gameOver()
{
    // Implement game over message and cleanup here
    printf("Game Over!\n");
    system("pause");
}
