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

// 함수 템플릿 (클래스 템플릿을 생성하는 도움 함수)
template<typename T>
MemberAction<T>* action( void(T::*f)(), T* obj)
{
    return new MemberAction<T>(f,obj);
}

FuctionAction* action( void(*f)())
{
    return new FuctionAction(f);
}

int main()
{
    //void(*f1)()         = &foo;

    //일반/멤버 함수가 동일한 데이터 타입 가질 수 있음
    IAction* p = action(&foo);//new FuctionAction(&foo);
    p->execute();
    Dialog dlg;
    IAction* p2 = action(&Dialog::Close,&dlg);//new MemberAction<Dialog>
    p2->execute();
    //void(Dialog::*f2)() = &Dialog::Close;
}

//----------------------------------
// 함수 템플릿은 타입을 추론하지만, 클래스 템플릿은 명시적으로 지정해야함
// 이럴때는 클래스 템플릿을 생성하는 함수 템플릿 도움함수를 만든다
