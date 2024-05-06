#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

const int DISPLAY_WIDTH = 50; // ���÷��� �ʺ�
const int DISPLAY_HEIGHT = 20; // ���÷��� ����
const int UPDATE_INTERVAL = 3000; // 5�ʸ��� ���÷��� ������Ʈ

// ȭ���� ����� ���÷��� ������ �׸��� �Լ�
void drawDisplay(const vector<string>& display)
{
    system("cls"); // �ܼ� ȭ���� ����ϴ�.

    // ������ ���÷��� ������ display�� �׸��ϴ�.
    for (int i = 0; i < DISPLAY_HEIGHT; ++i)
    {
        if (i < display.size())
        {
            cout << display[i];
        }
        cout << endl;
    }
}

// ���÷��� ������Ʈ ������ �Լ�
void updateDisplayThread(vector<string>& display)
{
    while (true) {
        // ���÷��� ������Ʈ
        drawDisplay(display);

        // ���ο� �ܾ� �߰�
        string newWord;
        for (int i = 0; i < 5; ++i)
        {
            newWord.push_back('A' + rand() % 26); // ������ ���ĺ� ����
        }

        // ���ο� �ܾ��� ���� ��ġ�� �����ϰ� ����
        int startPos = rand() % (DISPLAY_WIDTH - newWord.size() + 1);

        // ���ο� �ܾ ���÷��� �� ���� �߰�
        display.insert(display.begin(), newWord);

        // ���÷��� ũ�Ⱑ DISPLAY_HEIGHT�� �ʰ��ϴ� ��� ������ �ܾ� ����
        if (display.size() > DISPLAY_HEIGHT)
        {
            display.pop_back();
        }

        // ���÷��� ũ�Ⱑ DISPLAY_HEIGHT�� �ʰ��ϴ� ��� ������ �ܾ� ����
        if (display.size() > DISPLAY_HEIGHT)
        {
            display.pop_back();
        }

        // ������Ʈ ���
        cout << "�ܾ �Է��ϼ���: ";

        // �Ͻ� ����
        this_thread::sleep_for(chrono::milliseconds(UPDATE_INTERVAL));
    }
}

int main() {
    srand(time(0));

    // display ���� �ʱ�ȭ
    vector<string> display(DISPLAY_HEIGHT, string(DISPLAY_WIDTH, ' '));

    // ���ο� �����忡�� ���÷��� ������Ʈ
    thread updateThread(updateDisplayThread, ref(display));

    // ���� ����
    while (true)
    {
        // ����� �Է� �ޱ�
        string userInput;
        cin >> userInput;

        // �ܾ� ã�� �� ����
        auto it = find(display.begin(), display.end(), userInput);
        if (it != display.end())
        {
            display.erase(it); // �ش� �ܾ �����մϴ�.
        }
        else
        {
            cout << "�Է��� �ܾ ���÷��̿� �����ϴ�!" << endl;
        }

    }

    return 0;
}