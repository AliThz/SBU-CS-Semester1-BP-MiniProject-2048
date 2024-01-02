// LeaderBoard
// Player changing and talk to the player
// Random Access File

#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

using namespace std;

#define KB_1 49
#define KB_2 50
#define KB_3 51
#define KB_UpArrow 72
#define KB_DownArrow 80
#define KB_LeftArrow 75
#define KB_RightArrow 77
#define KB_ESC 27

void displayMenu();
void colorTile(int);
void generateNewBoard();
void generateBoard();
void generateBoardTable();
void makeMove();
void moveUp();
void mergeSimillarTilesUp();
void moveDown();
void mergeSimillarTilesDown();
void moveRight();
void mergeSimillarTilesRight();
void moveLeft();
void mergeSimillarTilesLeft();
bool checkIfFinished();
void anounceResult(bool);
void displayPauseMenu();
int generateRandomNumber();
void insertRandomNumber();
void displayLeaderBoard();
void exitBoard();

// const int boardSize = 4;
int *boardSizePtr;
int **board;
// int board[*boardSizePtr][*boardSizePtr] = {0};

int main()
{
    int boardSize;
    cin >> boardSize;
    boardSizePtr = &boardSize;

    board = new int *[*boardSizePtr];
    for (int i = 0; i < *boardSizePtr; i++)
        board[i] = new int[*boardSizePtr];

    // *boardSizePtr = 4;
    // cin >> *boardSizePtr;

    displayMenu();

    return 0;
}

void displayMenu()
{
    system("cls");
    cout << "--- 2048" << endl
         << "1 :  New board" << endl
         << "2 :  Leaderboard" << endl
         << "3 :  Exit" << endl;

    int command = getch();

    switch (command)
    {
    case KB_1:
        generateNewBoard();
        break;
    case KB_2:
        displayLeaderBoard();
        break;
    case KB_3:
        exitBoard();
        break;

    default:
        cout << "Invalid command!" << endl
             << "Please enter one of the commands above ...";

        Sleep(3000);

        displayMenu();
        break;
    }
}

void colorTile(int tile)
{
    switch (tile)
    {
    case 2:

        break;

    default:
        break;
    }
}

void generateNewBoard()
{
    for (int i = 0; i < *boardSizePtr; i++)
        for (int j = 0; j < *boardSizePtr; j++)
            board[i][j] = 0;

    insertRandomNumber();
    insertRandomNumber();
    generateBoard();
}

bool checkIfFinished()
{
    bool isFull = true;
    bool won = false;
    for (int i = 0; i < *boardSizePtr; i++)
    {
        for (int j = 0; j < *boardSizePtr; j++)
        {
            if (board[i][j] == 0)
            {
                isFull = false;
                return isFull;
            }

            if (board[i][j] == 2048)
            {
                won = true;
                isFull = true;
            }

            colorTile(board[i][j]);
        }
    }
    if (isFull)
        anounceResult(won);

    return isFull;
}

void generateBoard()
{
    generateBoardTable();
    if (!checkIfFinished())
        makeMove();
}

void generateBoardTable()
{
    system("cls");

    // --- First Line and Mid Lines
    for (int i = 0; i < 3 * (*boardSizePtr); i++)
    {
        if (i % 3 == 0)
        {
            cout << endl;
            if (i == 0)
                cout << "\u2554";
            else
                cout << "\u2560";

            for (int j = 1; j < 10 * (*boardSizePtr) + 1; j++)
            {
                if (j % 10 == 0)
                {
                    if (j == 10 * *boardSizePtr)
                    {
                        if (i == 0)
                            cout << "\u2557";
                        else
                            cout << "\u2563";

                        continue;
                    }

                    if (i == 0)
                        cout << "\u2566";
                    else
                        cout << "\u256C";

                    continue;
                }

                cout << "\u2550";
            }
        }
        cout << endl;

        for (int j = 1; j < 3 * (*boardSizePtr) + 4; j++)
        {
            if (j % 3 == 0)
            {
                if (j == 3 * *boardSizePtr + 3)
                {
                    cout << "\u2551"
                         << "         ";
                    continue;
                }

                int tileValue = board[((i - 1) / 3)][(j / 3) - 1];
                if ((i % 3 == 1) && tileValue != 0)
                    // cout << "\u2551" << setw(5) << 4 << "    ";
                    cout << "\u2551" << setw(5) << tileValue << "    ";
                // cout << "\u2551" << setw(5) << i << "*" << j << "    ";
                else
                    cout << "\u2551"
                         << "         ";
            }
        }
    }
    // ---

    // --- Last Line
    cout << endl
         << "\u255A";
    for (int i = 1; i < 10 * (*boardSizePtr); i++)
    {
        if (i % 10 == 0)
        {
            cout << "\u2569";
            continue;
        }
        cout << "\u2550";
    }
    cout << "\u255D";
    // ---
}

