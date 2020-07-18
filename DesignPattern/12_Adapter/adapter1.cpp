/**
 * 도형편집기에서 TextView를 사용하려면... 다중 상속 사용
 * Adapter Pattern : 한 클래스(혹은 객체)의 인터페이스를 클라이언트에서 사용하고자 하는 다른 인터페이스로 변환한다
 * 호환성 때문에 사용할 수 없었던 클래스를 연결해서 사용할 수 있다.
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

//TextView를 도형편집기에서 사용하기 위해 
//인터페이스를 변경(함수 이름을 변경해주었음)
class Text : public TextView, public Shape
{
    Text(string s) : TextView(s) {}

    virtual void Draw() { TextView::Show(); }
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl; }
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Draw Circle" << endl; }
};

int main()
{
    vector<Shape*> v;

    v.push_back(new Rect);
    v.push_back(new Circle);
    v.push_back(new Text("hello"));

    for(auto p : v)
        p->Draw();
}
