#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>

const int DISPLAY_WIDTH = 30;
const int DISPLAY_HEIGHT = 50;

std::vector<std::vector<std::string>> tmp(DISPLAY_HEIGHT, std::vector<std::string>(DISPLAY_WIDTH, " "));
std::vector<std::vector<std::string>> display(DISPLAY_HEIGHT, std::vector<std::string>(DISPLAY_WIDTH, " "));


// 단어 내려오는 영역
void wordDisplay()
{
	int col = 0;

	std::cout << "hello";

	for (int j = 0; j < DISPLAY_HEIGHT; j++)
	{
		std::string newWord;
		int r_num = rand() % 25;
		for (int i = 0; i < 5; i++)
		{
			newWord.push_back('a' + rand() % 26);
			display[j][r_num].push_back('a' + rand() % 26);
		}

		std::cout << newWord << "\n";
	}

	/*while (true)
	{
		system("cls");

		for (int i = 0; i < DISPLAY_HEIGHT; i++)
		{
			for (int j = 0; j < DISPLAY_WIDTH; j++)
			{
				std::cout << display[i][j];
			}
			Sleep(3000);
			std::cout << "\n";
		}
		col++;
	}*/

	/*std::vector<char> string;
	char character = ' ';

	while ((character = _getche()) != '.')
	{
		string.push_back(character);
		system("cls");
		std::string print;
		for (char element : string)
		{
			print.push_back(element);
		}
		std::cout << print;
	}

	return EXIT_SUCCESS;*/
}

int main(void)
{
	system("mode con:cols=30 lines=50");

	std::cout << "ehllo";
	//wordDisplay();

	return 0;
}