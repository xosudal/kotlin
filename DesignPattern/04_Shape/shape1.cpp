/**
 *  예제 : 도형만들기
 *  1. 모든 도형을 type으로 설계
 *  2. 모든 도형의 공통의 기반 클래스가 있으면 모든 도형을 하나의 container에 담아서 관리 가능 (Shape 구현)
 *  3. 파생클래스에서 재정의 하게 되는 함수는 반드시 가상함수로 만들어야 한다
 *
 */
#include <iostream>
#include <vector>
using namespace std;

class Shape
{
public:
    virtual void Draw() {cout << "Draw Shape" << endl;}
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
    //vector<Rect*> r;
    //vector<Circle*> c;
    //위와 같이 vector를 만들어 관리하면 제대로 되지 않음
    //기반 클래스를 만들어 관리
    vector<Shape*> v;

    while (1)
    {
        int cmd;
        cin >> cmd;
        if ( cmd == 1 ) v.push_back(new Rect);
        else if (cmd == 2) v.push_back(new Circle);
        else if (cmd == 9)
        {
            for(auto p : v)
                p->Draw();
        }
    }
}