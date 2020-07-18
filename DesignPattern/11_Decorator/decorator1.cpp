/**
 * Decorator Pattern
 * 실행시간에 객체에 기능을 추가 할 때 사용하는 패턴
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

int main()
{
    SpaceCraft sc;
    sc.Fire();
}
