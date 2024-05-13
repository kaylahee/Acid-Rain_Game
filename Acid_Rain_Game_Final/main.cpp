#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h>

const int DISPLAY_WIDTH = 30;
const int DISPLAY_HEIGHT = 20;
const int TYPING_AREA_HEIGHT = 3; // Height of the typing area

std::vector<std::vector<std::string>> display(DISPLAY_HEIGHT, std::vector<std::string>(DISPLAY_WIDTH, " "));
std::vector<std::string> words;

int hp = 10; // Initial HP
int score = 0; // Initial score

std::string generateRandomWord() 
{
    std::string newWord;
    for (int i = 0; i < 5; i++) 
    {
        newWord.push_back('a' + rand() % 26);
    }
    return newWord;
}

// Function to move the cursor to a specific position on the console
void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printDisplay() 
{
    for (int i = 0; i < DISPLAY_HEIGHT; i++) 
    {
        for (int j = 0; j < DISPLAY_WIDTH; j++) 
        {
            std::cout << display[i][j]; 
        }
        std::cout << "\n";
    }
}

void wordDisplay() {
    std::vector<char> inputString;
    int cursorX = 15;

    int col = 0;
    int tmp_num = 0;

    DWORD prevTime = GetTickCount();

    while (true) 
    {
        DWORD currentTime = GetTickCount();
        DWORD deltaTime = currentTime - prevTime;

        if (deltaTime >= 1000)
        {
            system("cls");

            for (int i = 1; i < DISPLAY_WIDTH - 1; i++)
            {
                display[0][i] = " ";
            }

            std::string newWord = generateRandomWord();
            words.push_back(newWord);

            int r_num = rand() % (DISPLAY_WIDTH - 5);
            for (int i = 0; i < 5; i++)
            {
                display[0][r_num + i] = newWord[i];
            }

            for (int i = DISPLAY_HEIGHT - 1; i >= 0; i--)
            {
                for (int j = 0; j < DISPLAY_WIDTH; j++)
                {
                    if (i - 1 >= 0)
                    {
                        display[i][j] = display[i - 1][j];
                    }
                    else
                    {
                        display[i][j] = " ";
                    }
                }
            }

            printDisplay();
            std::cout << "\n\n";

            std::cout << "HP: " << hp << " Score: " << score << "\n";

            for (int i = 0; i < TYPING_AREA_HEIGHT; ++i)
            {
                std::cout << std::string(DISPLAY_WIDTH, ' ') << "\n";
            }
            std::cout << "\rFill the word: ";

            gotoxy(cursorX, 55);

            std::string print;
            for (char element : inputString)
            {
                print.push_back(element);
            }

            if (_kbhit())
            {
                char ch = _getch();
                // Backspace key
                if (ch == 8)
                {
                    if (!inputString.empty())
                    {
                        inputString.pop_back();
                        cursorX--;
                        gotoxy(cursorX, 55);
                        std::string print(inputString.begin(), inputString.end());
                        std::cout << print;
                    }
                }
                // Enter key
                else if (ch == '\r')
                {
                    std::string inputWord(inputString.begin(), inputString.end());

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
                            for (int i = 0; i < DISPLAY_HEIGHT; ++i)
                            {
                                for (int j = 0; j < DISPLAY_WIDTH - 5; ++j)
                                {
                                    std::string wordFromDisplay = display[i][j] + display[i][j + 1] + display[i][j + 2] + display[i][j + 3] + display[i][j + 4];

                                    if (wordFromDisplay == inputWord)
                                    {
                                        for (int k = j; k < j + 5; ++k)
                                        {
                                            display[i][k] = " ";
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    inputString.clear();
                    std::string print(inputString.begin(), inputString.end());
                    system("cls");
                    std::cout << print;
                    cursorX = 15;
                }
                else
                {
                    inputString.push_back(ch);
                    cursorX++;
                    std::string print(inputString.begin(), inputString.end());
                    std::cout << print;
                }
            }

            bool yesInDisplay = false;
            for (int i = 0; i < DISPLAY_WIDTH; i++)
            {
                if (display[DISPLAY_HEIGHT - 1][i] != " ")
                {
                    yesInDisplay = true;

                    std::string prevWord;
                    for (int j = 0; j < DISPLAY_WIDTH; j++)
                    {
                        if (display[DISPLAY_HEIGHT - 1][j] != " ")
                        {
                            prevWord += display[DISPLAY_HEIGHT - 1][j];
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
    srand(time(NULL));
    system("mode con:cols=30 lines=50");
    wordDisplay();
    return 0;
}
