#include "monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

constexpr float TEMP_LOW = 95.0f;
constexpr float TEMP_HIGH = 102.0f;
constexpr float PULSE_LOW = 60.0f;
constexpr float PULSE_HIGH = 100.0f;
constexpr float SPO2_LOW = 90.0f;

VitalStatus checkVitals(float temperature, float pulseRate, float spo2) {
    if (temperature < TEMP_LOW || temperature > TEMP_HIGH) {
        return VitalStatus::TemperatureOutOfRange;
    }
    if (pulseRate < PULSE_LOW || pulseRate > PULSE_HIGH) {
        return VitalStatus::PulseOutOfRange;
    }
    if (spo2 < SPO2_LOW) {
        return VitalStatus::Spo2OutOfRange;
    }
    return VitalStatus::OK;
}

static void blinkAlertMessage(const char* msg) {
    cout << msg << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
    cout << "\r  \n"; // Clear blinking
}

void alertIfNeeded(VitalStatus status) {
    switch (status) {
        case VitalStatus::TemperatureOutOfRange:
            blinkAlertMessage("Temperature is critical!");
            break;
        case VitalStatus::PulseOutOfRange:
            blinkAlertMessage("Pulse Rate is out of range!");
            break;
        case VitalStatus::Spo2OutOfRange:
            blinkAlertMessage("Oxygen Saturation out of range!");
            break;
        case VitalStatus::OK:
        default:
            // No alert
            break;
    }
}
