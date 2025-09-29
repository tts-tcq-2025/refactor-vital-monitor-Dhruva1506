#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

bool isTemperatureCritical(float temperature) {
  return temperature > 102 || temperature < 95;
}

bool isPulseRateOutOfRange(float pulseRate) {
  return pulseRate < 60 || pulseRate > 100;
}

bool isSpo2Low(float spo2) {
  return spo2 < 90;
}

VitalStatus evaluateVital(float value, float min, float max) {
  if (value < min) return VitalStatus::LOW;
  if (value > max) return VitalStatus::HIGH;
  return VitalStatus::NORMAL;
}

std::vector<std::string> checkVitals(const std::vector<VitalCheck>& vitals) {
  std::vector<std::string> warnings;
  for (const auto& vital : vitals) {
    VitalStatus status = evaluateVital(vital.value, vital.min, vital.max);
    if (status == VitalStatus::LOW || status == VitalStatus::HIGH) {
      warnings.push_back(vital.name + " out of range!");
    }
  }
  return warnings;
}

void blinkWarningMessage(const char* message) {
  cout << message << '\n';
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
  cout << "\r  \r" << flush;  // Clear the line
}

bool vitalsOk(float temperature, float pulseRate, float spo2) {
  std::vector<VitalCheck> vitals = {
      {"Temperature", temperature, 95, 102},
      {"Pulse Rate", pulseRate, 60, 100},
      {"SpO2", spo2, 90, 100}};

  auto warnings = checkVitals(vitals);
  if (!warnings.empty()) {
    blinkWarningMessage(warnings.front().c_str());  // Show only first issue
    return false;
  }
  return true;
}
