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

int main()
{
    MenuItem m("sound", 11);
}
