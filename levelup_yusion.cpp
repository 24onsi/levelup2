#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class UserInfo
{
private:
    string name;                 // 유저 이름
    int level;                   // 레벨
    long double exp;             // 현재 경험치
    long double Max_exp;         // 최재 경험치
    long double Box_exp;         // 1~5 단계 경험치 담은

public:
    UserInfo()                   // 초기화
    {
        level = 1;
        exp = 20000;
        Max_exp = 30000;
        Box_exp = 0;
    }
    void InputName();                          // 이름 입력
    void ShowUserInfo(int turn);               // 레벨, 경험치 출력
    void NomalStep(int step);                  // 1~5 단계
    void EventStep();                          // 이벤트 단계
    void LevelUpDown();                        // 레벨 업 다운 판단
    int NextTurn(int& turn, int& exi);         // 다음 턴 진행 입력
    int Ending(int turn, int & exi);           // 엔딩 판단
    ~UserInfo()
    { }
};


int main()
{
    srand(time(NULL));

    UserInfo user;                          // 클래스
    int step = 0;                           // 1턴안에 5 단계
    int turn = 1;                           // 턴 수
    int exi = 0;                            // 종료
    cout << fixed;
    cout.precision(2);

    cout << "[  나 혼자 만 레벨 업  ]\n\n";
    user.InputName();

    while(1)
    {
        cout << "|| 현재 " << turn << "번째 턴\n\n";
        
        for(step = 1 ; step <= 6 ; step++)
        {
            if(step == 6)                   // 이벤트
                user.EventStep();

            else                            // 1~5 단계
                user.NomalStep(step);
        }

        user.LevelUpDown();                 // 레벨 업 다운 판단
        user.ShowUserInfo(turn);            // 유저 정보 출력

        exi = user.Ending(turn, exi);       // 엔딩 판단
        if(exi == 1)
            break;

        exi = user.NextTurn(turn, exi);     // 다음 턴 진행 입력
        if (exi == 1)
            break;
    }
    cout << "종료" << endl;
    return 0;
}

void UserInfo::InputName()
{
    cout << "이름을 입력하세요: ";
    getline(cin, name);
    cout << endl;
    cout << name << "님 Lv.99 될 때까지 힘내세요!" << endl;
    cout << endl;
}

void UserInfo::ShowUserInfo(int turn)
{
    cout << "\n---------------------------------------\n\n  ";
    cout << name << "님 정보\n\n";
    cout << "  - Lv." << level << endl;
    cout << "  - Exp : " << exp/10000 << endl;
    cout << "  - MAX Exp : " << Max_exp/10000 << endl;
    cout << "  - " << turn << "턴" << endl;
    cout << "\n---------------------------------------\n\n";
}

void UserInfo::NomalStep(int step)
{
    float randNum = (float)(rand()%7001 - 3500);
    cout << "step # " << step << endl;
    Box_exp += randNum;
    if (randNum > 0)
        cout << "| " << randNum << " 경험치를 획득했습니다.\n\n";
    else
        cout << "| " << randNum << " 경험치를 잃었습니다.\n\n";
}

void UserInfo::EventStep()
{
    float randNum = (float)(((rand()%50)/10)+1);
    cout << "이벤트 스테이지 입니다." << endl;
    cout << "| " << "\" 경험치 x " << randNum << " 배 \"" << endl;
    cout << "|   아이템을 받았습니다." << endl;
    Box_exp *= randNum;
    exp += Box_exp;       
}

void UserInfo::LevelUpDown()
{
    while(exp > Max_exp || exp < 0)
    {
        float randNum = (float)(((rand()%7)/10)+1.8);
        cout << "\n---------------------------------------\n\n";
        if (exp > Max_exp)
        {
            cout << "   Lv." << level << " -> ";
            level += 1;
            cout << "Lv." << level << " LEVEL UP !!\n";
            exp -= Max_exp;
            Max_exp *= randNum;
            cout << "   현재 최대 경험치 : \n";
            cout << "   > " << Max_exp/10000 << "\n";
        }
        else if(exp < 0)
        {
            cout << "   Lv." << level << " -> ";
            level -= 1;
            cout << "Lv." << level << " LEVEL DOWN...\n";
            Max_exp /= randNum;
        }
        if(level == 99 || level <=0)
            break;
    }
}

int UserInfo::Ending(int turn, int& exi)
{
    if(level==99)
    {
        cout << "\n\n---------------------------------------\n\n";
        cout << "  축하합니다.\n  " << turn << "번째 턴에 게임 클리어 했습니다.\n";
        cout << "\n---------------------------------------\n";
        exi = 1;
    }
    else if(level <= 0)
    {
        cout << "\n\n---------------------------------------\n\n";
        cout << "\t아쉽네요...\n\t다음 기회에....\n";
        cout << "\n---------------------------------------\n";
        exi = 1;
    }
    else
        exi = 0;
    
    return exi;
}

int UserInfo::NextTurn(int& turn, int& exi)
{
    char answer;
    cout << "  다음 턴을 진행하시겠습니까? \n  ( 진행 : y, 종료 : n ) " << endl;
    cin >> answer;
    if(answer == 'y')
    {
        cout << "  다음 턴으로 이동합니다.\n\n";
        turn += 1;
        Box_exp = 0;
        exi= 0;
    }
    else
    {
        cout << "  종료합니다." << endl;
        exi = 1;
    }

    return exi;
}