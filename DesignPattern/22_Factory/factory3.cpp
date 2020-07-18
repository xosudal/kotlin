#include <iostream>
#include <vector>
#include <map>
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
    static Shape* Create() { return new Rect;}
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Draw Circle" << endl; }
    static Shape* Create() { return new Circle;}
};

// 다양한 정보를 관리할 수 있다

class ShapeFactory
{
    MAKE_SINGLETON(ShapeFactory)
    typedef Shape*(*CREATOR)();
    map<int, CREATOR> create_map;

public:
    void RegisterShape(int type, CREATOR f)
    {
        create_map[type] = f;
    }
    Shape* CreateShape(int type)
    {
        Shape* p = 0;

        auto it = create_map[type].find(type);

        if (it == create_map.end()) return 0;

        p = create_map[type]();

        return p;
    }
};

int main()
{
    vector<Shape*> v;
    ShapeFactory sf = ShapeFactory::getInstance();

    // register
    factory.Register(1, &Rect::Create);
    factory.Register(2, &Circle::Create);

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
