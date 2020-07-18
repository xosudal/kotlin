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
    PopupMenu* p1      = new PopupMenu("display");
    
    p1->addMenu(new PopupMenu("해상도변경"));
    p1->addMenu(new PopupMenu("명암 변경"));
    p1->addMenu(new MenuItem("음량 조절", 31));

    // p1은 복합객체
    // [ display ]

    // 1. title을 변경하는 멤버함수 추가 -> 기반 클래스에 함수를 추가해야함. 모든 파생 클래스 수정을 해야함
    // 새로운 가상함수 추가는 굉장히 복잡함 (수정 point가 굉장히 많다)

    // 2. 기존 클래스 변경 없이 operation 추가 = 방문자 패턴
    // 수정이 필요하긴 하지만 visitor 패턴을 추가하기 위한 수정으로, 이후 수정이 쉬워짐
    // 함수를 추가하는 효과를 낼 수 있음

    MenuTitleChangeVisitor mtcv;

    p1->accept(&mtcv);

    p1->command();
}
