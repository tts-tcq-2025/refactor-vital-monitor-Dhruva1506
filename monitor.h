#ifndef MONITOR_H
#define MONITOR_H

enum class VitalStatus {
    OK,
    TemperatureOutOfRange,
    PulseOutOfRange,
    Spo2OutOfRange
};

// Pure function: check vitals, return status
VitalStatus checkVitals(float temperature, float pulseRate, float spo2);

// Alert function: handle alerts with blinking and messages
void alertIfNeeded(VitalStatus status);

#endif // MONITOR_H
