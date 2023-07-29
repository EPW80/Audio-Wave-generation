# Sound Wave Generator

Generate WAV audio files with custom frequencies and waveforms using this straightforward C++ command-line utility.

## Technolgy used

- C++

- cpplint

- libsndfile library

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
./main output.wav triangle 3 300
```

This command will create an "output.wav" file, containing a triangle waveform of 3 seconds duration with frequencies of 300Hz, 600Hz, and 900Hz.

To clean up the compiled files, you can use:

```
make clean
```

You can also test the program with default parameters

```
make test
```

## Time Complexity Notation

O(1): Represents constant time complexity. Regardless of input size, the algorithm approximately takes a consistent amount of time.

## Code Overview

This utility constructs a buffer filled with audio samples for multiple waveforms at various frequencies. It then uses this buffer to create a WAV file. Some critical constants include:

SAMPLE_RATE: The number of audio samples taken per second.
TWO_PI: Represents 2×Pi for a full circle in radians.
MAX_AMPLITUDE: The highest amplitude the audio wave can achieve.
The main function calculates the increment needed for each audio sample to generate the desired frequency. It then fills a buffer with the audio samples corresponding to each frequency. These samples are derived from the waveform function's evaluation at the current wave position. This is followed by scaling and translating the waveform's [-1,1] range to a 16-bit signed integer domain. Once the audio data generation is complete, the program sets up the libsndfile info structure (sfinfo), opens the designated output file, writes the audio data, and finally, closes the file.

## Contributor

Erik Williams
