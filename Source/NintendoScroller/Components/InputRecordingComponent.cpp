// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputRecordingComponent.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Tests/Utils/JsonUtils.h"
#include "GameFramework/PlayerInput.h"

using namespace ::Test;

UInputRecordingComponent::UInputRecordingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UInputRecordingComponent::BeginPlay()
{
    Super::BeginPlay();

    check(GetOwner())
    check(GetWorld())
    check(GetOwner()->InputComponent)

    const auto* Pawn = Cast<APawn>(GetOwner());
    check(Pawn)

    const auto* PlayerController = Pawn->GetController<APlayerController>();
    check(PlayerController)

    PlayerInput = PlayerController->PlayerInput;
    check(PlayerInput)

    InputData.InitialTransform = GetOwner()->GetActorTransform();
    InputData.Bindings.Add(MakeBindingsData());
}

void UInputRecordingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    JsonUtils::WriteInputData(GenerateFileName(), InputData);
}

void UInputRecordingComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    InputData.Bindings.Add(MakeBindingsData());
}

FBindingsData UInputRecordingComponent::MakeBindingsData() const
{
    FBindingsData BindingsData;
    BindingsData.WorldTime = GetWorld()->TimeSeconds;
    for (const auto& AxisBinding : GetOwner()->InputComponent->AxisBindings)
    {
        BindingsData.AxisValues.Add(FAxisData{AxisBinding.AxisName, AxisBinding.AxisValue});
    }

    for (int32 i = 0; i < GetOwner()->InputComponent->GetNumActionBindings(); ++i)
    {
        const auto Action = GetOwner()->InputComponent->GetActionBinding(i);
        if (const auto ActionKeys = PlayerInput->GetKeysForAction(Action.GetActionName()); ActionKeys.Num() > 0)
        {
            const bool Pressed = PlayerInput->IsPressed(ActionKeys[0].Key);
            const bool State = (Pressed && Action.KeyEvent == EInputEvent::IE_Pressed) ||  //
                               (!Pressed && Action.KeyEvent == EInputEvent::IE_Released);
            BindingsData.ActionValues.Add(FActionData{Action.GetActionName(), ActionKeys[0].Key, State});
        }
    }

    return BindingsData;
}

FString UInputRecordingComponent::GenerateFileName() const
{
    FString SavedDir = FPaths::ProjectSavedDir();
    const FString Date = FDateTime::Now().ToString();
    return SavedDir.Append("/Tests/").Append(FileName).Append("_").Append(Date).Append(".json");
}