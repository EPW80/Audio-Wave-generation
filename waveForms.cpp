#include "waveForms.h"

double sine_wave(double x)
{
    return sin(x * TWO_PI);
}

double square_wave(double x)
{
    return x - floor(x) < 0.5 ? -1 : 1;
}

double sawtooth_wave(double x)
{
    return 2.0 * (x - floor(x)) - 1.0;
}

double triangle_wave(double x)
{
    return 2 * abs(2 * (x - floor(x + 0.5))) - 1;
}
