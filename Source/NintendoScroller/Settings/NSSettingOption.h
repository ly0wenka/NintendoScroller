// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NSSettingOption.generated.h"

USTRUCT()
struct FNSSettingOption
{
    GENERATED_BODY()

    FText Name;

    int32 Value;
};
