/**
 *  OCP : Open Close Principle
 *  기능 확장은 열려있고 코드 수정은 닫혀있어야 함
 *  새로운 기능이 추가되더라도 기존 코드 수정은 없도록 만들어야 함
 * 
 *  이를 해결하기 위해 모든 카메라가 따르는 규칙을 만든다
 *  제품을 먼저 만들지 않고, 제품의 인터페이스(규칙, 계약)을 먼저 설계 한다
 */

// 약한 결합의 예(Loosely Coupling)
// 객체는 상호 간에 인터페이스를 통해서 통신
// Client는 구현에 의존하지 않고 인터페이스에 의존한다

#include <iostream>
using namespace std;

class ICamera // 모든 카메라는 아래 인터페이스를 구현해야 한다
{
public:
    virtual void take() = 0;
    virtual ~ICamera() {}
};

/*
struct ICamera
{
    virtual void take() = 0;
};

*/

class Camera : public ICamera
{
public:
    void take() { cout << "take a picture" << endl; }
};

class HDCamera : public ICamera
{
public:
    void take() { cout << "take a HD picture" << endl; }
};

class People
{
public:
    void useCamera(ICamera* p)   {p->take();}   // 규칙대로 take를 사용하겠다라는 의미
                                                // 규칙을 준수하는 모든 camera는 사용 가능하다
                                                // 카메라가 추가 되더라도 코드 수정을 하지 않아도 됨
};

int main()
{
    People p;
    Camera c;
    p.useCamera(&c);

    HDCamera hc;
    p.useCamera(&hc);
}