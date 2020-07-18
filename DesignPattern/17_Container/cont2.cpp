#include <iostream>
using namespace std;

// data의 type을 다양하게 저장하는 방법

// 1. 기반 클래스의 포인터를 저장하는 container
// 장점 : 코드 메모리가 증가 하지 않음
// 단점 : 1. 타입 안정성이 떨어진다
//        2. 꺼낼 때 캐스팅이 필요하다
//        3. primitive type을 저장할 수 없음(Integer 같은 class 필요)

struct Object
{
    virtual ~Object() {}
};

class Point : public Object
{
};

class Dialog : public Object
{
};

struct Node
{
    Object* data;
    Node* next;
    Node(Object* d, Node* n) : data(n), next(n) {}
};

class slist
{
    Node* head = 0;
public:
    void push_front(Object* n) { head = new Node(n, head);}
    Object* front() {return head->data;}
};

int main()
{
    slist s;
    s.push_front(new Point);
    s.push_front(new Dialog); // error X, 안정성 떨어짐
    Point* p = static_cast<Point*>(s.front());
}
