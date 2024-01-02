#include <iostream>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>

using namespace std;

#define KB_1 49
#define KB_2 50
#define KB_3 51
#define KB_UpArrow 72
#define KB_DownArrow 80
#define KB_LeftArrow 75
#define KB_RightArrow 77
#define KB_ESC 27

// Console Text Color
const string RESET_COLOR = "\033[0m";
const string BLACK_COLOR = "\033[30m";
const string RED_COLOR = "\033[31m";
const string GREEN_COLOR = "\033[32m";
const string YELLOW_COLOR = "\033[33m";
const string BLUE_COLOR = "\033[34m";
const string PURPLE_COLOR = "\033[35m";
const string CYAN_COLOR = "\033[36m";
const string WHITE_COLOR = "\033[37m";

// Console Background Color
const string RESET_BGCOLOR = "\033[0m";
const string BLACK_BGCOLOR = "\033[40m";
const string RED_BGCOLOR = "\033[41m";
const string GREEN_BGCOLOR = "\033[42m";
const string YELLOW_BGCOLOR = "\033[43m";
const string BLUE_BGCOLOR = "\033[44m";
const string PURPLE_BGCOLOR = "\033[45m";
const string CYAN_BGCOLOR = "\033[46m";
const string WHITE_BGCOLOR = "\033[47m";

// Console Text Style
const string BOLDON_STYLE = "\033[1m";
const string BOLDOFF_STYLE = "\033[22m";

struct Game
{
    string playerName;
    int boardSize;
    int **board;
    int score;
};

void generateBoard();
void displayMenu();
string colorTile(int);
void generateNewGame();
bool checkIfFinished();
void displayBoard();
void displayBoardTable();
void makeMove();
void moveUp();
void mergeSimillarTilesUp(bool &);
void moveDown();
void mergeSimillarTilesDown(bool &);
void moveRight();
void mergeSimillarTilesRight(bool &);
void moveLeft();
void mergeSimillarTilesLeft(bool &);
void saveData();
bool checkIfAnyMovesLeft();
bool checkIfFinished();
void anounceResult(bool);
void displayPauseMenu();
int generateRandomNumber();
void insertRandomNumber();
void fetchData();
void displayLeaderBoard();
void ShowConsoleCursor(bool);
void deletePointers();
void exitBoard();

Game *game;

int main()
{
    displayMenu();

    return 0;
}

void getPlayerInformation()
{
    cout << BLUE_COLOR << "Enter Your Name : ";
    cin >> (*game).playerName;
}

void generateBoard()
{
    cout << BLUE_COLOR << "Enter board size : ";
    cin >> (*game).boardSize;
    cout << RESET_COLOR;

    if (cin.fail())
    {
        cerr << RED_COLOR << "Please enter a number" << RESET_COLOR << endl;
        Sleep(500);
        cin.clear();
        cin.ignore(256, '\n');
        generateBoard();
    }
    else if ((*game).boardSize < 2)
    {
        cout << RED_COLOR << "Please enter a bigger size" << RESET_COLOR << endl;
        Sleep(500);
        generateBoard();
    }

    (*game).board = new int *[(*game).boardSize];
    for (int i = 0; i < (*game).boardSize; i++)
        (*game).board[i] = new int[(*game).boardSize];
}

void displayMenu()
{
    system("cls");
    ShowConsoleCursor(false);

    cout << BOLDON_STYLE << GREEN_COLOR << "---  2 0 4 8  ---" << RESET_COLOR << BOLDOFF_STYLE << endl
         << BLUE_COLOR
         << "1 :  New Game" << endl
         << "2 :  Leaderboard" << endl
         << "3 :  Exit" << endl
         << RESET_COLOR;

    int command = getch();

    switch (command)
    {
    case KB_1:
        generateNewGame();
        break;
    case KB_2:
        displayLeaderBoard();
        break;
    case KB_3:
        exitBoard();
        break;

    default:
        cout << RED_COLOR << "Invalid command!" << endl
             << "Please enter one of the commands above ..." << RESET_COLOR;

        Sleep(1000);

        displayMenu();
        break;
    }
}

