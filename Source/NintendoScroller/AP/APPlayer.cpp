// Fill out your copyright notice in the Description page of Project Settings.


#include "APPlayer.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"

AAPPlayer::AAPPlayer() 
{
    UPaperFlipbookComponent* SC = GetSprite();
    SC->SetRelativeLocation(FVector(20.000000, 0.000000, 20.000000));
    SC->SetRelativeScale3D(FVector(5.750000, 5.750000, 5.750000));
    SC->SetFlipbook(LoadObject<UPaperFlipbook>(this, TEXT(
		"Paper2D.PaperFlipbook '/Game/2DPlatformerCourseAssets/Warrior_Individual_Sprites/idle/Warrior_Idle.Warrior_Idle'"
	)));

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetRelativeRotation(FRotator(0.000000, -90.000000, 0.000000));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void AAPPlayer::BeginPlay() 
{
    // Make sure that we have a valid PlayerController.
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        // Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            // PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
            Subsystem->ClearAllMappings();

            // Add each mapping context, along with their priority values. Higher values outprioritize lower values.
            Subsystem->AddMappingContext(MyInputMappingContext, MyInt32Priority);
        }
    }
}

void AAPPlayer::PostInitializeComponents()
{
    Super::PostInitializeComponents();


}