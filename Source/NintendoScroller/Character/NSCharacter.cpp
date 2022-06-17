// Fill out your copyright notice in the Description page of Project Settings.


#include "NSCharacter.h"

// Sets default values
ANSCharacter::ANSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

