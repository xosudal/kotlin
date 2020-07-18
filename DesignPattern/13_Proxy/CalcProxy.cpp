#include "ipcheader.hpp"
#include "ICalc.h" // interface를 통해 함수이름 일치 시키기

using namespace ecourse;

//Proxy를 동적 모듈로 제공하기

// Proxy 객체의 수명 관리 필요(new를 했으니 delete도 해야함)
// 참조 계수를 사용하는 것이 널리 사용된다
// 참조 계수를 사용하려면 ICalc 안에도 참조계수 관련 함수가 있어야 함
class Calc : public ICalc
{
    int server;
    int count = 0;
public:
    Calc() { server = ec_find_server("CalcService"); }
    ~Calc() { cout << "~Calc()" << endl; }

    void AddRef() {++count;}
    void Release() { if (--count == 0) delete this; }

    int Add(int a, int b) { return ec_send_server(server, 1, a, b);}
    int Sub(int a, int b) { return ec_send_server(server, 2, a, b);}
}


// 느슨한 결합을 제공하기 위해 동적 모듈 안에 있는 class를 생성하기 위해 약속된 함수를 제공
ICalc* CreateCalc()
{
    return new Calc;
}
