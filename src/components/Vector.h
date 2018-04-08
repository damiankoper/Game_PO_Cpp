#pragma once
#include <SDL.h>
class Vector
{
  public:
    Vector();
    Vector(double x, double y);
    Vector operator+(const Vector v);
    Vector operator+=(const Vector v);
    Vector operator*(const int i);
    Vector operator*(const double i);
    Vector operator/(const double i);
    bool operator==(const Vector v);
    bool operator==(const double i);
    bool operator!=(const int i);
    void resetNonZero(Vector v);
    bool operator<(const Vector v);
    double x, y;
};