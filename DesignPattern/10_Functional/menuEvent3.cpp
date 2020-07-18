/**
 * MenuItem Class 설계
 * 메뉴를 선택할 때 하는 일은 메뉴 객체에 따라 다르다
 * 메뉴마다 하는 일이 다르므로 command에서 어떤 일을 직접 하면 안됨
 * 3. 메뉴 선택 시 객체가 아닌 함수와 직접 연결한다
 * 
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BaseMenu // 복합 객체 (composite, node)
{
    string title;
public:
    BaseMenu(string s) : title(s) {}

    string getTitle() const { return title;}

    // popup에만 필요함. menu는 필요 없는 경우
    // 순수가상함수로는 만들지 않음
    virtual BaseMenu* getSubMenu(int idx) {return 0;}

    virtual void addMenu(BaseMenu* p)
    {
        throw "unsupported function";
    }

    virtual void command() = 0; // important
};

class MenuItem : public BaseMenu // 개별객체 (leaf)
{
    int id;
    //c++에는 일반함수 / 멤버함수 동시에 담는 포인터가 없음
    //void (*handler)();
    //void (Dialog::*handler)();
    //Dialog* target;
public:
    MenuItem(string s, int n) : BaseMenu(s), id(n) {}

    virtual void command()
    {
    }
};

class Dialog : public IMenuListener
{
public:
    virtual void doCmd(int id)
    {
        cout << "Dialog Cmd : " << id << endl;
    }
}

class PopupMenu : public BaseMenu
{
    vector<BaseMenu*> v;
public:
    PopupMenu(string s) : BaseMenu(s) {}

    void addMenu(BaseMenu* p) {v.push_back(p);}

    virtual void command()
    {
        while (1)
        {
            int sz = v.size();

            for (int i=0; i<sz; i++)
            {
                cout << i+1 << ". " << v[i]->getTitle() << endl;
            }
            cout << sz+1 << ". 상위 메뉴로" << endl;
            //---------- 화면 메뉴 출력
            int cmd;
            cout << "메뉴를 선택하세요 >> ";
            cin >> cmd;

            if (cmd < 1 || cmd > sz + 1) continue;

            if (cmd == sz + +1)     break;

            // 선택된 메뉴 실행..
            // 선택된 것이 팝업이냐 메뉴이냐가 중요
            // 구별할 필요가 없이 command를 부르면 알아서 호출
            v[cmd-1]->command(); // important!!
        }
    }

    virtual BaseMenu* getSubMenu(int idx)
    {
        return v[idx];
    }
};

int main()
{
    PopupMenu* menubar  = new PopupMenu("Menubar");
    PopupMenu* pm1      = new PopupMenu("display");
    PopupMenu* pm2      = new PopupMenu("sound");
    MenuItem*  m1       = new MenuItem("information", 11);

    menubar->addMenu(pm1);
    menubar->addMenu(pm2);
    menubar->addMenu(m1);

    pm1->addMenu(new MenuItem("해상도변경", 21));
    pm1->addMenu(new MenuItem("명암 변경", 22));
    pm2->addMenu(new MenuItem("음량 조절", 31));

    BaseMenu* p = menubar->getSubMenu(1)->getSubMenu(0);

    menubar->getSubMenu(1)->addMenu(new MenuItem("test",100));

    // start
    menubar->command();
}
