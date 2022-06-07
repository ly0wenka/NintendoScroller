// Fill out your copyright notice in the Description page of Project Settings.

#include "Battery.h"

#include "Microsoft/AllowMicrosoftPlatformTypes.h"

constexpr float ChargeAmount = 0.1f;

Battery::Battery(const float PercentIn) { SetPercent(PercentIn); }

void Battery::Charge() { SetPercent(Percent + ChargeAmount); }

void Battery::UnCharge() { SetPercent(Percent - ChargeAmount); }

float Battery::GetPercent() const { return Percent; }

FColor Battery::GetColor() const {
  if (Percent > .8f)
    return FColor::Green;
  return Percent > .3f ? FColor::Yellow : FColor::Red;
}

FString Battery::ToString() const {
  return FString::Printf(TEXT("%i%%"), FMath::RoundToInt(Percent * 100));
}

void Battery::SetPercent(const float PercentIn) {
  this->Percent = FMath::Clamp(PercentIn, 0.0f, 1.0f);
}
