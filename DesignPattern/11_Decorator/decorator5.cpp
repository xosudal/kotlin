/**
 * Decorator Pattern ( 상속 - 클래스 / 구성 - 객체 )
 * left / right 는 공통의 특징이 있으니 또 기반 클래스를 만들어보자
 * 객체에 동적으로 새로운 서비스를 추가 할 수 있다
 * 기능 추가를 위해 서브 클래스 사용보다 더 융통성 있다고 볼 수 있다
 */

#include <iostream>
using namespace std;

struct Component
{
    virtual void Fire() = 0;
    virtual ~Component() {}
};

class SpaceCraft : public Component // Concrete Component
{
    int color;
    int speed;
public:
    void Fire() { cout << "Space Craft : -------->" << endl;}
};

// 기능추가 클래스의 공통의 기반 클래스
// Concrete Decorator
class IDecorator : public Component
{
    Component* craft;
public:
    IDecorator(Component* p) : craft(p) {}
    void Fire() {craft->Fire();}
};


class LeftMissile : public IDecorator
{
public:
    LeftMissile(Component* p) : IDecorator(p) {}
    void Fire()
    {
        IDecorator::Fire(); // 기존 기능 수행
        cout << "Left Missile : >>>>>>>>>>>>" << endl;
    }
};

class RightMissile : public IDecorator
{
    Component* craft;
public:
    RightMissile(Component* p) : IDecorator(p) {}
    void Fire()
    {
        IDecorator::Fire(); // 기존 기능 수행
        cout << "Right Missile : <<<<<<<<<<<<" << endl;
    }
};

int main()
{
    SpaceCraft sc;
    //sc.Fire();

    LeftMissile lm(&sc);
    //lm.Fire();

    //RightMissile rm(&sc);
    RightMissile rm(&lm); // 기능 추가된 객체에 기능 추가 필요
    rm.Fire();
}
