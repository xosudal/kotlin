#include <iostream>
#include "ipcheader.hpp"
#include "ICalc.h" // interface를 통해 함수이름 일치 시키기

using namespace std;
using namespace ecourse;

using F = ICalc*(*)();

int main()
{
    // 동적 module load
    void* addr = ec_load_module("CalcProxy.dll");

    F f = (F)ec_get_fuction_address(addr, "CreateCalc");

    ICalc* pCalc = f(); // CreateCalc()

    cout << pCalc->Add(1,2) << endl;
    cout << pCalc->Sub(10,8) << endl;
}
