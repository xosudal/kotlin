/**
 *  예제 : 도형만들기
 *  1. 모든 도형을 type으로 설계
 *  2. 모든 도형의 공통의 기반 클래스가 있으면 모든 도형을 하나의 container에 담아서 관리 가능 (Shape 구현)
 *  3. 파생클래스에서 재정의 하게 되는 함수는 반드시 가상함수로 만들어야 한다
 *  4. 다형성 - 동일한 함수(method)호출이 상황(class)에 따라 다르게 동작
 *  5. copy&paste 기능 추가     1) type 코드를 추가 (class 에서 type 설정)
 *                             2) 가상함수 사용 (Clone) - OCP를 만족한다
 *                             // Prototype Pattern이라고 불리는 design pattern 이다
 *                             // 어떤 객체의 복사본을 만들어야 할 때 사용한다
 *
 *  6. template Method
 *     Draw가 multi-thread 환경에서 안전하지 않다고 가정  1) mutex lock/unlock은 공통적으로 수행되어야 하고, Draw는 파생 객체가 알아서 수행
 *                                                     2) 따라서 변하는 것을 가상함수로 뽑아냄
 *                                                     // template Method
 *                                                     // 공통/변하지 않는 부분은 기반 클래스에서 제공 (public, final)
 *                                                     // 각 도형별로 변하는 부분은 가상함수 (private, protected) 로 제공해서 재 정의 가능하도록
 *  
 */

#include <iostream>
#include <vector>
using namespace std;

class Shape
{
protected:
    virtual void DrawImp()
    {
        cout << "Draw Shape" << endl;
    }

public:
    virtual void Draw() final // 파생클래스가 재 정의 못하도록 final 추가
    {
        cout << "mutex lock" << endl;
        DrawImp();
        cout << "mutex unlock" << endl;
    }

    // 자신의 복사본을 만드는 가상함수
    virtual Shape* Clone() { return new Shape(*this);}
};

class Rect : public Shape
{
public:
    virtual void DrawImp() { cout << "Draw Rect" << endl; }
    virtual Shape* Clone() { return new Rect(*this);}
};

class Circle : public Shape
{
public:
    virtual void DrawImp() { cout << "Draw Circle" << endl; }
    virtual Shape* Clone() { return new Circle(*this);}
};

int main()
{
    vector<Shape*> v;

    while (1)
    {
        int cmd;
        cin >> cmd;

        if ( cmd == 1 ) v.push_back(new Rect);
        else if (cmd == 2) v.push_back(new Circle);
        else if (cmd == 8) // copy & paste 기능
        {
            cout << "index : ";
            int k;
            cin >> k;
            // k번째 도형의 복사본을 v에 추가한다

            v.push_back(v[k]->Clone()); // Q. v의 k번째 도형의 복사본을 만들어서 붙여넣어라, A. 다형성으로 구현
        }
        else if (cmd == 9)
        {
            for(auto p : v)
                p->Draw();  // 다형성(객체가 누구를 가리키느냐에 따라 다른 함수를 호출)
        }
    }
}