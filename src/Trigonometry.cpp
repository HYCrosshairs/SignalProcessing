#include "Trigonometry.hpp"

using namespace maths::trig;

Trigonometry::Trigonometry()
{
}

Trigonometry::~Trigonometry()
{
}

double Trigonometry::sinus(double x, u8 precision)
{
    double result{0.0};

    for (u16 n = 0; n < precision; n++)
    {
        result = result + (((n & 0x01) ? -1 : 1) * power(toRadians(x), static_cast<u16>((2 * n) + 1))) / factorial(static_cast<u16>((2 * n) + 1));    
    }
    return result;
}
