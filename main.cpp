#include <sndfile.h>
#include <cstdlib> // for atof
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "waveForms.h"

const int SAMPLE_RATE = 44100;
const double MAX_AMPLITUDE = 0.9;

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    std::cerr << "Usage: " << argv[0] << " <waveform> <duration> <frequency1> <frequency2> ... <frequencyN>\n";
    return 1;
  }

  std::string waveform = argv[1];
  int duration = std::atoi(argv[2]);

  std::vector<short> buffer(SAMPLE_RATE * duration);

  for (int arg = 3; arg < argc; ++arg)
  {
    double frequency = std::atof(argv[arg]);

    for (int i = 0; i < SAMPLE_RATE * duration; i++)
    {
      double value;
      double x = (double)i / SAMPLE_RATE * frequency;

      if (waveform == "sine")
        value = sine_wave(x);
      else if (waveform == "square")
        value = square_wave(x);
      else if (waveform == "triangle")
        value = triangle_wave(x);
      else if (waveform == "sawtooth")
        value = sawtooth_wave(x);
      else
      {
        std::cerr << "Invalid waveform: " << waveform << "\n";
        return 1;
      }

      buffer[i] += value * MAX_AMPLITUDE * 32767.0 / (argc - 3);
    }
  }

  SF_INFO sfinfo;
  sfinfo.samplerate = SAMPLE_RATE;
  sfinfo.channels = 1;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  SNDFILE *outfile = sf_open("audio.wav", SFM_WRITE, &sfinfo);

  if (!outfile)
  {
    std::cerr << "Error opening file: " << sf_strerror(NULL) << std::endl;
    return -1;
  }

  sf_count_t count = sf_write_short(outfile, &buffer[0], SAMPLE_RATE * duration);
  if (count != SAMPLE_RATE * duration)
  {
    std::cerr << "Error writing to file: " << sf_strerror(outfile) << std::endl;
    sf_close(outfile);
    return -1;
  }

  sf_close(outfile);

  std::cout << "Wrote " << duration << " second(s) of a " << argv[3]
            << "Hz " << waveform << " wave to 'audio.wav'" << std::endl;

  return 0;
}
