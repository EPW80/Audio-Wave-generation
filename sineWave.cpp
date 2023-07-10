#include <sndfile.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

const int SAMPLE_RATE = 44100;
const double TWO_PI = M_PI * 2;
const double FREQUENCY = 440.0;
const double MAX_AMPLITUDE = 0.9;

int main() {
  // Prepare to generate sine wave
  const double increment = FREQUENCY * TWO_PI / SAMPLE_RATE;
  double x = 0;

  // Create a buffer to hold the samples
  std::vector<short> buffer(SAMPLE_RATE);

  // Generate one second of audio
  for (int i = 0; i < SAMPLE_RATE; i++) {
    double value = sin(x);
    x += increment;

    // Convert to a short with appropriate scaling
    buffer[i] = value * MAX_AMPLITUDE * 32767.0;
  }

  // Write to .wav file
  SF_INFO sfinfo;
  sfinfo.samplerate = SAMPLE_RATE;
  sfinfo.channels = 1;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  // Open the sound file for writing
  SNDFILE *outfile = sf_open("sine.wav", SFM_WRITE, &sfinfo);

  // Write the generated samples to the file
  sf_write_short(outfile, &buffer[0], SAMPLE_RATE);

  // Close the file
  sf_close(outfile);

  std::cout << "Wrote one second of a " << FREQUENCY
            << "Hz sine wave to 'sine.wav'" << std::endl;

  return 0;
}
