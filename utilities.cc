// Copyright 2023 Erik Williams

// utilities.cc
#include <cmath>
#include <fstream>
#include "utilities.h"

bool ParseArguments(int argc, char *argv[], std::string* output_file_name,
                    std::string* waveform, int* duration,
                    std::vector<double>* frequencies) {
    if (argc < 5) {
        return false;
    }

    *output_file_name = argv[1];
    *waveform = argv[2];
    *duration = std::stoi(argv[3]);
    
    for (int i = 4; i < argc; ++i) {
        frequencies->push_back(std::stod(argv[i]));
    }
    return true;
}


double CalculateWaveformValue(const std::string& waveform, double x) {
    // Normalize x to [0, 2π]
    double phase = x - 2.0 * M_PI * std::floor(x / (2.0 * M_PI));

    if (waveform == "sine") {
        return std::sin(phase);
    } else if (waveform == "triangle") {
        if (phase < M_PI) {
            return 2.0 * phase / M_PI - 1.0;
        } else {
            return 3.0 - 2.0 * phase / M_PI;
        }
    } else if (waveform == "sawtooth") {
        return (2.0 * phase / (2.0 * M_PI)) - 1.0;
    } else if (waveform == "square") {
        return phase < M_PI ? 1.0 : -1.0;
    }
    // Return 0 if waveform type is unrecognized.
    return 0.0;
}



bool WriteToOutputFile(const std::string& output_file_name,
                       const std::vector<int16_t>& buffer) {
    std::ofstream outfile(output_file_name, std::ios::binary);
    if (!outfile.is_open()) {
        return false;
    }
    outfile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size() * sizeof(int16_t));
    outfile.close();
    return true;
}

