/**
 * Decorator Pattern ( 상속 - 클래스 / 구성 - 객체 )
 * space / left / right 모두 포함하는 기반 클래스를 생성하자
 * 우주선과 기능 추가 객체는 동일 기반 클래스를 가져야한다 
 *
 */

#include <iostream>
using namespace std;

struct Component
{
    virtual void Fire() = 0;
    virtual ~Component() {}
};

class SpaceCraft : public Component
{
    int color;
    int speed;
public:
    void Fire() { cout << "Space Craft : -------->" << endl;}
};

// 구성(Composition) 을 통한 기능의 추가
class LeftMissile : public Component
{
    Component* craft;
public:
    LeftMissile(Component* p) : craft(p) {}
    void Fire()
    {
        craft->Fire(); // 기존 기능 수행
        cout << "Left Missile : >>>>>>>>>>>>" << endl;
    }
};

class RightMissile : public Component
{
    Component* craft;
public:
    RightMissile(Component* p) : craft(p) {}
    void Fire()
    {
        craft->Fire(); // 기존 기능 수행
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
