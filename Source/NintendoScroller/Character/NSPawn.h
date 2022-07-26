// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NSPawn.generated.h"

class UInputComponent;

UCLASS()
class NINTENDOSCROLLER_API ANSPawn : public APawn {
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ANSPawn();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;
};
