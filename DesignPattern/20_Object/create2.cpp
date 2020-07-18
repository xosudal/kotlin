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
    static Shape* Create() { return new Rect;}
};

class Circle : public Shape
{
    Rect() {}
public:
    static Shape* Create() {return new Circle;}
};

// 도형을 만들어서 그림을 그리는 함수
void CreateAndDraw(Shape*(*f)())
{
    Shape* p = f();
    p->Draw();
}

int main()
{
    // 2. static member 함수를 통해 객체 생성
    // 객체의 생성을 한 곳에서 수행 한다
    // 객체 생성 함수를 함수의 인자로 전달할 수 있다

    //Shape* p = Rect::Create();
    CreateAndDraw(&Rect::Create);
};
