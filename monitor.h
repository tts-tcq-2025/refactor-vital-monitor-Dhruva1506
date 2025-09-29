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


VitalStatus evaluateVital(float value, float min, float max);
std::vector<std::string> checkVitals(const std::vector<VitalCheck>& vitals);


bool isTemperatureCritical(float temperature);
bool isPulseRateOutOfRange(float pulseRate);
bool isSpo2Low(float spo2);


void blinkWarningMessage(const std::string& message);
bool vitalsOk(float temperature, float pulseRate, float spo2);