string colorTile(int tile)
{
    switch (tile)
    {
    case 2:
        return WHITE_COLOR;
        break;
    case 4:
        return WHITE_COLOR;
        break;
    case 8:
        return YELLOW_COLOR;
        break;
    case 16:
        return PURPLE_COLOR;
        break;
    case 32:
        return RED_COLOR;
        break;
    case 64:
        return CYAN_COLOR;
        break;
    case 128:
        return CYAN_COLOR;
        break;
    case 256:
        return BLUE_COLOR;
        break;
    case 512:
        return BLUE_COLOR;
        break;
    case 1024:
        return GREEN_COLOR;
        break;
    case 2048:
        return GREEN_COLOR;
        break;

    default:
        return BLUE_COLOR;
        break;
    }
}

void generateNewGame()
{
    system("cls");
    game = new Game;
    getPlayerInformation();
    generateBoard();
    (*game).score = 0;

    for (int i = 0; i < (*game).boardSize; i++)
        for (int j = 0; j < (*game).boardSize; j++)
            (*game).board[i][j] = 0;

    for (int i = 0; i < ((*game).boardSize) / 2; i++)
        insertRandomNumber();

    displayBoard();
}

bool checkIfAnyMovesLeft()
{
    for (int j = 0; j < (*game).boardSize; j++)
        for (int i = 0; i < (*game).boardSize - 1; i++)
            if ((*game).board[i][j] == (*game).board[i + 1][j])
                return true;

    for (int j = 0; j < (*game).boardSize; j++)
        for (int i = (*game).boardSize - 1; i > 0; i--)
            if ((*game).board[i][j] == (*game).board[i - 1][j])
                return true;

    for (int i = 0; i < (*game).boardSize; i++)
        for (int j = (*game).boardSize - 1; j > 0; j--)
            if ((*game).board[i][j] == (*game).board[i][j - 1])
                return true;

    for (int i = 0; i < (*game).boardSize; i++)
        for (int j = 0; j < (*game).boardSize - 1; j++)
            if ((*game).board[i][j] == (*game).board[i][j + 1])
                return true;

    return false;
}

bool checkIfBoardIsFull()
{
    for (int i = 0; i < (*game).boardSize; i++)
        for (int j = 0; j < (*game).boardSize; j++)
            if ((*game).board[i][j] == 0)
                return false;

    return true;
}

bool checkIfFinished()
{
    bool won = false;

    if (!checkIfBoardIsFull())
        return false;

    for (int i = 0; i < (*game).boardSize; i++)
        for (int j = 0; j < (*game).boardSize; j++)
            if ((*game).board[i][j] == 2048)
                won = true;

    bool isFinished = checkIfBoardIsFull() && !checkIfAnyMovesLeft();

    if (isFinished)
        anounceResult(won);

    return isFinished;
}

void displayBoard()
{
    system("cls");

    cout << GREEN_COLOR << (*game).playerName << endl
         << "Score :  " << (*game).score << RESET_COLOR;

    cout << BLUE_COLOR;
    displayBoardTable();
    cout << RESET_COLOR;

    cout << endl
         << GREEN_COLOR << "Press escape to pause the game" << RESET_COLOR;

    if (!checkIfFinished())
        makeMove();
}

