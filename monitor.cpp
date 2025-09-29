#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;


VitalStatus evaluateVital(float value, float min, float max) {
  if (value < min) return VitalStatus::LOW;
  if (value > max) return VitalStatus::HIGH;
  return VitalStatus::NORMAL;
}


std::vector<std::string> checkVitals(const std::vector<VitalCheck>& vitals) {
  std::vector<std::string> warnings;
  for (const auto& vital : vitals) {
    VitalStatus status = evaluateVital(vital.value, vital.min, vital.max);
    if (status != VitalStatus::NORMAL) {
      warnings.push_back(vital.name + " out of range!");
    }
  }
  return warnings;
}


bool isTemperatureCritical(float temperature) {
  return temperature < 95.0f || temperature > 102.0f;
}

bool isPulseRateOutOfRange(float pulseRate) {
  return pulseRate < 60.0f || pulseRate > 100.0f;
}

bool isSpo2Low(float spo2) {
  return spo2 < 90.0f;
}


static void printBlinkFrame(int frame) {
  cout << (frame % 2 == 0 ? "\r* " : "\r *") << flush;
}


void blinkWarningMessage(const std::string& message) {
  cout << message << '\n';
#ifdef ENABLE_BLINKING
  for (int i = 0; i < 6; ++i) {
    printBlinkFrame(i);
    sleep_for(seconds(1));
  }
  cout << "\r  \r" << flush;  // Clear the line
#else
  cout << "[BLINKING DISABLED in test mode]\n";
#endif
}


bool vitalsOk(float temperature, float pulseRate, float spo2) {
  std::vector<VitalCheck> vitals = {
    {"Temperature", temperature, 95.0f, 102.0f},
    {"Pulse Rate", pulseRate, 60.0f, 100.0f},
    {"SpO2", spo2, 90.0f, 100.0f}
  };

  auto warnings = checkVitals(vitals);
  if (!warnings.empty()) {
    blinkWarningMessage(warnings.front());
    return false;
  }
  return true;
}
