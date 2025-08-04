#include <gtest/gtest.h>
#include "monitor.h"

TEST(Monitor, TemperatureOutOfRange) {
    EXPECT_EQ(checkVitals(94.9f, 70, 95), VitalStatus::TemperatureOutOfRange);
    EXPECT_EQ(checkVitals(102.1f, 70, 95), VitalStatus::TemperatureOutOfRange);
}

TEST(Monitor, PulseOutOfRange) {
    EXPECT_EQ(checkVitals(98.6f, 59, 95), VitalStatus::PulseOutOfRange);
    EXPECT_EQ(checkVitals(98.6f, 101, 95), VitalStatus::PulseOutOfRange);
}

TEST(Monitor, Spo2OutOfRange) {
    EXPECT_EQ(checkVitals(98.6f, 70, 89), VitalStatus::Spo2OutOfRange);
}

TEST(Monitor, AllVitalsOk) {
    EXPECT_EQ(checkVitals(98.6f, 70, 95), VitalStatus::OK);
}

TEST(Monitor, MultipleIssues) {
    EXPECT_EQ(checkVitals(94.0f, 59, 85), VitalStatus::TemperatureOutOfRange);
    EXPECT_EQ(checkVitals(98.0f, 59, 85), VitalStatus::PulseOutOfRange);
}
