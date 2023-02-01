#pragma once

#include "Maths.hpp"

namespace maths::trig
{

class Trigonometry : public Maths
{
public:
    Trigonometry();
    ~Trigonometry();

    double sinus(double x, u8 precision = 10);

private:
    /* data */
};   
} // namespace maths::trig
