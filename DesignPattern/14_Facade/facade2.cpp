/**
 * 하나의 클래스는 하나의 책임만 지는 것이 좋다.
 * 하나의 클래스에 모든 기능 넣기 (X)
 * 기능별로 분리해서 클래스화 시키기 (O)
 */

#include <iostream>
#include <WinSock2.h>
using namespace std;

// 3개로 분리
// library 초기화 - NetworkInit
// IP 주소 관리 - IPAddress
// socket 프로그래밍의 일반적 함수 - Socket

int main()
{

    //1. 네트워크 라이브러리 초기화
    WSADATA w;
    WSAStartup(0x202, &w);

    //2. 소켓 생성
    int sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓

    //3. 소켓에 주소 지정
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(sock, (SOCKADDR*)&addr, sizeof(addr));

    //4. 소켓을 대기 상태로 변경
    listen(sock, 5);

    //5. 클라이언트가 접속할 때 까지 대기
    struct sockaddr_int addr2 = {0};
    int sz = sizeof(addr2);

    accept(sock, (SOCKADDR*)&addr2, &sz);

    //6. socket library cleanup
    WSACleanup();
}
