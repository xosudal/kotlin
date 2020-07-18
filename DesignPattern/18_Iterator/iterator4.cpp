// STL 방식의 반복자
// 1. 인터페이스 사용하지 않음
// 2. 이동 / 접근 시 포인터 규칙에 따름(++/*)
// 3. 이동 및 접근은 inline으로 선언

// 컨테이너의 규칙
// 약속된 함수로 만든다(begin)
// 반복자는 동적으로 생성하지 않고 값 형식으로 리턴한다

#include <iostream>
using namespace std;

template<typename T> struct Node
{
	T data;
	Node* next;
	Node(const T& d, Node* n) : data(d), next(n) {}
};

// list의 반복자

template<typename T> class slist_iterator
{
	Node<T>* current = 0;
public:
	slist_iterator(Node<T>* p = 0) : current(p) {}
	inline slist_iterator& operator++()
	{
		current = current->next;
		return *this;
	}
	inline T& operator*() { return current->data; }
};

template<typename T> class slist
{
	Node<T>* head = 0;
public:
	slist_iterator<T> begin()
	{
		return slist_iterator<T>(head);
	}
	void push_front(const T& n) { head = new Node<T>(n, head); }
	T front() { return head->data; }
};

// p = begin , p2 = end
template<typename T> Show(T p, T p2)
{
	do {
		cout << "show : " << *p << endl;
	} while (++p != p2);
};

int main()
{
	slist<int> s;

	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	s.push_front(40);

	slist_iterator<int> p = s.begin();

	int n = *p; // 40
	cout << n << endl;
	++p;

	cout << *p << endl; // 30
}