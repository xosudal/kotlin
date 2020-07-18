#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Shape
{
public:
    virtual void Draw() {cout << "Draw Shape" << endl;}
    virtual Shape* Clone() = 0;
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl; }
    static Shape* Create() { return new Rect;}
    virtual Shape* Clone() { return new Rect(*this);}
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Draw Circle" << endl; }
    static Shape* Create() { return new Circle;}
    virtual Shape* Clone() { return new Circle(*this);}
};

// 다양한 정보를 관리할 수 있다

class ShapeFactory
{
    MAKE_SINGLETON(ShapeFactory)
    // ProtoType 패턴
    // 클래스가 아닌 객체를 등록
    map<int, Shape*> proto_map;

public:
    void RegisterShape(int type, Shape* sample)
    {
        proto_map[type] = sample;
    }
    Shape* CreateShape(int type)
    {
        Shape* p = 0;

        auto it = create_map[type].find(type);

        if (it == create_map.end()) return 0;

        p = proto_map[type]->Clone();

        return p;
    }
};

int main()
{
    vector<Shape*> v;
    ShapeFactory sf = ShapeFactory::getInstance();

    // register
    // 클래스 등록(2개의 Rect는 등록 X, 클래스 당 한 개씩)
    //factory.Register(1, &Rect::Create);
    //factory.Register(2, &Circle::Create);

    Rect* r1 = new Rect; // 빨간색 크기 5
    Rect* r2 = new Rect; // 파란색 크기 10

    // 객체 등록(다양한 사각형)
    factory.Register(1, r1);
    factory.Register(2, r2);

    //factory.ShowProduct();

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
