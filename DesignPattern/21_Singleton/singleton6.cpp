#include <iostream>
using namespace std;

// singleton 코드 재 사용 기술
// 매크로를 사용한 재 사용

#define MAKE_SINGLETON(classname)               \
private:                                        \
    classname(const classname&) = delete;             \
    void operator=(const classname&) = delete;     \
    classname() {}                                 \
public:                                         \
    static classname& getInstance()                \
    {                                           \
        static classname instance;                 \
        return instance;                        \
    }


class Cursor
{
    int x,y;
    MAKE_SINGLETON(Cursor)
};

int main()
{
    Cursor& c1 = Cursor::getInstance();
}
