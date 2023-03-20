#pragma once

#include <stdint.h>
#include <stdexcept>
#include <functional>

namespace maths
{
constexpr double PI = 3.14159265358979323846;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class MathsException : public std::runtime_error
{
public:
    MathsException(const std::string &msg) : std::runtime_error(msg) {}
};

class Maths
{
public:
    Maths(/* args */);
    ~Maths();

    //void taylorSeries();
    double factorial(u16 number);
    double power(double number, u16 exp);

    template<typename F>
    double sinus(F func, u8 precision)
    {
        double result{0.0};

        for (u16 n = 0; n < precision; n++)
        {
            result = result + (((n & 0x01) ? -1 : 1) * power(func(), static_cast<u16>((2 * n) + 1))) / factorial(static_cast<u16>((2 * n) + 1));    
        }
        return result;
    }

    double toRadians(double x);
    double toDegrees(double radians);

private:
    /* data */
};
} // namespace signal::maths