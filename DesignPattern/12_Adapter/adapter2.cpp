/**
 * class adapter : class I/F 변경, 다중 상속 혹은 값으로 ... 이미 존재하던 인터페이스는 변경 불가
 * object adapter : 객체의 인터페이스 변경. 구성(composition)을 주로 사용. 기본 객체를 포인터 또는 참조로 포함한다
 */

#include <iostream>
#include <vector>
#include "01_TextView.h"
using namespace std;

class Shape
{
public:
    virtual void Draw() {cout << "Draw Shape" << endl;}
};


// TextView 클래스의 인터페이스를 도형 편집기에 맞도록 수정
class Text : public TextView, public Shape
{
    Text(string s) : TextView(s) {}

    virtual void Draw() { TextView::Show(); }
};

// object adapter
class ObjectAdapter : public Shape
{
    TextView* pView; // pointer 핵심
public:
    ObjectAdapter(TextView* p) : pView(p) {}

    virtual void Draw() { pView->Show(); }
};

int main()
{
    TextView tv("world"); // 이미 존재하던 객체

    vector<Shape*> v;

    v.push_back(&tv); // error. Shape의 파생 클래스가 아님

    v.push_back(new ObjectAdapter(&tv));

    v.push_back(new Text("hello"));

    for(auto p : v)
        p->Draw();
}
