#pragma once
#include <string>
#include <vector>

enum class VitalStatus { NORMAL, LOW, HIGH };

struct VitalCheck {
  std::string name;
  float value;
  float min;
  float max;
};

// Pure functions
VitalStatus evaluateVital(float value, float min, float max);
std::vector<std::string> checkVitals(const std::vector<VitalCheck>& vitals);

// I/O handling
void blinkWarningMessage(const std::string& message);
bool vitalsOk(float temperature, float pulseRate, float spo2);
