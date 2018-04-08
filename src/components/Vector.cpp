#include "Vector.h"
#include <cmath>
Vector Vector::operator+(const Vector v)
{
    return Vector(x + v.x, y + v.y);
}
Vector Vector::operator+=(const Vector v)
{
    x += v.x;
    y += v.y;
}
Vector Vector::operator*(const int i)
{
    return Vector(x * i, y * i);
}
Vector Vector::operator*(const double i)
{
    return Vector(x * i, y * i);
}
Vector Vector::operator/(const double i)
{
    return Vector(x / i, y / i);
}
bool Vector::operator<(const Vector v)
{
    return sqrt(x * x + y * y) < sqrt(v.x * v.x + v.y * v.y);
}
bool Vector::operator==(const Vector v)
{
    return sqrt(x * x + y * y) == sqrt(v.x * v.x + v.y * v.y);
}
bool Vector::operator==(const double i)
{
    return sqrt(x * x + y * y) == i;
}
bool Vector::operator!=(const int i)
{
    return sqrt(x * x + y * y) != i;
}
void Vector::resetNonZero(Vector v){
    if(v.x!=0){
        x = 0;
    }
    if(v.y!=0){
        y = 0;
    }
}
Vector::Vector(double x, double y) : x(x), y(y) {}
Vector::Vector() {}