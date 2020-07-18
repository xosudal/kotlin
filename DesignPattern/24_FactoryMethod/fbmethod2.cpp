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

class BaseDialog
{
public:
    void Init()
    {
        IButton* pBtn = new CreateButton();
        IEdit*   pEdit = new CreateEdit();
        //pBtn->Move();
        //pBtn->Move();

        pBtn->Draw();
        pEdit->Draw();
    }
    // 객체를 생성하기 위해 인터페이스를 정의하지만
    // 어떤 클래스의 인스턴스를 생성할 지에 대해서는 서브 클래스가 결정한다
    // Factory Method.. (template method와 유사)
    virtual IButton* CreateButton() = 0;
    virtual IEdit*   CreateEdit() = 0;
};

// 옵션에 관계 없이 무조건 windows 스타일
class WinDialog : public BaseDialog
{
public:
    virtual IButton* CreateButton() {return new WinButton;}
    virtual IEdit*   CreateEdit() {return new WinEdit;}
};

class GTKDialog : public BaseDialog
{
public:
    virtual IButton* CreateButton() {return new GTKButton;}
    virtual IEdit*   CreateEdit() {return new GTKEdit;}
};

int main(int argv, char** argc)
{
    WinDialog dlg;
    dlg.Init();
}
