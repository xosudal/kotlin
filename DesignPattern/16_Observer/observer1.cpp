/**
 * 하나의 data 변경 시 연결되어 있는 객체들이 자동으로 update 되도록
 * 1. 변화를 관찰 ( 무한 loop)
 * 2. 변화를 알려줌
 * 객체 사이의 1:N의 종속성을 정의하고 한 객체의 상태가 변하면 종속된 다른 객체에 통보가 가고 자동으로 수정
 * 관찰자(Observer) / 관찰자의 대상(Subject)
 */

#include <iostream>
#include <vector>
using namespace std;

class Table
{
    int data;
public:
    void SetData(int d) { data = d; }

};

class PieGraph
{
public:
    void Draw(int n)
    {
        cout << "Pie Graph : ";
        for (int i=0; i<n; i++)
            cout << "*";
    }

};

int main
{

}
