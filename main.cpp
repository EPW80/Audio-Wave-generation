#include <sndfile.h>

// #include <cmath>
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
    std::cerr << "Usage: " << argv[0] << " <frequency> <duration> <waveform>\n";
    return 1;
  }

  double frequency = std::atof(argv[1]);
  int duration = std::atoi(argv[2]);
  std::string waveform = argv[3];

  // Create a buffer to hold the samples
  std::vector<short> buffer(SAMPLE_RATE * duration);

  // Generate audio
  for (int i = 0; i < SAMPLE_RATE * duration; i++)
  {
    double value;
    double x = (double)i / SAMPLE_RATE * frequency; // phase

    // Select waveform
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

    // Convert to a short with appropriate scaling
    buffer[i] = value * MAX_AMPLITUDE * 32767.0;
  }

  // Write to .wav file
  SF_INFO sfinfo;
  sfinfo.samplerate = SAMPLE_RATE;
  sfinfo.channels = 1;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  // Open the sound file for writing
  SNDFILE *outfile = sf_open("audio.wav", SFM_WRITE, &sfinfo);

  // Write the generated samples to the file
  sf_write_short(outfile, &buffer[0], SAMPLE_RATE * duration);

  // Close the file
  sf_close(outfile);

  std::cout << "Wrote " << duration << " second(s) of a " << frequency
            << "Hz " << waveform << " wave to 'audio.wav'" << std::endl;

  return 0;
}
