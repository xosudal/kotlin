// ICalc.h

// 모든 Proxy Class들은 Add,Release를 사용하므로
// 아래와 같이 기반클래스를 만들어서 상속하도록 한다
struct IRefCount
{
    virtual void AddRef() = 0;
    virtual void Release() = 0;
    virtual ~IRefCount() {}
};

struct ICalc : public IRefCount
{
    virtual int Add(int a, int b) = 0;
    virtual int Sub(int a, int b) = 0;
    virtual ~ICalc() {}
;
