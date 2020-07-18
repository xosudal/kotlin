// 객체를 생성하는 방법
class Shape
{
public:
    virtual ~Shape() {}
};

class Rect : public Shape
{
    Rect() {} // private 생성자
public:
    friend class ShapeFactory;
};

class Circle : public Shape
{
    Circle() {}
public:
    friend class ShapeFactory;
};

// 3. 객체 생성을 위한 전용 클래스
// 추상 팩토리 패턴
// 객체 생성을 한 곳에 집중시키고, 객체 본래의 기능과 객체 생성을 위한 코드를 분리
class ShapeFactory
{
public:
    Shape* CreateShape(int type)
    {
        Shape* p = 0;
        switch(type)
        {
        case 1: p = new Rect; break;
        case 2: p = new Circle; break;
        }
        return p;
    }
};

int main()
{
    ShapeFactory factory;
    Shape* p = factory.CreateShape(1);
};
