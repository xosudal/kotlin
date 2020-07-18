#include <iotream>
#include <string>
using namespace std;

using Application = string;

class Director
{
    string name = "HONG";
    string phone = "010-1111-1111";
    string address = "SEOUL";

public:
    Application constructor()
    {
        Application app;
        app += name + "\n";
        app += phone + "\n";
        app += address + "\n";
        return app;
    }
};

int main()
{
    Director d;
    Application app = d.construct();
    cout << app << endl;
}
