// validation 정책은 변경 가능해야함

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class Edit
{
    string data;
public:
    string getData()
    {
        data.clear();
        if (c==13) break;
        if (isdigit(c))
        {
            data.push_back(c);
            cout << c;
        }
        cout << endl;
        return data;
    }

};

int main()
{
    Edit edit;

    while(1)
    {
        string s = edit.getData();
        cout << s << endl;
    }
}