void makeMove()
{
    int move = getch();
    if (move == 224)
        move = getch();

    switch (move)
    {
    case KB_UpArrow:
        moveUp();
        break;
    case KB_DownArrow:
        moveDown();
        break;
    case KB_LeftArrow:
        moveLeft();
        break;
    case KB_RightArrow:
        moveRight();
        break;
    case KB_ESC:
        displayPauseMenu();
        break;
    default:
        cout << "Invalid move!";
        Sleep(500);
        generateBoard();
        break;
    }
}

void moveUp()
{
    for (int k = 0; k < *boardSizePtr - 1; k++)
    {
        for (int i = 0; i < *boardSizePtr - 1; i++)
            for (int j = 0; j < *boardSizePtr; j++)
                if (board[i][j] == 0)
                    swap(board[i][j], board[i + 1][j]);

        mergeSimillarTilesUp();
    }

    insertRandomNumber();
    generateBoard();
}

void mergeSimillarTilesUp()
{
    for (int j = 0; j < *boardSizePtr; j++)
    {
        for (int i = 0; i < *boardSizePtr - 1; i++)
        {
            if (board[i][j] == board[i + 1][j])
            {
                board[i][j] *= 2;
                board[i + 1][j] = 0;
            }
        }
    }
}

void moveDown()
{
    for (int k = 0; k < *boardSizePtr - 1; k++)
    {
        for (int i = *boardSizePtr - 1; i > 0; i--)
            for (int j = 0; j < *boardSizePtr; j++)
                if (board[i][j] == 0)
                    swap(board[i][j], board[i - 1][j]);

        mergeSimillarTilesDown();
    }
    insertRandomNumber();
    generateBoard();
}

void mergeSimillarTilesDown()
{
    for (int j = 0; j < *boardSizePtr; j++)
    {
        for (int i = *boardSizePtr - 1; i > 0; i--)
        {
            if (board[i][j] == board[i - 1][j])
            {
                board[i][j] *= 2;
                board[i - 1][j] = 0;
            }
        }
    }
}

void moveRight()
{
    for (int k = 0; k < *boardSizePtr - 1; k++)
    {
        for (int i = 0; i < *boardSizePtr; i++)
            for (int j = *boardSizePtr - 1; j > 0; j--)
                if (board[i][j] == 0)
                    swap(board[i][j], board[i][j - 1]);

        mergeSimillarTilesRight();
    }

    insertRandomNumber();
    generateBoard();
}

void mergeSimillarTilesRight()
{
    for (int i = 0; i < *boardSizePtr; i++)
    {
        for (int j = *boardSizePtr - 1; j > 0; j--)
        {
            if (board[i][j] == board[i][j - 1])
            {
                board[i][j] *= 2;
                board[i][j - 1] = 0;
            }
        }
    }
}

void moveLeft()
{
    for (int k = 0; k < *boardSizePtr - 1; k++)
    {
        for (int i = 0; i < *boardSizePtr; i++)
            for (int j = 1; j < *boardSizePtr; j++)
                if (board[i][j - 1] == 0)
                    swap(board[i][j - 1], board[i][j]);

        mergeSimillarTilesLeft();
    }

    insertRandomNumber();
    generateBoard();
}

void mergeSimillarTilesLeft()
{
    for (int i = 0; i < *boardSizePtr; i++)
    {
        for (int j = 0; j < *boardSizePtr - 1; j++)
        {
            if (board[i][j] == board[i][j + 1])
            {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
            }
        }
    }
}

void anounceResult(bool won)
{
    cout << "\n \n";
    if (won)
    {
        cout << "----- Winner ! -----";
    }
    else
    {
        cout << "----- board Over -----";
    }

    cout << "\n \n"
         << "1 :  Play Again" << endl
         << "2 :  Quit" << endl;

    int command = getch();
    switch (command)
    {
    case KB_1:
        generateNewBoard();
        break;
    case KB_2:
        displayMenu();
        break;

    default:
        cout << "Invalid Command";
        Sleep(500);
        displayPauseMenu();
        break;
    }
}

void displayPauseMenu()
{
    system("cls");
    cout << "--- Pause Room" << endl
         << "1 :  Resume" << endl
         << "2 :  Quit" << endl;

    int command = getch();
    switch (command)
    {
    case KB_1:
        generateBoard();
        break;
    case KB_2:
        displayMenu();
        break;

    default:
        cout << "Invalid Command";
        Sleep(1000);
        displayPauseMenu();
        break;
    }
}

int generateRandomNumber()
{
    // srand(time(0));
    int random = rand() % 4;
    if (random == 0)
        return 4;
    else
        return 2;
}

void insertRandomNumber()
{
    // srand(time(0));

    int randomNumber = generateRandomNumber();

    int randomTileI = rand() % *boardSizePtr;
    int randomTileJ = rand() % *boardSizePtr;

    if (board[randomTileI][randomTileJ] == 0)
        board[randomTileI][randomTileJ] = randomNumber;
    else
        insertRandomNumber();
}

void displayLeaderBoard()
{
    system("cls");
    cout << "Leader Board ";
}

void exitBoard()
{
    system("cls");
    cout << "Thanks for playing!";
    exit(0);
}