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
            if (pInstance ==0)
            {
                pInstance = new Cursor; // 동기화 필요
                // 1. temp = sizeof(Cursor) 메모리 할당
                // 2. Cursor::Cursor() 생성자 호출
                // 3. pInstance == temp;

                // 컴파일러가 최적화에 따른 버그 발생 가능성 존재
                // 1. temp = sizeof(Cursor) 메모리 할당
                // 3. pInstance == temp;
                // 2. Cursor::Cursor() 생성자 호출
                // 생성자 호출 중 getInstance 시 잘못 된 객체 리턴 가능
                // reordering 수행 하면 안 됨
                // c+11 atomic lib 사용하면 안전하게 사용 가능
            }
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
