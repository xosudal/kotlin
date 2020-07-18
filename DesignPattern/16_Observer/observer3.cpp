/**
 * 변경된 data를 전달하는 방법
 * 1. 변화를 통보할 때 같이 전달 - push
 * 2. 변화 되었다는 사실만 전달, graph에서 table 멤버 함수를 통해 접근 - pull
 *
 */

#include <iostream>
#include <vector>
using namespace std;

class Subject;

struct IGraph
{
    virtual void update(Subject*) = 0;

    virtual ~IGraph() {}
};

class Subject
{
    vector<IGraph*> v;
public:
    void attach(IGraph* p) { v.push_back(p); }
    void detach(IGraph* p) { }
    void notify()
    {
        for (auto p : v)
            p->update(this);
    }
};

class Table : public Subject
{
    int data;
public:
    int GetData() {return data;}
    void SetData(int d)
    {
        data = d;
        notify(data);
    }
};

class Table3D : public Subject
{
    int data[10];
public:
    void SetData(int d)
    {
        data = d;
    }
};

class PieGraph : public IGraph
{
public:
    virtual void update(Subject* p)
    {
        //table에 접근해서 data를 꺼내온다
        int n = static_cast<Table*>(p)->GetData();
        Draw(n); // 그래프 다시 그리기
    }
    void Draw(int n)
    {
        cout << "Pie Graph : ";
        for (int i=0; i<n; i++)
            cout << "*";
        cout << endl;
    }

};

class BarGraph : public IGraph
{
public:
    virtual void update(int n)
    {
        int n = static_cast<Table*>(p)->GetData();
        Draw(n); // 그래프 다시 그리기
    }
    void Draw(int n)
    {
        cout << "Bar Graph : ";
        for (int i=0; i<n; i++)
            cout << "+";
        cout << endl;
    }

};

int main()
{
    BarGraph bg;
    PieGraph pg;

    Table t;
    t.attach(&bg);
    t.attach(&pg);

    while(1)
    {
        int n;
        cin >> n;
        t.SetData(n);
    }
}
