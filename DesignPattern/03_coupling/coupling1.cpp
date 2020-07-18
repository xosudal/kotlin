/**
 *  OCP : Open Close Principle
 *  기능 확장은 열려있고 코드 수정은 닫혀있어야 함
 *  새로운 기능이 추가되더라도 기존 코드 수정은 없도록 만들어야 함
 */

// 강한 결합의 예(Tightly Coupling)
// 객체가 서로 상호 작용 할 때 서로에 대해 잘 알고 있는 것 (Class 이름 등)
// 교체/확장이 불가능한 경직된 Design Pattern

#include <iostream>
using namespace std;

class Camera
{
public:
    void take() { cout << "take a picture" << endl; }
};

class HDCamera
{
public:
    void take() { cout << "take a HD picture" << endl; }
};

class People
{
public:
    void useCamera(Cemara* p)   {p->take();}
    void useCamera(HDCamera* p) {p->take();} // HD Camera 추가로 인해 기존 코드가 수정되는 불편함이 있음
};

int main()
{
    People p;
    Camera c;
    p.useCamera(&c);

    HDCamera hc;
    p.useCamera(&hc);
}