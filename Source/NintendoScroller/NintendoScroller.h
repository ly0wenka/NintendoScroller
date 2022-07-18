// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    WT_None UMETA(DisplayName="None"),
    WT_Sword UMETA(DisplayName="Sword"),
    WT_Dualblade UMETA(DisplayName="Dualblade"),
    WT_Axe_Or_Blunt UMETA(DisplayName="Axe_Or_Blunt"),
    WT_Shield UMETA(DisplayName="Shield"),
};