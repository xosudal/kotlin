#include <iotream>
#include <string>
using namespace std;

using Application = string;

// 복잡한 객체를 생성하는 방법과 표현하는 방법을 정의하는 클래스를
// 별도로 분리하여 서로 다른 표현이라도 이를 생성할 수 있는
// 동일한 구축 공정을 제공

// 전략패턴과 다른점.. builder는 객체를 생성, 전략패턴은 알고리즘 변경
// 의도가 다르다..

// 지원서의 각 단계의 표현을 만드는 빌더 인터페이스
struct IBuilder
{
    virtual ~IBuilder() {}
    virtual void makeName(string name) = 0;
    virtual void makePhone(string phone) = 0;
    virtual void makeAddress(string addr) = 0;

    virtual Application getResult() = 0;
};


class Director
{
    string name = "HONG";
    string phone = "010-1111-1111";
    string address = "SEOUL";
    IBuilder* pBuilder;
public:
    void setBuilder(IBuilder* p) {pBuilder = p;}
    Application constructor()
    {
        pBuilder->makeName(name);
        pBuilder->makePhone(phone);
        pBuilder->makeAddress(address);
        return pBuilder->getResult();
    }
};

class TextBuilder : public IBuilder
{
    Application app;
public:
    virtual void makeName(string name)
    {
        app += name + "\n";
    }
    virtual void makePhone(string phone)
    {
        app += phone + "\n";
    }
    virtual void makeAddress(string addr)
    {
        app += addr + "\n";
    }
    virtual Application getResult() {return app;}
};

int main()
{
    Director d;
    TextBuilder tb;
    Application app;
    d.setBuilder(&tb);
    app = d.constructor();
}
