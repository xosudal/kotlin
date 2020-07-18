// 생성자를 protected로 선언함으로써 기반 클래스를 생성하지 못하게 하는 기법
class Animal
{
protected:
    Animal() {}
};

class Dog : public Animal
{
public:
    Dog() {}    // Dog() : Animal() {}
                // complier에서 위와 같이 animal 생성자를 추가해줌
                // 따라서 Dog d 호출 시 Dog가 일단 먼저 불리고 Animal 생성자가 호출되는 것임
};


int main()
{
    Animal a;   // error
    Dog d;      // ok
}
