// Copyright 2023 Erik Williams

// utilities.h
#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <vector>
#include <string>
#include <cstdint>

bool ParseArguments(int argc, char *argv[], std::string *output_file_name,
                    std::string *waveform, int *duration,
                    std::vector<double> *frequencies);
double CalculateWaveformValue(const std::string &waveform, double x);
bool WriteToOutputFile(const std::string &output_file_name,
                       const std::vector<int16_t> &buffer);

#endif // UTILITIES_H_
