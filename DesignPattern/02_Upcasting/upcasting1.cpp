/**
 *  upcasting 개념
 *  기반 클래스 포인터에 파생클래스 주소를 담을 수 있다
 */

class Animal
{
    int age;
};

class Dog : public Animal
{
    int color;
};

int main()
{
    Dog d;

    Dog* p1 = &d;       // ok
    double* p2 = &d;    // error
    Animal* p3 = &d;    // ok. 중요함
}