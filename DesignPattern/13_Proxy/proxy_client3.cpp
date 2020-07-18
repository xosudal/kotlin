#include <iostream>
#include "ipcheader.hpp"
#include "ICalc.h" // interface를 통해 함수이름 일치 시키기

using namespace std;
using namespace ecourse;

// RPC(Remote Procedure Call) : 다른 프로세스에 있는 함수를 호출하는 개념
// pCalc의 Add를 호출하면 Server의 Add가 불린다
// Java는 Remote Method Invocation


//ICalc interface 사용으로 인해 Server Class와 proxy class가 동일한 함수를 가지고 있음을 보장
class Calc : public ICalc
{
    int server;
public:
    Calc() { server = ec_find_server("CalcService"); }

    int Add(int a, int b) { return ec_send_server(server, 1, a, b);}
    int Sub(int a, int b) { return ec_send_server(server, 2, a, b);}
}

int main()
{
    Calc* pCalc = new Calc;


    cout << pCalc->Add(1,2) << endl;
    cout << pCalc->Sub(10,8) << endl;
}
