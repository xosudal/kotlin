//policy1.cpp
// List에서 변하는 것 : 동기화 정책(multi-thread)
// List에서 변하지 않는 것 : list의 알고리즘
// 가상함수가 성능 저하가 있긴함
// 혹은 push_front가 loop 내에 있는 경우 call의 overhead 존재
#include <iostream>
using namespace std;

struct ISync
{
    virtual void Lock() = 0;
    virtual void UnLock() = 0;
    virtual ~ISync() {}
};

template<typename T> class List
{
    ISync* pSync = 0;
public:
    void setSync(ISync* p) { pSync = p; }
    void push_front(const T& a)
    {
        if (pSync!=0) pSync->Lock();
        // ...
        if (pSync!=0) pSync->UnLock();
    }
};

List<int> s; // multi-thread에 안전하지 않음

class MutexLock : public ISync
{
    //mutex m;
public:
    virtual void Lock() {}
    virtual void UnLock() {}
};

int main()
{
    MutexLock m;
    s.setSync(&m);

    s.push_front(10);
}
