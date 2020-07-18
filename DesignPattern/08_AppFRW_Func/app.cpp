// App Framework
#include <iostream>
using namespace std;

class CWinApp;

CWinApp* g_app = 0;

class CWinApp
{
public:
    CWinApp()   { g_app = this; }
    virtual bool InitInstance() { return false; }
    virtual bool ExitInstance() { return false; }
    virtual int  Run()          { return 0;     }
};

int main()
{
    if (g_app->InitInstance() == true)
        g_app->Run();

    g_app->ExitInstance();
}
//----------------------------
// Library + 사용자
// 1. CWinApp의 파생 클래스를 만들어야 함
// 2. 사용자 클래스를 전역객체 생성

class MyApp : public CWinApp
{
public:
    virtual bool InitInstance()
    {
        cout << "initialization" << endl;
        return true;
    }

    virtual bool ExitInstance()
    {
        cout << "finish" << endl;
        return true;
    }
};
MyApp theApp;

// 1.전역변수 생성자. 기반 클래스의 생성자
// 2.main함수 실행
