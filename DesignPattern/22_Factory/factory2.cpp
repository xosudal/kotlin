#include <iostream>
#include <vector>
using namespace std;

class Shape
{
public:
    virtual void Draw() {cout << "Draw Shape" << endl;}
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl; }
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Draw Circle" << endl; }
};

// 객체 생성을 한 곳에서 관리가능
// 새로운 도형이 추가될 경우 한 곳만 코드를 수정하면 된다

class ShapeFactory
{
    MAKE_SINGLETON(ShapeFactory)
public:
    Shape* CreateShape(int type)
    {
        Shape* p = 0;
        if (type==1) p = new Rect;
        else if (type==2) p = new Circle;

        return p;
    }
};

int main()
{
    vector<Shape*> v;
    ShapeFactory sf = ShapeFactory::getInstance();
    while (1)
    {
        int cmd;
        cin >> cmd;
        if (cmd>=1 && cmd<=5)
        {
            Shape* p = factory.CreateShape(cmd);
            if (p!=0)
                v.push_back(p);
        }
        else if (cmd == 9)
        {
            for(auto p : v)
                p->Draw(); // 다형성
        }
    }
}
