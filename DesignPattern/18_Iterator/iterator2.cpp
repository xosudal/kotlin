// 모든 종류의 컨테이너를 위한 반복자는 사용법이 동일해야 함 - 인터페이스 필요

#include <iostream>
using namespace std;

template<typename T> struct Node
{
	T data;
	Node* next;
	Node(const T& d, Node* n) : data(d), next(n) {}
};

struct IEnumerator
{
	virtual ~IEnumerator() {}
	virtual bool MoveNext() = 0;
	virtual Object GetObject() = 0;
	// C# 1.0 에서는 object 사용
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

// 모든 컨테이너에서는 반복자를 꺼낼 수 있어야 함
// 컨테이너가 지켜야하는 인터페이스
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
}