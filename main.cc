// Copyright 2023 Erik Williams

#include <sndfile.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utilities.h"
#include "waveForms.h"

namespace soundwave {
    const int kSampleRate = 44100;
    const double kMaxAmplitude = 0.9;
}  // namespace soundwave

int main(int argc, char *argv[]) {
    std::string output_file_name;
    std::string waveform;
    int duration;
    std::vector<double> frequencies;

    if (!ParseArguments(argc, argv, &output_file_name, &waveform, &duration, &frequencies)) {
        return 1;
    }

    std::vector<double> tempBuffer(soundwave::kSampleRate * duration, 0.0);

    for (double frequency : frequencies) {
        for (int i = 0; i < soundwave::kSampleRate * duration; ++i) {
            double t = static_cast<double>(i) / soundwave::kSampleRate;  // Current time in seconds
            double envelope = 1.0;  // Default envelope value

            if (t < 0.1 * duration) {  // Fade-in
                envelope = t / (0.1 * duration);
            } else if (t > 0.9 * duration) {
                envelope = (1.0 - t) / 0.1;
            }

            double x = t * frequency;
            double value = CalculateWaveformValue(waveform, x);
            tempBuffer[i] += envelope * value * soundwave::kMaxAmplitude;
        }
    }

    for (int i = 0; i < soundwave::kSampleRate * duration; ++i) {
        tempBuffer[i] /= frequencies.size();
    }

    std::vector<int16_t> buffer(soundwave::kSampleRate * duration);
    for (int i = 0; i < soundwave::kSampleRate * duration; ++i) {
        double val = tempBuffer[i] * 32767.0;
        buffer[i] = static_cast<int16_t>(std::max(-32768.0, std::min(32767.0, val)));
    }

    if (!WriteToOutputFile(output_file_name, buffer)) {
    std::cerr << "Error: Failed to write to output file.\n";
    return 1;
}


    // Log message for multiple frequencies
    std::cout << "Wrote " << duration << " second(s) of ";
    for (size_t i = 0; i < frequencies.size(); i++) {
        std::cout << frequencies[i] << "Hz";
        if (i != frequencies.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " " << waveform << " wave to '" << output_file_name << "'\n";

    return 0;
}
