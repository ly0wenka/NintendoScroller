// Fill out your copyright notice in the Description page of Project Settings.


#include "APPlayer.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

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

void AAPPlayer::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}