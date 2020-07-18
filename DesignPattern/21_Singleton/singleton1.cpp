#include <iostream>
using namespace std;

// 상속을 사용한 기법

// CRTP : Curiously Recurring Template Pattern
template<typename T> class Singleton
{
    int x,y;
protected: // 파생클래스의 객체를 만드려면 기반클래스의 생성자는 protected
    Singleton() {}
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
public:
    static T& getInstance()
    {
        static T instance;
        return instance;
    }
};

class Mouse : public Singleton<Mouse>
{

};

int main()
{
    Cursor& c1 = Cursor::getInstance();
}
