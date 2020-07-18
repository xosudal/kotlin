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

int main(int argv, char** argc)
{
    IButton* pBtn;
    if (strcmp(argc[1], "Windows"))
        pBtn = new WinButton;
    else
        pBtn = new GTKButton;

    pBtn->Draw();
}
