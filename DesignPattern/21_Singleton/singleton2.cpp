#include <iostream>
using namespace std;

// 유일한 객체를 생성하는 방법

#if 0
//1. static member data - 사용하지 않아도 생성자가 불린다
class Cursor
{
    int x,y;
private:
    Cursor() {}
    Cursor(const Cursor&) = delete;
    void operator=(const Cursor&) = delete;

    static Cursor instance;
public:
    static Cursor& getInstance()
    {
        return instance;
    }
};

Cursor Cursor::instance;

int main()
{
    //Cursor& c1 = Cursor::getInstance();
}
#endif

#if 1 
// 2. static 지역 변수
// getInstance가 불릴 때 생성됨
class Cursor
{
    int x,y;
private:
    Cursor() {}
    Cursor(const Cursor&) = delete;
    void operator=(const Cursor&) = delete;
public:
    // lazy initialization
    static Cursor& getInstance()
    {
        static Cursor instnace;
        return instance;
    }
};

int main()
{
    //Cursor& c1 = Cursor::getInstance();
}
#endif
#if 1 
// 3. new를 생성할 때 생성
// getInstance가 불릴 때 생성됨
class Cursor
{
    int x,y;
private:
    Cursor() {}
    Cursor(const Cursor&) = delete;
    void operator=(const Cursor&) = delete;
    static Cursor* pInstance;
public:
    // lazy initialization
    static Cursor& getInstance()
    {
        if (pInstance ==0) pInstance = new Cursor;
        return *pInstance;
    }
};
Cursor* Cursor::pInstance;

int main()
{
    //Cursor& c1 = Cursor::getInstance();
}
#endif