void displayBoardTable()
{
    // --- First Line and Mid Lines
    for (int i = 0; i < 3 * ((*game).boardSize); i++)
    {
        if (i % 3 == 0)
        {
            cout << endl;
            if (i == 0)
                cout << "\u2554";
            else
                cout << "\u2560";

            for (int j = 1; j < 10 * ((*game).boardSize) + 1; j++)
            {
                if (j % 10 == 0)
                {
                    if (j == 10 * ((*game).boardSize))
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

        for (int j = 1; j < 3 * ((*game).boardSize) + 4; j++)
        {
            if (j % 3 == 0)
            {
                if (j == 3 * ((*game).boardSize) + 3)
                {
                    cout << "\u2551"
                         << "         ";
                    continue;
                }

                int tileValue = (*game).board[((i - 1) / 3)][(j / 3) - 1];
                if ((i % 3 == 1) && tileValue != 0)
                    cout << "\u2551" << colorTile(tileValue) << setw(5) << tileValue << BLUE_COLOR << "    ";
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
    for (int i = 1; i < 10 * ((*game).boardSize); i++)
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
        cout << RED_COLOR << "Invalid move!" << RESET_COLOR;
        Sleep(500);
        displayBoard();
        break;
    }
}

void moveUp()
{
    bool flag = true;

    for (int k = 0; k < (*game).boardSize - 1; k++)
    {
        for (int i = 0; i < (*game).boardSize - 1; i++)
            for (int j = 0; j < (*game).boardSize; j++)
                if ((*game).board[i][j] == 0)
                    swap((*game).board[i][j], (*game).board[i + 1][j]);

        if (flag)
            mergeSimillarTilesUp(flag);
    }

    if (!checkIfBoardIsFull())
        insertRandomNumber();

    displayBoard();
}

void mergeSimillarTilesUp(bool &flag)
{
    for (int j = 0; j < (*game).boardSize; j++)
    {
        for (int i = 0; i < (*game).boardSize - 1; i++)
        {
            if ((*game).board[i][j] == (*game).board[i + 1][j])
            {
                flag = false;
                flag = true;
                (*game).board[i][j] *= 2;
                (*game).board[i + 1][j] = 0;
                (*game).score += (*game).board[i][j];
            }
        }
    }
}

void moveDown()
{
    bool flag = true;

    for (int k = 0; k < (*game).boardSize - 1; k++)
    {
        for (int i = (*game).boardSize - 1; i > 0; i--)
            for (int j = 0; j < (*game).boardSize; j++)
                if ((*game).board[i][j] == 0)
                    swap((*game).board[i][j], (*game).board[i - 1][j]);

        if (flag)
            mergeSimillarTilesDown(flag);
    }
    if (!checkIfBoardIsFull())

        insertRandomNumber();

    displayBoard();
}

void mergeSimillarTilesDown(bool &flag)
{
    for (int j = 0; j < (*game).boardSize; j++)
    {
        for (int i = (*game).boardSize - 1; i > 0; i--)
        {
            if ((*game).board[i][j] == (*game).board[i - 1][j])
            {
                flag = false;
                (*game).board[i][j] *= 2;
                (*game).board[i - 1][j] = 0;
                (*game).score += (*game).board[i][j];
            }
        }
    }
}

void moveRight()
{
    bool flag = true;

    for (int k = 0; k < (*game).boardSize - 1; k++)
    {
        for (int i = 0; i < (*game).boardSize; i++)
            for (int j = (*game).boardSize - 1; j > 0; j--)
                if ((*game).board[i][j] == 0)
                    swap((*game).board[i][j], (*game).board[i][j - 1]);

        if (flag)
            mergeSimillarTilesRight(flag);
    }

    if (!checkIfBoardIsFull())
        insertRandomNumber();

    displayBoard();
}

void mergeSimillarTilesRight(bool &flag)
{
    for (int i = 0; i < (*game).boardSize; i++)
    {
        for (int j = (*game).boardSize - 1; j > 0; j--)
        {
            if ((*game).board[i][j] == (*game).board[i][j - 1])
            {
                flag = false;
                (*game).board[i][j] *= 2;
                (*game).board[i][j - 1] = 0;
                (*game).score += (*game).board[i][j];
            }
        }
    }
}

void moveLeft()
{
    bool flag = true;

    for (int k = 0; k < (*game).boardSize - 1; k++)
    {
        for (int i = 0; i < (*game).boardSize; i++)
            for (int j = 1; j < (*game).boardSize; j++)
                if ((*game).board[i][j - 1] == 0)
                    swap((*game).board[i][j - 1], (*game).board[i][j]);

        if (flag)
            mergeSimillarTilesLeft(flag);
    }

    if (!checkIfBoardIsFull())
        insertRandomNumber();

    displayBoard();
}

void mergeSimillarTilesLeft(bool &flag)
{
    for (int i = 0; i < (*game).boardSize; i++)
    {
        for (int j = 0; j < (*game).boardSize - 1; j++)
        {
            if ((*game).board[i][j] == (*game).board[i][j + 1])
            {
                flag = false;
                (*game).board[i][j] *= 2;
                (*game).board[i][j + 1] = 0;
                (*game).score += (*game).board[i][j];
            }
        }
    }
}

void saveData()
{
    ofstream file("LeaderBoard.txt", ios::app);
    if (file.is_open())
    {
        file << (*game).score << " - " << (*game).playerName << " - " << (*game).boardSize << "\n";
        file.close();
        deletePointers();
    }
    else
    {
        cerr << endl
             << "Unable to open the file." << endl;
    }
}

void anounceResult(bool won)
{
    cout << "\n \n";
    if (won)
        cout << BOLDON_STYLE << GREEN_BGCOLOR << "----- Winner ! -----" << RESET_COLOR << BOLDOFF_STYLE;
    else
        cout << BOLDON_STYLE << RED_BGCOLOR << "----- Game Over -----" << RESET_COLOR << BOLDOFF_STYLE;

    cout << "\n \n"
         << "1 :  Play Again" << endl
         << "2 :  Quit" << endl;

    cout << BLUE_COLOR;
    int command = getch();
    switch (command)
    {
    case KB_1:
        saveData();
        generateNewGame();
        break;
    case KB_2:
        saveData();
        displayMenu();
        break;

    default:
        cout << RED_COLOR << "Invalid Command" << RESET_COLOR;
        Sleep(500);
        displayBoard();
        break;
    }
    cout << RESET_COLOR;
}

void displayPauseMenu()
{
    system("cls");
    cout << BOLDON_STYLE << YELLOW_COLOR << "--- Pause Room" << RESET_COLOR << BOLDOFF_STYLE << endl
         << WHITE_COLOR
         << "1 :  Resume" << endl
         << "2 :  Quit" << endl;

    int command = getch();
    switch (command)
    {
    case KB_1:
        displayBoard();
        break;
    case KB_2:
        displayMenu();
        break;

    default:
        cout << RED_COLOR << "Invalid Command" << RESET_COLOR;
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

    int randomTileI = rand() % (*game).boardSize;
    int randomTileJ = rand() % (*game).boardSize;

    if ((*game).board[randomTileI][randomTileJ] == 0)
        (*game).board[randomTileI][randomTileJ] = randomNumber;
    else
        insertRandomNumber();
}

void fetchData()
{
    ifstream file("LeaderBoard.txt");
    if (file.is_open())
    {
        string line, word;
        int l = 0;
        while (getline(file, line))
            l++;

        file.clear();
        file.seekg(0);

        Game games[l];

        int i = 0;
        while (getline(file, line))
        {
            int j = 0;
            while (file >> word)
            {
                if (word == "-")
                    continue;
                switch (j)
                {
                case 0:
                    games[i].score = stoi(word);
                    break;
                case 1:
                    games[i].playerName = word;
                    break;
                case 2:
                    games[i].boardSize = stoi(word);
                    break;
                }
                if (j == 2)
                    break;

                j++;
            }
            i++;

            // cout << "File read and printed successfully." << endl;
        }

        sort(games, games + sizeof(games) / sizeof(games[0]), [](const Game &game1, const Game &game2)
             {
                int result = 0;
                if (game2.score < game1.score)
                    result = 1;
                return result; });

        cout << GREEN_COLOR
             << setw(8) << left << "Rank" << setw(8)
             << "  |  "
             << setw(8) << left << "Score" << setw(8)
             << "  |  "
             << setw(8) << left << "Name" << setw(8)
             << "  |  "
             << setw(8) << left << "Board Size" << setw(8) << RESET_COLOR << endl;

        for (int i = 0; i < l - 1; i++)
            cout << BLUE_COLOR
                 << setw(8) << left << i + 1 << setw(8) << "  |  "
                 << setw(8) << left << games[i].score << setw(8) << "  |  "
                 << setw(8) << left << games[i].playerName << setw(8) << "  |  "
                 << setw(8) << left << games[i].boardSize << setw(8) << RESET_COLOR << endl;

        file.close();
    }
    else
    {
        cout << endl
             << RED_COLOR << "Unable to open the file." << RESET_COLOR << endl;
    }
}

void displayLeaderBoard()
{
    system("cls");
    cout << BOLDON_STYLE << GREEN_COLOR << "-- Leader Board \n\n"
         << RESET_COLOR << BOLDOFF_STYLE << BLUE_COLOR;

    fetchData();

    cout << RESET_COLOR << endl
         << WHITE_COLOR << "1 :  back" << endl
         << RESET_COLOR;

    int command = getch();
    switch (command)
    {
    case KB_1:
        displayMenu();
        break;

    default:
        cout << RED_COLOR << "Invalid Command" << RESET_COLOR;
        Sleep(500);
        displayLeaderBoard();
        break;
    }
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void deletePointers()
{
    for (int i = 0; i < (*game).boardSize; i++)
        delete[] (*game).board[i];

    delete[] (*game).board;
}

void exitBoard()
{
    system("cls");
    cout << BOLDON_STYLE << GREEN_COLOR << "Thanks for playing!" << RESET_COLOR << BOLDOFF_STYLE;
    exit(0);
}