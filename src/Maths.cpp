#include "Maths.hpp"

using namespace signal::maths;

Maths::Maths()
{
}

Maths::~Maths()
{
}

double Maths::factorial(u16 number)
{
    return static_cast<double>((number <= 1) ? 1 : number * factorial(number - 1));
}

double Maths::power(double number, u16 exp)
{
    double power{number};

    if (exp == 0)
    {
        return 1;
    }
    if (number == 0)
    {
        return 0;
    }
    
    for (u8 i = 1; i < exp; i++)
    {
        power = power * number;
    }
    
    return power;    
}

double Maths::sinus(double x, u8 precision)
{
    double result{0.0};

    for (u16 n = 0; n < precision; n++)
    {
        result = result + (((n & 0x01) ? -1 : 1) * power(toRadians(x), static_cast<u16>((2 * n) + 1))) / factorial(static_cast<u16>((2 * n) + 1));    
    }
    return result;
}

double Maths::toRadians(double x)
{
    return (PI / 180.0) * x;    
}

double Maths::toDegrees(double radians)
{
    return radians * (180.0 / PI);
}