#include <iostream>
#include "ipcheader.hpp"
using namespace std;
using namespace ecourse;


// Proxy .. 
// 원격지의 서버를 대신 하는 클래스
// 명령 코드 대신 함수 호출을 가능하게 함(잘못된 명령코드를 사용하지 않게 됨)
// Client는 IPC에 대해서 알 필요는 없음
// 보안의 기능 추가 혹은 자주 사용되는 요청에 대한 캐시를 추가 할 수도 있음

// Proxy는 함수 호출을 명령 코드로 변경해서 서버에 전달
// Stub는 명령 코드를 다시 함수 호출로 변경 (server 내 dispatch 함수)
// Proxy와 Stub가 서로 통신함
class Calc
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
