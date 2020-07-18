// 상속은 객체에 대한 변화가 아니라 클래스에 대한 변화

#include <iostream>
using namespace std;

class Character
{
    int gold = 0;
    int item = 0;
public:
    void run()      { runImp(); }
    void attack()   { attackImp(); }

    virtual void runImp() {}
    virtual void attackImp() {}
};

class PowerItemCharacter : public Character
{
public:
    virtual void runImp() { cout << "fast run" << endl;}
    virtual void attackImp() { cout << "strong attack" << endl;}

};

class Normalcharacter : public Character
{
public:
    virtual void runImp() { cout << "run" << endl;}
    virtual void attackImp() { cout << "attack" << endl;}

};

int main()
{
    Character *p = new NormalCharacter;
    p->run();
    p->attack();

    // 상태를 물려받지 못함. 새로운 캐릭터가 생성되는 코드임
    // 기존 객체의 동작이 변경된 것이 아니라 동작이 변경된 새로운 개체가 생성

    p = new PowerItemCharacter;
    p->run();
    p->attack();
}
