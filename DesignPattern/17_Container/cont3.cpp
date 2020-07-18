#include <iostream>
using namespace std;

// 2. Template로 만들기
// 장점 : 1. type 안정성이 뛰어나다
//        2. 캐스팅이 필요없다
//        3. primitive type 저장 가능
// 단점 : 코드 메모리가 증가함
template<typename T> struct Node
{
    T data;
    Node* next;
    Node(const T& d, Node* n) : data(n), next(n) {}
};

template<tynename T> class slist
{
    Node* head = 0;
public:
    void push_front(const T& n) { head = new Node<T>(n, head);}
    T front() {return head->data;}
};

int main()
{
    slist<int> s;
    s.push_front(10);
}
