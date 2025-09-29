#include <gtest/gtest.h>
#include "monitor.h"
#include <vector>
#include <string>

TEST(MonitorValidation, TemperatureChecks) {
  EXPECT_TRUE(isTemperatureCritical(103));
  EXPECT_TRUE(isTemperatureCritical(94));
  EXPECT_FALSE(isTemperatureCritical(98.6f));
  EXPECT_FALSE(isTemperatureCritical(95));
  EXPECT_FALSE(isTemperatureCritical(102));
}

TEST(MonitorValidation, PulseRateChecks) {
  EXPECT_TRUE(isPulseRateOutOfRange(59));
  EXPECT_TRUE(isPulseRateOutOfRange(101));
  EXPECT_FALSE(isPulseRateOutOfRange(75));
  EXPECT_FALSE(isPulseRateOutOfRange(60));
  EXPECT_FALSE(isPulseRateOutOfRange(100));
}

TEST(MonitorValidation, Spo2Checks) {
  EXPECT_TRUE(isSpo2Low(89));
  EXPECT_FALSE(isSpo2Low(95));
  EXPECT_FALSE(isSpo2Low(90));
}

TEST(MonitorVitalsOk, ReturnsFalseIfAnyVitalIsOffRange) {
  EXPECT_FALSE(vitalsOk(103, 80, 98));   
  EXPECT_FALSE(vitalsOk(98, 50, 98));    
  EXPECT_FALSE(vitalsOk(98, 80, 85));    
}

TEST(MonitorVitalsOk, ReturnsTrueIfAllVitalsNormal) {
  EXPECT_TRUE(vitalsOk(98.6f, 70, 97));
}
