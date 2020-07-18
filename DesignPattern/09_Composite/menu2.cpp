/**
 * Menu / Popup 두개 동시에 보관. 기반 클래스를 만든다
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BaseMenu
{
    string title;
public:
    BaseMenu(string s) : title(s) {}

    string getTitle() const { return title;}

    virtual void command() = 0; // important
};

class MenuItem : public BaseMenu
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
            system("cls");

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
    PopupMenu pm("display");
}
