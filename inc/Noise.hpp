#pragma once

#include "Maths.hpp"

namespace maths::random::noise
{

enum class NoiseType : int
{
    GAUSSIAN,
    WHITE,
    PINK,
    BROWN
};

class Noise
{
public:
    Noise();
    ~Noise();

    virtual void noiseGenerator() = 0;
private:
    /* data */
};
    
} // namespace maths::random::noise
