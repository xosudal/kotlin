/**
 * function template 사용
 * C+11 부터 지원되는 일반화된 함수 포인터 역할을 하는 템플릿
 * functional include 해서 사용
 * 모든 함수를 다 담을 수 있음
 * bind와 같이 사용하면 인자도 고정할 수 있다
 *
 */

#include <iostream>
#include <functional>
using namespace std;

void foo() { cout << "foo" << endl; }
void goo(int n) { cout << "goo : " << n << endl; }

class Dialog
{
public:
    void Close() { cout << "Dialog Close" << endl; }
};

int main()
{
    function<void()> f;
    f = &foo;
    f(); // foo

    Dialog dlg;

    f = bind(&Dialog::Close,&dlg);
    f(); // dlg.Close()

    f = bind(&goo, 5);
    f(); // goo(5)
}
