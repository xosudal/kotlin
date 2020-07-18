#include <iostream>
using namespace std;

struct Node
{
    int data; // 다양한 타입을 어떻게 보관해야할까
    Node* next;
    Node(int d, Node* n) : data(n), next(n) {}
};

class slist
{
    Node* head = 0;
public:
    void push_front(int n) { head = new Node(n, head);}
    int front() {return head->data;}
};

int main()
{
    slist s;
    s.push_front(10);
}
