#pragma once

namespace signal
{
class Periodic
{
public:
    Periodic(/* args */);
    ~Periodic() = default;
private:
    double frequency;
    double amplitude;
    double phase;
};   
} // namespace signal
