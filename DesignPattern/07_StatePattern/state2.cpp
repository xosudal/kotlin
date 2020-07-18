//비효율적임

#include <iostream>
using namespace std;

class Character
{
    int gold = 0;
    int item = 0;
public:
    void run()
    {
        if (item == 1)
            cout << "run" << endl;
        else (item == 2)
            cout << "fast run" << endl;
    }
    void attack()
    {
        if (item == 1)
            cout << "attack" << endl;
        else if (item == 2)
            cout << "strong attack" << endl;
    }
};

int main()
{
    Character *p = new Character;
    p->run();
    p->attack();
}
