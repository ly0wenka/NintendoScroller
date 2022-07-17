// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryTests.h"

#include "Misc/AutomationTest.h"
#include "TPS/Battery.h"

using namespace TPS;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBatteryBatterDefaultTest,
                                 "TPSGame.Items.Battery.BatteryDefault",
                                 EAutomationTestFlags::ApplicationContextMask |
                                     EAutomationTestFlags::ProductFilter |
                                     EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBatteryTests, "TPSGame.Items.Battery.Tests",
                                 EAutomationTestFlags::ApplicationContextMask |
                                     EAutomationTestFlags::ProductFilter |
                                     EAutomationTestFlags::HighPriority)

bool FBatteryBatterDefaultTest::RunTest(const FString &Parameters) {
  AddInfo("Battery with default ctor");

  const FBattery BatterDefault;
  TestTrueExpr(FMath::IsNearlyEqual(BatterDefault.GetPercent(), 1.0f));
  TestTrueExpr(BatterDefault.GetColor() == FColor::Green);
  TestTrueExpr(BatterDefault.ToString().Equals("100%"));

  return true;
}

bool FBatteryTests::RunTest(const FString &Parameters) {
  const FBattery BatterDefault;
  TestTrueExpr(FMath::IsNearlyEqual(BatterDefault.GetPercent(), 1.0f));
  TestTrueExpr(BatterDefault.GetColor() == FColor::Green);
  TestTrueExpr(BatterDefault.ToString().Equals("100%"));

  const auto BatteryTestFunc = [this](float Percent, const FColor &Color,
                                      const FString &PercentString) {
    const FBattery BatteryObject{Percent};
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(),
                                      FMath::Clamp(Percent, 0.0f, 1.0f)));
    TestTrueExpr(BatteryObject.GetColor() == Color);
    TestTrueExpr(BatteryObject.ToString().Equals(PercentString));
  };

  AddInfo("custom ctor");
  BatteryTestFunc(1.0f, FColor::Green, "100%");
  BatteryTestFunc(0.46f, FColor::Yellow, "46%");
  BatteryTestFunc(0.2f, FColor::Red, "20%");
  BatteryTestFunc(3333.0f, FColor::Green, "100%");
  BatteryTestFunc(-3333.0f, FColor::Red, "0%");

  AddInfo("Battery charge / discharge");
  FBattery BatteryObject;
  for (int i = 0; i < 100; ++i) {
    BatteryObject.UnCharge();
  }
  BatteryTestFunc(.0f, FColor::Red, "0%");
  for (int i = 0; i < 100; ++i) {
    BatteryObject.Charge();
  }
  BatteryTestFunc(1.0f, FColor::Green, "100%");

  AddInfo("Battery comparison");
  const FBattery BatteryLow{.3f};
  const FBattery BatteryHigh{.9f};

  TestTrueExpr(BatteryHigh >= BatteryLow);
  TestTrueExpr(FMath::Max(BatteryHigh, BatteryLow) == BatteryHigh);

  AddInfo("Battery in memory comparison");
  TestNotSame("Not the same battery", BatteryLow, BatteryHigh);
  const FBattery BatteryHighDuplicate{.9f};
  TestNotSame("Not the same battery", BatteryHighDuplicate, BatteryHigh);
  const FBattery &BatteryHighRef = BatteryHigh;
  TestNotSame("Not the same battery", BatteryHighRef, BatteryHigh);

  return true;
}