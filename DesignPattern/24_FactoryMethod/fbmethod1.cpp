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


// 옵션에 관계 없이 무조건 windows 스타일
class WinDialog
{
public:
    void Init()
    {
        WinButton* pBtn = new WinButton;
        WinEdit*   pEdit = new WinEdit;
        //pBtn->Move();
        //pBtn->Move();

        pBtn->Draw();
        pBtn->Draw();
    }
};

class GTKDialog
{
public:
    void Init()
    {
        GTKButton* pBtn = new GTKButton;
        GTKEdit*   pEdit = new GTKEdit;
        //pBtn->Move();
        //pBtn->Move();

        pBtn->Draw();
        pBtn->Draw();
    }
};

int main(int argv, char** argc)
{
    WinDialog dlg;
    dlg.Init();
}
