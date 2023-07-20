// Copyright 2023 Erik Williams

#ifndef DESKTOP_AUDIO_WAVE_GENERATION_WAVEFORMS_H_
#define DESKTOP_AUDIO_WAVE_GENERATION_WAVEFORMS_H_

#include <cmath>

namespace waveforms {
    const double kTwoPi = 2.0 * M_PI;
    // Generates a sine wave for the given phase x.
    double SineWave(double x);
    // Generates a square wave for the given phase x.
    double SquareWave(double x);
    // Generates a sawtooth wave for the given phase x.
    double SawtoothWave(double x);
    // Generates a triangle wave for the given phase x.
    double TriangleWave(double x);
}  // namespace waveforms

#endif  // DESKTOP_AUDIO_WAVE_GENERATION_WAVEFORMS_H_
