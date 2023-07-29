# Sound Wave Generator

Generate WAV audio files with custom frequencies and waveforms using this straightforward C++ command-line utility.
## Technolgy used

- C++

- cpplint

## Requirements

- C++ compiler (supports C++11)

- libsndfile library

## Installation

To install libsndfile, you can usually use a package manager. Here are some examples:

For Ubuntu/Debian:

```
sudo apt-get install libsndfile1-dev
```

For Fedora/RHEL/CentOS:

```
sudo dnf install libsndfile-devel
```

For macOS:

```
brew install libsndfile
```

## Compilation & Usage

To compile the program, navigate to the project directory and use the provided Makefile:

```
make
```

This will produce an executable named main.

Run the program with:

```
./main <output_file_name> <waveform> <duration> <frequency1> <frequency2> ... <frequencyN>
```

Example:

```
./main output.wav triangle 3 300 600 900
```

This command will create an "output.wav" file, containing a triangle waveform of 3 seconds duration with frequencies of 300Hz, 600Hz, and 900Hz.

To clean up the compiled files, you can use:

```
make clean
```

## Time Complexity Notation

O(1): Represents constant time complexity. Regardless of input size, the algorithm approximately takes a consistent amount of time.

## Code Overview

The utility generates a buffer of audio samples for multiple audio waves at diverse frequencies and subsequently writes this buffer to a WAV file. Constants include SAMPLE_RATE (samples per second of audio), TWO_PI (2×Pi for full circle representation in radians), and MAX_AMPLITUDE (maximum audio wave amplitude).

The main function determines the increment for each audio sample to produce the desired frequency. It then populates a buffer with audio samples for each frequency. Samples are produced by evaluating the waveform function's audio at the current wave position, then scaling and translating the [-1,1] function range to a 16-bit signed integer range. After audio data production, the program configures the libsndfile info structure (sfinfo), opens the output file, writes the audio data, and concludes by closing the file.

## Contributor

Erik Williams
