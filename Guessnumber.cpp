#include <bits/stdc++.h>
using namespace std;
int playGame (mt19937 &rng){
    uniform_int_distribution<int> dist(1,100);
    int secret = dist(rng);
    int guess = 0;
    int attempts = 0;
    cout << "\n 猜数字游戏开始！" << endl;
    cout << "我已经想好了一个 1 到 100 之间的整数。" << endl;
    do {
        cout << "请输入你的猜测: ";
        if (!(cin >> guess)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << " 无效输入！请输入一个整数。" << endl;
            continue;
        }
        if (guess < 1 || guess > 100 ){
            cout << "  请输入 1~100 之间的数字。" << endl;
            continue;
        }
        attempts ++;
        if (guess < secret){
            cout << " 猜低了！ (已猜 " << attempts << " 次) 再试试看。" << endl;
        }
        else if (guess > secret){
            cout << " 猜高了！ (已猜 " << attempts << " 次) 再试试看。" << endl;
        }
        else {
            cout << "\n 恭喜你猜对了！数字就是 " << secret << " ！" << endl;
            cout << " 你总共猜了 " << attempts << " 次。" << endl;
            break;
        }
    }   while (true);
    return attempts;
}
int main (){
    random_device rd;
    mt19937 rng(rd());
    int bestScore = numeric_limits<int> :: max();
    char choice;
    bool playAgain = true;
    cout << "======================================" << endl;
    cout << "          欢迎来到猜数字游戏！          " << endl;
    cout << "======================================" << endl;
    do {
        int currentAttempts = playGame(rng);
        if (currentAttempts < bestScore){
            bestScore = currentAttempts;
            cout << " 恭喜！你创造了新纪录！最佳成绩为 " << bestScore << " 次猜测。?" << endl;
        }
        else if (bestScore != numeric_limits<int>::max()){
            cout << " 本轮猜测次数: " << currentAttempts
                      << " 次  |  最佳记录: " << bestScore << " 次" << endl;
        } 
        else {
            cout << " 本轮猜测次数: " << currentAttempts << " 次" << endl;
        }
        cout << "\n 再玩一局吗？(y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y'){
            playAgain = false;
        }
    }while (playAgain);
    cout << "\n 感谢游玩，再见！" << endl;
    return 0;
}