#pragma once

#include <stdint.h>
#include <stdexcept>

namespace signal::maths
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
    double sinus(double x, u8 precision = 10);
    double toRadians(double x);
    double toDegrees(double radians);

private:
    /* data */
};
} // namespace signal::maths