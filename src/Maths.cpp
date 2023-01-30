#include "Maths.hpp"

using namespace signal::maths;

Maths::Maths()
{
}

Maths::~Maths()
{
}

u64 Maths::factorial(u8 number)
{
    return (number <= 1) ? 1 : number * factorial(number - 1);
}

double Maths::power(double number, u8 exp)
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
    
    for (uint8_t i = 1; i < exp; i++)
    {
        power = power * number;
    }
    
    return power;    
}

double Maths::sinus(double x, u8 precision)
{
    double result{0.0};

    for (u8 n = 0; n < precision; n++)
    {
        result = result + (power(-1, n) * (power(x, 2*n + 1) / static_cast<double>(factorial(2 * n + 1))));
    }
    return result;
}