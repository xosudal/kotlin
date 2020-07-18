/**
 * Decorator Pattern
 * 1. 상속을 통해 기능을 추가
 * 객체가 아닌 클래스에 기능을 추가
 * 실행 시간이 아닌 코드 작성시에 기능이 추가
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

// 상속을 통한 기능의 추가
class LeftMissile : public SpaceCraft
{
public:
    void Fire()
    {
        SpaceCraft::Fire(); // 기존 기능 수행
        cout << "Left Missile : >>>>>>>>>>>>" << endl;
    }
};

int main()
{
    SpaceCraft sc;
    sc.Fire();

    LeftMissile lm;
    lm.Fire(); // sc와 관계없는 또 다른 객체가 생성됨(우주선 총 2대 됨)
               // 기능이 추가된 새로운 객체가 생김
}
