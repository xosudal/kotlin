/**
 * facade 객체 : 사용자가 사용하기 쉽게 하기위해 서브 시스템을 합성하는 다수 인터페이스의 객체로 구성
 * 포괄적 개념의 인터페이스를 제공함
 */

#include <iostream>
#include <WinSock2.h>
using namespace std;

// 3개로 분리
// library 초기화 - NetworkInit
// IP 주소 관리 - IPAddress
// socket 프로그래밍의 일반적 함수 - Socket

// 더 간단하게 하기 위해 하나의 클래스로 구성
class TCPServer
{
    NetworkInit init;
    Socket sock;
public:
    TCPServer() : sock(SOCK_STREAM) {}

    void Start(const char* sip, short port)
    {
        IPAddress ip(sip, port);
        sock.Bind(&ip);
        sock.Listen();
        sock.Accept();
    }
};

int main()
{
    TCPServer server;
    server.Start("127.0.0.1", 4000);
}
