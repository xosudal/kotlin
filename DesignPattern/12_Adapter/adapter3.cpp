/**
 * Container adapter : sequence container(list, vector)의 인터페이스를 수정해서 stack/queue/priority_queue 를 지원
 * Class Adapter이다
 */

#include <iostream>
#include <list>
using namespace std;

// stack 만들기
// list의 함수 이름을 stack처럼 보이도록 변경하기

/*
template<typename T> class Stack : public list<T>
{

public:
    void push(const T& a) {list<T>::push_back(a);} // 기존 함수를 push처럼 동작하게끔 만든다
    void pop (const T& a) {list<T>::pop_back(a);}
    T& top() {return list<T>::back();}
};
*/

template< typename T, typename C = deque<T> > class Stack
{
    C st;
    //vector<T> v;
public:
    void push(const T& a) {st.push_back(a);} // 기존 함수를 push처럼 동작하게끔 만든다
    void pop (const T& a) {st.pop_back(a);}
    T& top() {return st.back();}
};

int main()
{
    Stack<int> s;
    Stack<int, list<int>> s;
    Stack<int, vector<int>> s;
    s.push(10);
    s.push(20);

    s.push_front(20); // 가능함. list를 public 상속 받았기 때문에
                      // 해결법 1 : list를 private로 상속받음
                      // 해결법 2 : 상속받지 말고 포함해서
    cout << s.top() << endl; // 20
}
