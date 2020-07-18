/**
 * Table 자체 Data 관리 말고 관찰자 패턴을 위한 코드는 동일하다
 * 관찰자 패턴을 제공하는 기반 클래스 제공(vector, attach, detach)
 */

#include <iostream>
#include <vector>
using namespace std;

struct IGraph
{
    virtual void update(int) = 0;

    virtual ~IGraph() {}
};

class Subject
{
    vector<IGraph*> v;
public:
    void attach(IGraph* p) { v.push_back(p); }
    void detach(IGraph* p) { }
    void notify(int data)
    {
        for (auto p : v)
            p->update(data);
    }
};

class Table : public Subject
{
    int data;
public:
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
    virtual void update(int n)
    {
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
