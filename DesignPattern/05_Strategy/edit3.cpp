// validation 정책은 변경 가능해야함
// 변하지 않는 코드 안에 변해야 하는 부분은 분리 하는 것이 좋음
// isdigit(c) 를 분리하는 기법
// 변하는 것을 가상 함수 말고 클래스로 분리함
// 교체 가능하도록 해야함(약한 결합)
// IValidator 인터페이스 설계
// Strategy(전략 패턴)
// 구성(Composition)
// 정책 재 사용 및 실행시간에 교체 가능(client와 독립적으로 알고리즘 변경)
// 
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

//validation을 위한 interface
struct IValidator
{
    virtual bool validate(string s, char c) = 0;
    virtual bool iscomplete(string s) { return true; }
    //모든 기반 클래스는 가상 소멸자를 가져야 함
    virtual ~IValidator() {}
};

class Edit
{
    string data;
    IValidator* pVal = 0;
public:
    void setValidator(IValidator* p) { pVal = p; }

    virtual bool validate(char c)
    {
        return isdigit(c);
    }

    string getData()
    {
        data.clear();

        char c = getch();

        if (c==13 && (pVal==0 || pVal->iscomplete(data)) break;
        if (pVal == 0 || pVal->validate(data, c))
        {
            data.push_back(c);
            cout << c;
        }
        cout << endl;
        return data;
    }

};

class LimitDigitValidator : public IValidator
{
    int value;
public:
    LimitDigitValidator(int n) : value(n) {}

    virtual bool validate( string s, char c )
    {
        return s.size() < value && isdigit(c);
    }

    virtual bool iscomplete (string s)
    {
        return s.size() == value;
    }

}

int main()
{
    Edit edit;
    LimitDigitValidator v(5);
    edit.setValidator(&v);

    while(1)
    {
        string s = edit.getData();
        cout << s << endl;
    }
}
