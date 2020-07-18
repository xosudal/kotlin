#include <iostream>
using namespace std;

// 3. thin template 기법
// 템플릿에 의한 코드 중복을 줄이기 위한 기술
// void* 등으로 내부 자료구조를 구성하고, 캐스팅을 위한 템플릿을 제공
// ex) Android Framework - Vector
// C++ Idioms

struct Node
{
    void* data;
    Node* next;
    Node(void* d, Node* n) : data(n), next(n) {}
};

class slistImp
{
    Node* head = 0;
public:
    void push_front(void* n) { head = new Node(n, head);}
    void* front() {return head->data;}
};

template<typename T> class slist : public slistImp
{
public:
    inline void push_front(T n) { slistImp::push_front((void*)n);}
    inline T front() {return (T)slistImp::front();}
};

int main()
{
    slist<int> s;
    s.push_front(10);

    int n = s.front();
}
