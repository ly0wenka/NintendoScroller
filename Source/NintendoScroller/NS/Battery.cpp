// Fill out your copyright notice in the Description page of Project Settings.

#include "Battery.h"

#include "Microsoft/AllowMicrosoftPlatformTypes.h"

using namespace NS;

constexpr float ChargeAmount = 0.1f;

FBattery::FBattery(const float PercentIn) { SetPercent(PercentIn); }

void FBattery::Charge() { SetPercent(Percent + ChargeAmount); }

void FBattery::UnCharge() { SetPercent(Percent - ChargeAmount); }

float FBattery::GetPercent() const { return Percent; }

FColor FBattery::GetColor() const {
  if (Percent > .8f)
    return FColor::Green;
  return Percent > .3f ? FColor::Yellow : FColor::Red;
}

FString FBattery::ToString() const {
  return FString::Printf(TEXT("%i%%"), FMath::RoundToInt(Percent * 100));
}

void FBattery::SetPercent(const float PercentIn) {
  this->Percent = FMath::Clamp(PercentIn, 0.0f, 1.0f);
}
