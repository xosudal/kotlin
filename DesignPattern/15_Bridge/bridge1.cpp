#include <iostream>
using namespace std;

struct IMp3
{
    virtual void PlayOneMinute() = 0; // 모든 class가 변경되어야 함
    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtual ~IMp3() {}
};

class IPod : public IMp3
{
public:
    void Play() { cout << "Play Mp3" << endl;}
    void Stop() { cout << "Stop Mp3" << endl;}
};

class People
{
public:
    void UseMp3(IMp3* p)
    {
        p->Play();
        p->PlayOneMinute(); // 새로운 기능 추가
    }
};

int main()
{

}
