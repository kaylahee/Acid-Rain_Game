#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

const int DISPLAY_WIDTH = 50; // 디스플레이 너비
const int DISPLAY_HEIGHT = 20; // 디스플레이 높이
const int UPDATE_INTERVAL = 3000; // 5초마다 디스플레이 업데이트

// 화면을 지우고 디스플레이 영역을 그리는 함수
void drawDisplay(const vector<string>& display)
{
    system("cls"); // 콘솔 화면을 지웁니다.

    // 고정된 디스플레이 영역에 display를 그립니다.
    for (int i = 0; i < DISPLAY_HEIGHT; ++i)
    {
        if (i < display.size())
        {
            cout << display[i];
        }
        cout << endl;
    }
}

// 디스플레이 업데이트 스레드 함수
void updateDisplayThread(vector<string>& display)
{
    while (true) {
        // 디스플레이 업데이트
        drawDisplay(display);

        // 새로운 단어 추가
        string newWord;
        for (int i = 0; i < 5; ++i)
        {
            newWord.push_back('A' + rand() % 26); // 랜덤한 알파벳 생성
        }

        // 새로운 단어의 시작 위치를 랜덤하게 선택
        int startPos = rand() % (DISPLAY_WIDTH - newWord.size() + 1);

        // 새로운 단어를 디스플레이 맨 위에 추가
        display.insert(display.begin(), newWord);

        // 디스플레이 크기가 DISPLAY_HEIGHT를 초과하는 경우 마지막 단어 제거
        if (display.size() > DISPLAY_HEIGHT)
        {
            display.pop_back();
        }

        // 디스플레이 크기가 DISPLAY_HEIGHT를 초과하는 경우 마지막 단어 제거
        if (display.size() > DISPLAY_HEIGHT)
        {
            display.pop_back();
        }

        // 프롬프트 출력
        cout << "단어를 입력하세요: ";

        // 일시 정지
        this_thread::sleep_for(chrono::milliseconds(UPDATE_INTERVAL));
    }
}

int main() {
    srand(time(0));

    // display 벡터 초기화
    vector<string> display(DISPLAY_HEIGHT, string(DISPLAY_WIDTH, ' '));

    // 새로운 스레드에서 디스플레이 업데이트
    thread updateThread(updateDisplayThread, ref(display));

    // 게임 루프
    while (true)
    {
        // 사용자 입력 받기
        string userInput;
        cin >> userInput;

        // 단어 찾기 및 제거
        auto it = find(display.begin(), display.end(), userInput);
        if (it != display.end())
        {
            display.erase(it); // 해당 단어를 삭제합니다.
        }
        else
        {
            cout << "입력한 단어가 디스플레이에 없습니다!" << endl;
        }

    }

    return 0;
}