// 객체를 생성하는 방법
class Shape
{
public:
    virtual ~Shape() {}
};

class Rect : public Shape
{
public:
};

class Circle : public Shape
{
public:
};

int main()
{
    // 1. 사용자가 직접 객체를 생성
    Rect r; // stack
    Shape* p = new Rect; // heap
};
