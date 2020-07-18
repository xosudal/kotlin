/**
 *  추상 클래스 : 순수 가상함수를 한 개 이상 가지고 있음
 *  객체는 만들지 못하지만 포인터는 가능함
 *  만드는 의도 : 파생 클래스에게 특정 함수를 반드시 구현하라고 지시
 */

class Shape // 추상 클래스 : 순수 가상함수를 한 개 이상 가지고 있음
{
public:
    virtual void Draw() = 0; // 순수 가상함수
};

class Rect : public Shape
{
public:
    virtual void Draw() {} // 구현부를 제공하면 추상클래스가 되지 않음
};

int main()
{
    Shape s;   // error. draw 구현부를 부를 수 없으니 객체를 만들 수 없다
    Shape* sp; // ok

    Rect r;    // Draw를 만들지 않으면 객체를 만들 수 없다
}