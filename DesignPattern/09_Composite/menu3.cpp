/**
 * Composite 패턴
 * 객체들을 트리 구조로 구성하여 부분과 전체를 나타내는 계층 구조로 만들 수 있다.
 * 개별 객체와 복합 객체를 구별하지 않고 동일한 방법으로 다룰 수 있다.
 * 재귀적 느낌이 있음
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

    virtual void command() = 0; // important
};

class MenuItem : public BaseMenu // 개별객체 (leaf)
{
    int id;
public:
    MenuItem(string s, int n) : BaseMenu(s), id(n) {}

    virtual void command()
    {
        cout << getTitle() << " in MenuItem"<< endl;
        getchar();
    }
};

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

    menubar->command();
}
