// PIMPL(Pointer to Implementation)
// 컴파일 속도를 향상 시킴
// 완벽한 정보 은닉이 가능(header를 감출 수 있다)
class pointImpl;

class Point
{
    pointImpl* pImpl; // 전방 선언했으므로 header include 필요 X
public:
    Point (int a=0, int b=0);
    
    void Print() const;
}
