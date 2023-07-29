// Copyright 2023 Erik Williams

#include <sndfile.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "waveForms.h"

namespace soundwave {

const int kSampleRate = 44100;
const double kMaxAmplitude = 0.9;

}  // namespace soundwave

// Function prototypes
bool ParseArguments(int argc, char *argv[], std::string* output_file_name,
                    std::string* waveform, int* duration,
                    std::vector<double>* frequencies);
double CalculateWaveformValue(const std::string& waveform, double x);
bool WriteToOutputFile(const std::string& output_file_name,
                       const std::vector<int16_t>& buffer);

int main(int argc, char *argv[]) {
  std::string output_file_name;
  std::string waveform;
  int duration;
  std::vector<double> frequencies;
  if (!ParseArguments(argc, argv,
                      &output_file_name,
                      &waveform,
                      &duration,
                      &frequencies)) {
    return 1;
  }

  std::vector<int16_t> buffer(soundwave::kSampleRate * duration);

  for (double frequency : frequencies) {
    for (int i = 0; i < soundwave::kSampleRate * duration; ++i) {
      double x = static_cast<double>(i) / soundwave::kSampleRate * frequency;
      double value = CalculateWaveformValue(waveform, x);
      buffer[i] += value * soundwave::kMaxAmplitude * 32767.0
                  / frequencies.size();
    }
  }

  if (!WriteToOutputFile(output_file_name, buffer)) {
    return 1;
  }

  std::cout << "Wrote " << duration << " second(s) of a " << frequencies[0]
            << "Hz " << waveform << " wave to '" << output_file_name << "'\n";

  return 0;
}

bool ParseArguments(int argc, char *argv[], std::string* output_file_name,
                    std::string* waveform, int* duration,
                    std::vector<double>* frequencies) {
  if (argc < 5) {
    std::cerr << "Usage: " << argv[0]
              << " <output_file_name> <waveform> <duration> <frequency1> "
              << "<frequency2> ... <frequencyN>\n";
    return false;
  }

  *output_file_name = argv[1];
  *waveform = argv[2];
  *duration = std::atoi(argv[3]);
  for (int arg = 4; arg < argc; ++arg) {
    frequencies->push_back(std::atof(argv[arg]));
  }

  return true;
}

double CalculateWaveformValue(const std::string& waveform, double x) {
  if (waveform == "sine") {
    return waveforms::SineWave(x);
  } else if (waveform == "square") {
    return waveforms::SquareWave(x);
  } else if (waveform == "triangle") {
    return waveforms::TriangleWave(x);
  } else if (waveform == "sawtooth") {
    return waveforms::SawtoothWave(x);
  } else {
    std::cerr << "Invalid waveform: " << waveform << "\n";
    exit(1);  // or throw an exception
  }
}

bool WriteToOutputFile(const std::string& output_file_name,
                       const std::vector<int16_t>& buffer) {
  SF_INFO sfinfo;
  sfinfo.samplerate = soundwave::kSampleRate;
  sfinfo.channels = 1;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  SNDFILE* outfile = sf_open(output_file_name.c_str(), SFM_WRITE, &sfinfo);
  if (!outfile) {
    std::cerr << "Error: Could not open output file '" << output_file_name
              << "' for writing.\n";
    return false;
  }

  sf_write_short(outfile, &buffer[0],
                soundwave::kSampleRate * buffer.size() / sizeof(int16_t));
  sf_close(outfile);

  return true;
}
