/**
 *  예제 : 도형만들기
 *  1. 모든 도형을 type으로 설계
 *  2. 모든 도형의 공통의 기반 클래스가 있으면 모든 도형을 하나의 container에 담아서 관리 가능 (Shape 구현)
 *  3. 파생클래스에서 재정의 하게 되는 함수는 반드시 가상함수로 만들어야 한다
 *  4. 다형성 - 동일한 함수(method)호출이 상황(class)에 따라 다르게 동작
 *  5. copy&paste 기능 추가 : 1) type 코드를 추가 (class 에서 type 설정)
 *  
 *
 */
#include <iostream>
#include <vector>
using namespace std;

class Shape
{
public:
    virtual void Draw() { cout << "Draw Shape" << endl; }

    // 자신의 복사본을 만드는 가상함수
    // 복사 생성자 호출을 통해 복사본이 만들어진다
    virtual Shape* Clone() { return new Shape(*this);}
};

class Rect : public Shape
{
public:
    virtual void Draw() { cout << "Draw Rect" << endl; }
    virtual Shape* Clone() { return new Rect(*this);}
};

class Circle : public Shape
{
public:
    virtual void Draw() { cout << "Draw Circle" << endl; }
    virtual Shape* Clone() { return new Circle(*this);}
};

class Triangle : public Shape
{
public:
    virtual void Draw() { cout << "Draw Triangle"<< endl; }
}

int main()
{
    vector<Shape*> v;

    while (1)
    {
        int cmd;
        cin >> cmd;

        if ( cmd == 1 ) v.push_back(new Rect);
        else if (cmd == 2) v.push_back(new Circle);
        else if (cmd == 3) v.push_back(new Triangle);
        else if (cmd == 8) // copy & paste 기능
        {
            cout << "index : ";
            int k;
            cin >> k;
            // k번째 도형의 복사본을 v에 추가한다
        }
        else if (cmd == 9)
        {
            for(auto p : v)
                p->Draw();  // 다형성(객체가 누구를 가리키느냐에 따라 다른 함수를 호출)
        }
    }
}
