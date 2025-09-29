#include <gtest/gtest.h>
#include "./monitor.h"

TEST(MonitorValidation, TemperatureChecks) {
  EXPECT_TRUE(isTemperatureCritical(103));
  EXPECT_TRUE(isTemperatureCritical(94));
  EXPECT_FALSE(isTemperatureCritical(98.6));

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

TEST(MonitorEvaluate, VitalStatusChecks) {
  EXPECT_EQ(evaluateVital(80, 60, 100), VitalStatus::NORMAL);
  EXPECT_EQ(evaluateVital(59, 60, 100), VitalStatus::LOW);
  EXPECT_EQ(evaluateVital(101, 60, 100), VitalStatus::HIGH);
}

TEST(MonitorCheckVitals, CollectsWarnings) {
  std::vector<VitalCheck> vitals = {
      {"Temp", 103, 95, 102},   
      {"Pulse", 50, 60, 100},   
      {"SpO2", 98, 90, 100}};   

  auto warnings = checkVitals(vitals);
  ASSERT_EQ(warnings.size(), 2);
  EXPECT_EQ(warnings[0], "Temp out of range!");
  EXPECT_EQ(warnings[1], "Pulse out of range!");
}

TEST(MonitorVitalsOk, ReturnsFalseIfAnyVitalIsOffRange) {
  EXPECT_FALSE(vitalsOk(103, 80, 98));   
  EXPECT_FALSE(vitalsOk(98, 50, 98));    
  EXPECT_FALSE(vitalsOk(98, 80, 85));   
}

TEST(MonitorVitalsOk, ReturnsTrueIfAllVitalsNormal) {
  EXPECT_TRUE(vitalsOk(98.6, 70, 97));
}
