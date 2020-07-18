#include <iostream>
using namespace std;


//bridge pattern : 구현과 추상과 개념을 분리해서 각각을 독립적으로 변경할 수 있게 함
struct IMp3
{
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

class Mp3
{
    IMp3* pImpl;
public:
    Mp3()
    {
        pImpl =  new Ipod;
    }
    void Play() {pImpl->Play();}
    void Stop() {pImpl->Stop();}
    void PlayOneMinute() // bridge!
    {
        pImpl->Play();
        Sleep(1);
        pImpl->Stop();
    }
};

class People
{
public:
    void UseMp3(Mp3* p)
    {
        p->Play();
        p->PlayOneMinute(); // 새로운 기능 추가
    }
};

int main()
{

}
