#include <iostream>
using namespace std;

struct IButton
{
    virtual void Draw() = 0;
    virtual ~IButton() {}
};

struct IEdit
{
    virtual void Draw() = 0;
    virtual ~IEdit() {}
};

struct WinButton : public IButton { void Draw() { cout << "Draw WinButton" << endl;}};
struct GTKButton : public IButton { void Draw() { cout << "Draw GTKButton" << endl;}};

struct WinEdit : public IEdit { void Draw() { cout << "Draw WinEdit" << endl;}};
struct GTKEdit : public IEdit { void Draw() { cout << "Draw GTKEdit" << endl;}};

//---------------------------------
// Factory의 공통 기반 클래스 = Abstract Factory
// 여러 객체의 군을 생성하기 위한 인터페이스

struct IFactory
{
    virtual IButton* CreateButton() = 0;
    virtual IEdit* CreateEdit() = 0;
};

struct WinFactory : public IFactory
{
    IButton* CreateButton() { return new WinButton; }
    IEdit* CreateEdit() { return new WinEdit; }
};

struct WinFactory : public IFactory
{
    IButton* CreateButton() { return new GTKButton; }
    IEdit* CreateEdit() { return new GTKEdit; }
};

int main(int argv, char** argc)
{
    IFactory* pFactory;
    if (strcmp(argc[1], "Windows") == 0)
        pFactory = new WinFactory;
    else
        pFactory = new GTKFactory;

    IButton* pBtn = pFactory->CreateButton();

    pBtn->Draw();
}

