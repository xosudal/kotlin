// policy3.cpp
// 단위 전략 디자인 (policy base design)
// template 인자를 사용해서 정책 클래스를 교체
// inline 치환이 가능하므로(가상함수 사용 X) 속도가 빠름
// template 인자를 사용하기 때문에 실행시간에 정책 교체가 불가능함
// 모든 정책 클래스는 자신이 지켜야 하는 규칙을 가지게 된다

#include <iostream>
using namespace std;

template<typename T, typename ThreadModel> class List
{
    ThreadModel tm;
public:
    void push_front(const T& a)
    {
        tm.Lock();
        // ...
        tm.UnLock();
    }
};


class MutexLock
{
    //mutex m;
public:
    inline void Lock() {cout << "mutex lock" << endl;}
    inline void UnLock() {cout << "mutex unlock" << endl;}
};

class NoLock 
{
    //mutex m;
public:
    inline void Lock() {}
    inline void UnLock() {}
};

List<int,NoLock> s; // multi-thread에 안전하지 않음

int main()
{
    MutexLock m;
    s.setSync(&m);

    s.push_front(10);
}
