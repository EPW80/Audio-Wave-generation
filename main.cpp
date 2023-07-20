#include <sndfile.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "waveForms.h"

const int kSampleRate = 44100;
const double kMaxAmplitude = 0.9;

int main(int argc, char *argv[])
{
  if (argc < 5)
  {
    std::cerr << "Usage: " << argv[0]
              << " <output_file_name> <waveform> <duration> <frequency1> <frequency2> ... <frequencyN>\n";
    return 1;
  }

  std::string output_file_name = argv[1];
  std::string waveform = argv[2];
  int duration = std::atoi(argv[3]);

  std::vector<short> buffer(kSampleRate * duration);

  for (int arg = 4; arg < argc; ++arg)
  {
    double frequency = std::atof(argv[arg]);

    for (int i = 0; i < kSampleRate * duration; ++i)
    {
      double value;
      double x = static_cast<double>(i) / kSampleRate * frequency;

      if (waveform == "sine")
      {
        value = sine_wave(x);
      }
      else if (waveform == "square")
      {
        value = square_wave(x);
      }
      else if (waveform == "triangle")
      {
        value = triangle_wave(x);
      }
      else if (waveform == "sawtooth")
      {
        value = sawtooth_wave(x);
      }
      else
      {
        std::cerr << "Invalid waveform: " << waveform << "\n";
        return 1;
      }

      buffer[i] += value * kMaxAmplitude * 32767.0 / (argc - 3);
    }
  }

  SF_INFO sfinfo;
  sfinfo.samplerate = kSampleRate;
  sfinfo.channels = 1;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  SNDFILE *outfile = sf_open(output_file_name.c_str(), SFM_WRITE, &sfinfo);
  if (!outfile)
  {
    std::cerr << "Error: Could not open output file '" << output_file_name << "' for writing.\n";
    return 1;
  }

  sf_write_short(outfile, &buffer[0], kSampleRate * duration);
  sf_close(outfile);

  std::cout << "Wrote " << duration << " second(s) of a " << argv[4]
            << "Hz " << waveform << " wave to '" << output_file_name << "'\n";

  return 0;
}
