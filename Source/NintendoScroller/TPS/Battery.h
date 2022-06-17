// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ostream>

#include "CoreMinimal.h"

namespace TPS
{
/**
 *
 */
class NINTENDOSCROLLER_API FBattery final {
public:
  FBattery() = default;
  explicit FBattery(float PercentIn);
  ~FBattery() = default;

  void Charge();
  void UnCharge();

  auto GetPercent() const -> float;
  auto GetColor() const -> FColor;
  auto ToString() const -> FString;

  friend bool operator==(const FBattery &Lhs, const FBattery &RHS) {
    return FMath::IsNearlyEqual(Lhs.Percent, RHS.Percent);
  }

  friend bool operator!=(const FBattery &Lhs, const FBattery &RHS) {
    return !(Lhs == RHS);
  }

  friend bool operator<(const FBattery &Lhs, const FBattery &RHS) {
    return Lhs.Percent < RHS.Percent;
  }

  friend bool operator<=(const FBattery &Lhs, const FBattery &RHS) {
    return !(RHS < Lhs);
  }

  friend bool operator>(const FBattery &Lhs, const FBattery &RHS) {
    return RHS < Lhs;
  }

  friend bool operator>=(const FBattery &Lhs, const FBattery &RHS) {
    return !(Lhs < RHS);
  }

private:
  float Percent{1.0f};
  void SetPercent(float PercentIn);
};
}
