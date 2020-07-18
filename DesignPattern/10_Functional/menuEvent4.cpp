/**
 * 일반함수와 멤버함수 포인터 동시에 담기
 * 일반/멤버함수포인터를 wrapping 하는 class 두 개 만들기
 * 이 둘을 묶는 공통의 기반 클래스 만들기
 */

#include <iostream>
using namespace std;

void foo() { cout << "foo" << endl; }

struct IAction
{
    virtual void execute() = 0;
    virtual ~IAction() {}
};

class Dialog
{
public:
    void Close() { cout << "Dialog Close" << endl; }
};

class FuctionAction : public IAction
{
    //typedef void(*FP)();
    using FP = void(*)();
    FP handler;
public:
    FuctionAction(FP f) : handler(f) {}
    virtual void execute() {handler();}
};

template<typename T>
class MemberAction : public IAction
{
    //typedef void(*FP)();
    using FP = void(T::*)();
    FP handler;
    T* target;
public:
    MemberAction(FP f, T* obj) : handler(f), target(obj) {}
    virtual void execute() {(target->*handler)();}
};

int main()
{
    //void(*f1)()         = &foo;

    //일반/멤버 함수가 동일한 데이터 타입 가질 수 있음
    IAction* p = new FuctionAction(&foo);
    p->execute();
    Dialog dlg;
    IAction* p2 = new MemberAction<Dialog>(&Dialog::Close,&dlg);
    p2->execute();
    //void(Dialog::*f2)() = &Dialog::Close;
}
