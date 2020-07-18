/**
 * iterator adapter : 다양한 알고리즘을 역순으로 사용할 수 있음
 */

#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

int main()
{
    list<int> s = {1,2,3,4};

    auto p1 = s.begin();
    auto p2 = s.end();

    // ++ 하면 다음인데 감소되도록 바꿔줌(역순으로 가능하도록)
    // 기본 반복자의 동작을 거꾸로 하게 하는 adapter
    reverse_iterator<list<int>::iterator> p3(p2); // --p2로 초기화됨
    reverse_iterator<list<int>::iterator> p4(p1); // --p1로 초기화됨

    for_each( p1, p2, [](int a) { cout << a << endl;});
    cout << endl;
    for_each( p3, p4, [](int a) { cout << a << endl;});
    
}
