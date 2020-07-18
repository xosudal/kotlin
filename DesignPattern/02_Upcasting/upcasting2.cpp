#include <iostream>
using namespace std;

class Animal
{
    int age;
public:
    void Cry() { cout << "cry animal" << endl; }
};

class Dog : public Animal
{
    int color;

public:
    //override
    void Cry() { cout << "cry dog"<< endl; }
};

int main()
{
    Dog d;

    Animal* p = &d;
    p->Cry();   // virtual 없으면 animal이 불림
                // virtual 이 있으면 dog가 불림
}