#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * 일반적인 객체지향은 새로운 타입을 추가하기는 쉽지만 새로운 함수를 추가하기는 어렵다
 * 방문자 패턴은 새로운 operation을 추가하기는 쉽지만 타입을 추가하기는 어렵다
 * 서로 반대의 개념이 되어버림
 */

class BaseMenu;
class MenuItem;
class PopupMenu;

struct IMenuVisitor
{
    virtual ~IMenuVisitor() {}
    virtual void visit(BaseMenu* p) = 0;
    virtual void visit(MenuItem* p) = 0;
    virtual void visit(PopupMenu* p) = 0;
};

struct IAcceptor
{
    virtual ~IAcceptor() {}
    virtual void accept(IMenuVisitor* p) = 0;
};


class BaseMenu : public IAcceptor// 복합 객체 (composite, node)
{
    string title;
public:
    BaseMenu(string s) : title(s) {}

    string getTitle() const { return title;}
    void setTitle(string s) { title = s; } // 캡슐화와 정보 은닉을 위반하게 된다
    virtual void command() = 0; // important
};

class MenuItem : public BaseMenu // 개별객체 (leaf)
{
    int id;
public:
    virtual void accept(IMenuVisitor* p)
    {
        p->visit(this);
    }

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

    virtual void accept(IMenuVisitor* p)
    {
        p->visit(this);

        for (auto m : v)
            m->accept(p);
    }
};

class MenuTitleChangeVisitor : public IMenuVisitor
{
public:
    virtual void visit(BaseMenu* p){}
    virtual void visit(MenuItem* p){}
    virtual void visit(PopupMenu* p)
    {
        // Popup Menu의 Title 변경
        string s = p->getTitle();
        s = "[" + s + "]";
        p->setTitle(s);
    }
};

class EraseTitleChangeVisitor : public IMenuVisitor
{
public:
    virtual void visit(BaseMenu* p){}
    virtual void visit(MenuItem* p){}
    virtual void visit(PopupMenu* p)
    {
        // Popup Menu의 Title 변경
        p->setTitle("...");
    }
};

int main()
{
    PopupMenu* p1      = new PopupMenu("display");
    
    p1->addMenu(new PopupMenu("해상도변경"));
    p1->addMenu(new PopupMenu("명암 변경"));
    p1->addMenu(new MenuItem("음량 조절", 31));


    // 1. 메뉴(복합객체)는 accept 필요
    // 2. 방문자 인터페이스 필요함

    MenuTitleChangeVisitor mtcv;

    p1->accept(&mtcv);

    EraseTitleChangeVisitor a;
    
    p1->accept(&a);

    p1->command();
}
