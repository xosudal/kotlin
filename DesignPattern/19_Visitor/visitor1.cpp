#include <iostream>
#include <list>
using namespace std;

// 방문자 패턴의 의도
// 객체 구조에 속한 요소에 수행할 operation을 정의하는 객체

int main()
{
    list<int> s = {1,2,3,4,5,6,7,8,9,10};

    // 모든 요소를 2배로 만들고 싶다

    // 1. 외부에서 모든 연산 수행

    for (auto& n : s) // 참조로
        n = n*2;

    // 2. 멤버 함수로 기능을 제공

    s.twice_all_element();
    s.show_all_element();

    // 3. 방문자 패턴 사용
    // linked list는 accept만 있어도 됨
    // member 함수를 추가하지 않아도(클래스 변경 X) 새로운 operation을 정의할 수 있다
    TwiceVisitor<int> tv; // 방문자.
    s.accept(&tv);

    ShowVisitor<int> sv;
    s.accept(&sv);

}
