// 상태에 따라 변경되는 동작들을 다른 클래스로 분리
// 객체의 속성은 유지하지만 동작을 변경할 수 있다
// 클래스가 아닌 객체에 대한 변화

// state pattern
// 객체 자신의 내부 상태에 따라 동작을 변경하도록 함
// 객체는 마치 클래스를 바꾸는 것 처럼 보인다

// state pattern과 strategy pattern 의 차이
// class diagram은 동일함
// state 는 어떤 객체의 동작을 변경하도록
// strategy는 동작하는 알고리즘을 변경

#include <iostream>
using namespace std;

struct IState
{
    virtual void run() = 0;
    virtual void attack() = 0;

    virtual ~IState() {}
};

class Character
{
    int gold = 0;
    int item = 0;
    IState* state;
public:
    void changeState(IState* p) { state = p; }
    void run()      { state->run(); }
    void attack()   { state->attack(); }
};

class NormalState : public IState
{
    virtual void run() { cout << "normal run" << endl; }
    virtual void attack() { cout << "normal attack" << endl; }
};

class PowerItemState : public IState
{
    virtual void run() { cout << "power run" << endl; }
    virtual void attack() { cout << "power attack" << endl; }
};

int main()
{
    NormalState ns;
    PowerItemState ps;
    Character *p = new Character;
    p->changeState(&ns);
    p->run();
    p->attack();

    p->changeState(&ps); // item 획득
    p->run();
    p->attack();
}
