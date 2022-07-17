// Copyright Epic Games, Inc. All Rights Reserved.

#include "NSCharacter.h"

#if MY_VR_MACRO
#include "HeadMountedDisplayFunctionLibrary.h"
#endif

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/NSInventoryComponent.h"
#include "TimerManager.h"

//////////////////////////////////////////////////////////////////////////
// ANSCharacter

UAbilitySystemComponent* ANSCharacter::GetAbilitySystemComponent() const
{
    return nullptr;
}

ANSCharacter::ANSCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;             // Character moves in the direction of input...
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);  // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;        // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = true;  // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);  // Attach the camera to the end of the boom and let the
                                                                                 // boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false;                               // Camera does not rotate relative to arm

    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

    InventoryComponent = CreateDefaultSubobject<UNSInventoryComponent>("InventoryComponent");
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Set up gameplay key bindings
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAxis("MoveForward", this, &ANSCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ANSCharacter::MoveRight);

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &ANSCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &ANSCharacter::LookUpAtRate);

    // handle touch devices
    PlayerInputComponent->BindTouch(IE_Pressed, this, &ANSCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &ANSCharacter::TouchStopped);

    // VR headset functionality
    PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ANSCharacter::OnResetVR);
}

void ANSCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
    Jump();
}

void ANSCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
    StopJumping();
}

void ANSCharacter::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ANSCharacter::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ANSCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ANSCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

void ANSCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthData.MaxHealth > 0.0f);
    Health = HealthData.MaxHealth;

    OnTakeAnyDamage.AddDynamic(this, &ANSCharacter::OnAnyDamageReceived);
}

float ANSCharacter::GetHealthPercent() const
{
    return Health / HealthData.MaxHealth;
}

void ANSCharacter::OnAnyDamageReceived(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    const auto IsAlive = [&]() { return Health > 0.0f; };

    if (Damage <= 0.0f || !IsAlive()) return;

    Health = FMath::Clamp(Health - Damage, 0.0f, HealthData.MaxHealth);

    if (IsAlive())
    {
        GetWorldTimerManager().SetTimer(HealTimerHandle, this, &ANSCharacter::OnHealing, HealthData.HealRate, true, -1.0f);
    }
    else
    {
        OnDeath();
    }
}

void ANSCharacter::OnHealing()
{
    Health = FMath::Clamp(Health + HealthData.HealModifier, 0.0f, HealthData.MaxHealth);
    if (FMath::IsNearlyEqual(Health, HealthData.MaxHealth))
    {
        Health = HealthData.MaxHealth;
        GetWorldTimerManager().ClearTimer(HealTimerHandle);
    }
}

void ANSCharacter::OnDeath()
{
    GetWorldTimerManager().ClearTimer(HealTimerHandle);

    check(GetCharacterMovement());
    check(GetCapsuleComponent());
    check(GetMesh());

    GetCharacterMovement()->DisableMovement();
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }

    SetLifeSpan(HealthData.LifeSpan);
}