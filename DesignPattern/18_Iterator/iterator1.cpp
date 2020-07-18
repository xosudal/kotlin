// container의 자료구조에 상관없이 동일하게 열거할 수 있는 방법
// 열거자 라고도 함 (Enumerator)

#include <iostream>
using namespace std;

template<typename T> struct Node
{
	T data;
	Node* next;
	Node(const T& d, Node* n) : data(d), next(n) {}
};

template<typename T> class slist
{
	Node<T>* head = 0;
public:
	void push_front(const T& n) { head = new Node<T>(n, head);}
	T front()					{ return head->data;}
};

int main()
{
	slist<int> s;
	
}