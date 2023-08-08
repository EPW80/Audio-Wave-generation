// Copyright 2023 Erik Williams

#ifndef WAVEFORMS_H_
#define WAVEFORMS_H_

#include <cmath>

namespace waveforms
{
    const double kTwoPi = 2.0 * M_PI;
    // Generates a sine wave for the given phase x.
    double SineWave(double x);
    // Generates a square wave for the given phase x.
    double SquareWave(double x);
    // Generates a sawtooth wave for the given phase x.
    double SawtoothWave(double x);
    // Generates a triangle wave for the given phase x.
    double TriangleWave(double x);
} // namespace waveforms

#endif // WAVEFORMS_H_
