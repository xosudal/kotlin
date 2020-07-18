#include <iostream>
#include <mutex>
using namespace std;

// DCLP (double check locking pattern)
class Cursor
{
    int x,y;
private:
    Cursor() {}
    Cursor(const Cursor&) = delete;
    void operator=(const Cursor&) = delete;
    static Cursor* pInstance;

    static mutex m;
public:
    // lazy initialization
    static Cursor& getInstance()
    {
        // 단점 : 최초 생성 시 if 를 두 번 실행
        // 장점 : 최초 제외 lock을 수행하지 않음
        if (pInstance == 0)
        {
            m.lock();
            if (pInstance ==0) pInstance = new Cursor; // 동기화 필요
            m.unlock();
        }
        return *pInstance;
    }
};
Cursor* Cursor::pInstance = 0;
mutex Cursor::m;

int main()
{
    //Cursor& c1 = Cursor::getInstance();
}
