// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "UObject/ObjectPtr.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "APPlayer.generated.h"

/**
 * 
 */
UCLASS()
class NINTENDOSCROLLER_API AAPPlayer : public APaperZDCharacter
{
	GENERATED_BODY()

public:
    AAPPlayer();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UCameraComponent> Camera;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<USpringArmComponent> SpringArm;

	UInputMappingContext* MyInputMappingContext;
    int32 MyInt32Priority;
};
