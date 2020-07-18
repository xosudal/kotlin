/**
 * Decorator Pattern ( 상속 - 클래스 / 구성 - 객체 )
 * 구성(composition)을 통해 기능을 추가함
 * 클래스가 아닌 객체에 기능 추가함
 * 컴파일 시간이 아닌 실행 시간에 기능 추가
 *
 */

#include <iostream>
using namespace std;

class SpaceCraft
{
    int color;
    int speed;
public:
    void Fire() { cout << "Space Craft : -------->" << endl;}
};

// 구성(Composition) 을 통한 기능의 추가
class LeftMissile
{
    SpaceCraft* craft;
public:
    LeftMissile(SpaceCraft* p) : craft(p) {}
    void Fire()
    {
        craft->Fire(); // 기존 기능 수행
        cout << "Left Missile : >>>>>>>>>>>>" << endl;
    }
};

int main()
{
    SpaceCraft sc;
    sc.Fire();

    LeftMissile lm(&sc);
    lm.Fire(); 
}
