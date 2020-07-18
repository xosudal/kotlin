#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Shape
{
public:
    virtual void Draw() {cout << "Draw Shape" << endl;}
};

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

struct RegisterShape
{
    RegisterShape(int type, Shape*(*f)())
    {
        ShapeFactory::getInstance().Register(type,f);
    }
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl; }
    static Shape* Create() { return new Rect;}

    static RegisterShape rs;
};
RegisterShape Rect::rs(1, &Rect::Create);

// 모든 도형이 지켜야 하는 규칙을 매크로로 제공
// 자동으로 도형을 등록
#define DECLARE_SHAPE(classname)        \
static Shape* Create() { return new classname;} \
static RegisterShape rs;

#define IMPLEMENT_SHAPE(type,classname)   \
RegisterShape classname::rs(type, &classname::Create);

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Draw Circle" << endl; }
    DECLARE_SHAPE(Circle)
};
IMPLEMENT_SHAPE(2,Circle)

// 다양한 정보를 관리할 수 있다


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
