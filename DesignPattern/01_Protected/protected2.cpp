/**
 *  소멸자를 protected로 선언함으로써 스택에 생성 못하게 함
 *  heap 에는 생성 가능하지만 바로 소멸자를 부르지는 못함
 *  member함수 호출을 통해 가능하도록 하는 기법
 */
class Cat
{
public:
    Cat () {}

    void Destory()
    {
        delete this;
    }

protected:
    ~Cat () {}
};

int main()
{
    Cat c;              // error
    Cat* c1 = new Cat;  // heap ok
    delete c1;          // error
    c1->Destory();      // ok
}
