#include <iostream>
#include "point.h"

Point::Point(int a, int b) : x(a), y(b) {}

void Point::Print() const
{
    cout << x << ", " << y << endl;
}
