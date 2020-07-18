#include <iostream>
using namespace std;

// singleton의 의도
// 클래스의 인스턴스는 오직 하나임을 보장
// 이에 대한 접근은 어디에서든지 하나로만 통일하여 제공
// static 멤버 함수를 통해서 하나의 객체를 생성한 후 참조를 반환
// 복사 생성자와 대입 연산자를 사용 못하게 해야한다
class Cursor
{
    int x,y;
    Cursor(const Cursor&) = delete;
    void operator=(const Cursor&) = delete;
private:
    Cursor() {}
public:
    static Cursor& getInstance()
    {
        static Cursor instance;
        return instance;
    }
};

int main()
{
    Cursor& c1 = Cursor::getInstance();
}
