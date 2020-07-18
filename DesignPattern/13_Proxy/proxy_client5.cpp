#include <iostream>
#include "ipcheader.hpp"
#include "ICalc.h" // interface를 통해 함수이름 일치 시키기
using namespace std;
using namespace ecourse;

using F = ICalc*(*)();

// ICalc를 smart pointer로 만들자 그러면 호출할 필요가 없음
// AddRef 와 Release를 자동으로 호출하도록...

template<typename T> class smartptr
{
    T* obj;
public:
    smartptr(T* p = 0) : obj(p)
    {
        if(obj != 0) obj->AddRef();
    }

    smartptr(const smartptr& p) : obj(p.obj)
    {
        if (obj!=0) obj->AddRef();
    }
    ~smartptr()
    {
        if (obj!=0) obj->Release();
    }

    T* operator->() { return obj;}
    T& operator*() { return *obj;}
};

int main()
{
    // 동적 module load
    void* addr = ec_load_module("CalcProxy.dll");

    F f = (F)ec_get_fuction_address(addr, "CreateCalc");

    smartptr<ICalc> pCalc = f();
    //ICalc* pCalc = f(); // CreateCalc()

    cout << pCalc->Add(1,2) << endl;
    cout << pCalc->Sub(10,8) << endl;
}
