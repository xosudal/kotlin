class Shape
{
public:
    virtual ~Shape() {}
    virtual Shape* Clone() = 0;
};

class Rect : public Shape
{
public:
    virtual Shape* Clone() { return new Rect(*this);}
};

class Circle : public Shape
{
public:
    virtual Shape* Clone() { return new Circle(*this);}
};

// 4. 기존에 존재하던 객체를 복사해서 새로운 객체 생성
// 프로토타입 패턴
// Clone 가상함수
int main()
{
    Shape* p = new Rect;
    Shape* p2 = p->Clone();
};
