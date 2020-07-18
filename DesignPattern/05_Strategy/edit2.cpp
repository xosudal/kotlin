// validation 정책은 변경 가능해야함
// 변하지 않는 코드 안에 변해야 하는 부분은 분리 하는 것이 좋음
// isdigit(c) 를 분리하는 기법
// 변해야 하는 부분을 별도의 가상 함수로 분리함
// template method 적용
// 알고리즘의 여러 단계중 일부는 서브 클래스 에서 구현
// hook-method (파생클래스가 재 정의하는 method)
// 알고리즘의 전체 구조를 유지하면서 서브 클래스에서 특정 단계를 재 정의함

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class Edit
{
    string data;
public:

    virtual bool validate(char c)
    {
        return isdigit(c);
    }

    string getData()
    {
        data.clear();

        char c = getch();

        if (c==13) break;
        if (validate(c))
        {
            data.push_back(c);
            cout << c;
        }
        cout << endl;
        return data;
    }

};

class AddressEdit : public Edit
{
public:
    virtual bool validate(char c)
    {
        return true;
    }
};


int main()
{
    Edit edit;

    AddressEdit edit2; // 모든 것 입력 가능

    while(1)
    {
        string s = edit.getData();
        cout << s << endl;
    }
}
