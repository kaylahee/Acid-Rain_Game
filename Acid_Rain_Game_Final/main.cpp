#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h>

#include "ConsoleUtils.h"

ConsoleUtils cu;

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;
const int TYPING_AREA_HEIGHT = 3;

std::vector<std::vector<std::string>> board(BOARD_HEIGHT, std::vector<std::string>(BOARD_WIDTH, " "));
std::vector<std::string> words;

int hp = 10;
int score = 0;

std::vector<char> inputString;
int cursorX = 15;

std::string generateRandomWord()
{
    std::string newWord;
    for (int i = 0; i < 5; i++)
    {
        newWord.push_back('a' + rand() % 26);
    }
    words.push_back(newWord);
    return newWord;
}

void printDisplay()
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            std::cout << board[i][j];
        }
        std::cout << "\n";
    }
}

void check_Word(std::string inputWord)
{
    bool isWordin = false;
    for (int i = 0; i < words.size(); ++i)
    {
        if (words[i] == inputWord)
        {
            isWordin = true;
            words.erase(words.begin() + i);
            score++;
        }

        if (isWordin == true)
        {
            for (int i = 0; i < BOARD_HEIGHT; ++i)
            {
                for (int j = 0; j < BOARD_WIDTH - 5; ++j)
                {
                    std::string wordFromDisplay = board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3] + board[i][j + 4];

                    if (wordFromDisplay == inputWord)
                    {
                        for (int k = j; k < j + 5; ++k)
                        {
                            board[i][k] = " ";
                        }
                        break;
                    }
                }
            }
        }
    }
}

void user_Input()
{
    if (_kbhit())
    {
        char ch = _getch();
        cu.gotoxy(cursorX + 1, 25);

        std::string print;

        // Backspace key
        if (ch == 8 && !inputString.empty())
        {
            inputString.pop_back();

            cu.clear_Screen();
            cu.gotoxy(cursorX + 1, 25);

            for (char element : inputString)
            {
                std::cout << element;
            }

            std::cout << " ";
        }
        // Enter key
        else if (ch == '\r')
        {
            std::string inputWord(inputString.begin(), inputString.end());
            check_Word(inputWord);

            cu.clear_Screen();
            cu.gotoxy(cursorX + 1, 25);

            inputString.clear();
            std::cout << "                       ";
            cursorX = 15;
        }
        else
        {
            inputString.push_back(ch);
            for (char element : inputString)
            {
                print.push_back(element);
            }
            std::cout << print;
        }
    }
}

void wordDisplay()
{
    int col = 0;
    int tmp_num = 0;

    DWORD prevTime = GetTickCount();

    while (true)
    {
        Sleep(100);

        DWORD currentTime = GetTickCount();
        DWORD deltaTime = currentTime - prevTime;

        cu.clear_Screen();

        printDisplay();
        std::cout << "-----------------------------";

        cu.gotoxy(0, 25);
        std::cout << "Fill the word:";
        user_Input();

        if (hp == 10)
        {
            cu.gotoxy(0, 27);
            std::cout << "HP: " << hp;
        }
        else
        {
            cu.gotoxy(0, 27);
            std::cout << "HP: " << hp;
            std::cout << " ";
        }
        cu.gotoxy(0, 28);
        std::cout << "Score: " << score;

        if (deltaTime >= 1500)
        {
            std::string newWord = generateRandomWord();
            words.push_back(newWord);

            int r_num = rand() % (BOARD_WIDTH - 5);
            for (int i = 0; i < 5; i++)
            {
                board[0][r_num + i] = newWord[i];
            }

            for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
            {
                for (int j = 0; j < BOARD_WIDTH; j++)
                {
                    if (i - 1 >= 0)
                    {
                        board[i][j] = board[i - 1][j];
                    }
                    else
                    {
                        board[i][j] = " ";
                    }
                }
            }

            bool yesInDisplay = false;
            for (int i = 0; i < BOARD_WIDTH; i++)
            {
                if (board[BOARD_HEIGHT - 1][i] != " ")
                {
                    yesInDisplay = true;

                    std::string prevWord;
                    for (int j = 0; j < BOARD_WIDTH; j++)
                    {
                        if (board[BOARD_HEIGHT - 1][j] != " ")
                        {
                            prevWord += board[BOARD_HEIGHT - 1][j];
                        }
                    }

                    for (int j = 0; j < words.size(); j++)
                    {
                        if (prevWord == words[j])
                        {
                            words.erase(words.begin() + j);
                        }
                    }
                }
            }

            if (yesInDisplay == true)
            {
                hp--;
                if (hp <= 0)
                {
                    system("cls");
                    std::cout << "Game Over! Your score: " << score << std::endl;
                    break;
                }
            }

            prevTime = currentTime;
        }
    }
}

int main()
{
    cu.CursorView();

    srand(time(NULL));
    system("mode con:cols=30 lines=50");
    wordDisplay();
    return 0;
}