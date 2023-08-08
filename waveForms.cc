// Copyright 2023 Erik Williams

#include "waveForms.h"

namespace waveforms
{
    double SineWave(double x)
    {
        return sin(x * kTwoPi);
    }
    double SquareWave(double x)
    {
        return x - floor(x) < 0.5 ? -1 : 1;
    }
    double SawtoothWave(double x)
    {
        return 2.0 * (x - floor(x)) - 1.0;
    }
    double TriangleWave(double x)
    {
        return 2 * abs(2 * (x - floor(x + 0.5))) - 1;
    }
} // namespace waveforms
