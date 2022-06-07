// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ostream>

#include "CoreMinimal.h"

// namespace TPS
// {
/**
 *
 */
class NINTENDOSCROLLER_API Battery final {
public:
  Battery() = default;
  Battery(float PercentIn);
  ~Battery() = default;

  void Charge();
  void UnCharge();

  float GetPercent() const;
  FColor GetColor() const;
  FString ToString() const;

  friend bool operator==(const Battery &Lhs, const Battery &RHS) {
    return FMath::IsNearlyEqual(Lhs.Percent, RHS.Percent);
  }

  friend bool operator!=(const Battery &Lhs, const Battery &RHS) {
    return !(Lhs == RHS);
  }

  friend bool operator<(const Battery &Lhs, const Battery &RHS) {
    return Lhs.Percent < RHS.Percent;
  }

  friend bool operator<=(const Battery &Lhs, const Battery &RHS) {
    return !(RHS < Lhs);
  }

  friend bool operator>(const Battery &Lhs, const Battery &RHS) {
    return RHS < Lhs;
  }

  friend bool operator>=(const Battery &Lhs, const Battery &RHS) {
    return !(Lhs < RHS);
  }

private:
  float Percent{1.0f};
  void SetPercent(float PercentIn);
};
// }
