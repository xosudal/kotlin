//policy1.cpp
// List에서 변하는 것 : 동기화 정책(multi-thread)
// List에서 변하지 않는 것 : list의 알고리즘

#include <iostream>
using namespace std;

template<typename T> class List
{
public:
    void push_front(const T& a)
    {
        Lock();
        // ...
        Unlock();
    }
};

List<int> s; // multi-thread에 안전하지 않음

int main()
{
    s.push_front(10);
}
