// Java, C#은 인터페이스 기반
// C++ 템플릿 기반


#include <iostream>
using namespace std;

template<typename T> struct Node
{
	T data;
	Node* next;
	Node(const T& d, Node* n) : data(d), next(n) {}
};

template<typename T> struct IEnumerator
{
	virtual ~IEnumerator() {}
	virtual bool MoveNext() = 0;
	virtual T& GetObject() = 0;
	// C# 2.0 에서부터는 template으로 구현 됨
};

// list의 반복자

template<typename T> class SlistEnumerator : public IEnumerator<T>
{
	Node<T>* current = 0;
public:
	SlistEnumerator(Node<T>* p = 0) : current(p) {}
	virtual bool MoveNext()
	{
		current = current->next; 
		return current;
	}
	virtual T& GetObject() { return current->data;}
};

template<typename T> struct IEnumerable
{
	virtual ~IEnumerable() {}
	virtual IEnumerator<T>* GetEnumerator() = 0;
};

template<typename T> class slist : public IEnumerable<T>
{
	Node<T>* head = 0;
public:
	virtual IEnumerator<T>* GetEnumerator()
	{
		return new SlistEnumerator<T>(head);
	}
	void push_front(const T& n) { head = new Node<T>(n, head);}
	T front()					{ return head->data;}
};

template<typename T> Show( IEnumerator<T>* p)
{
	do {
		cout << p->GetObject() << endl;
	} while (p->MoveNext());
};

// C++ 관점에서 인터페이스 구현의 단점
// 1. Show 함수에 배열을 전달 할 수 없다
// 2. 반복자는 new를 만들어내므로 delete를 해야함
// 3. 요소 접근/이동 함수는 가상함수로 오버헤드가 있다
// 따라서 C++에서는 STL 방식으로 만든다

int main()
{
	slist<int> s;
	
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	s.push_front(40);
	
	IEnumerator<int>* p = s.GetEnumerator();
	
	int n = p->GetObject(); // 40
	cout << n << endl;
	p->MoveNext();
	
	cout << p->GetObject() << endl; // 30
	
	Show(p);
	delete p;
}