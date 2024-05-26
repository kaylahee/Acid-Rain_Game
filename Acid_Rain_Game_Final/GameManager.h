#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h>

#include "ConsoleUtils.h"

class GameManager 
{
public:
    const int BOARD_WIDTH = 30;
    const int BOARD_HEIGHT = 20;
    const int TYPING_AREA_HEIGHT = 3;

    GameManager(): 
        board(BOARD_HEIGHT, std::vector<std::string>(BOARD_WIDTH, " ")), 
        hp(10), score(0), cursorX(15) 
    {
        std::srand(std::time(nullptr));
    }

    void run();

private:
    std::vector<std::vector<std::string>> board;
    std::vector<std::string> words;
    std::vector<char> inputString;
    int hp;
    int score;
    int cursorX;

    ConsoleUtils cu;

    std::string generateRandomWord();
    void printDisplay();
    void check_Word(const std::string& inputWord);
    void user_Input();
    void wordDisplay();    
};