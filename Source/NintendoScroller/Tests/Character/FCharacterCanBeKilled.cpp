#include "Character/NSCharacter.h"
#include "Misc/AutomationTest.h"
#include "Tests/Utils/TestUtils.h"
#include "Tests/Utils/WorldHelper.h"
#include "Tests/Utils/LevelScope/LevelScope.h"
#include "Tests/Utils/Character/CharacterTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCharacterCanBeKilled, "NSGame.Character.CharacterCanBeKilled",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

using namespace NS::Test;
using namespace NS::CharacterTest;


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCharacterDestroyedLatentCommand, ANSCharacter*, Character, float, LifeSpan);
bool FCharacterDestroyedLatentCommand::Update()
{
    const double NewTime = FPlatformTime::Seconds();
    if (NewTime - StartTime >= LifeSpan)
    {
        if (IsValid(Character))
        {
            UE_LOG(LogNSCharacterTests, Error, TEXT("Character wasn't destroyed"));
        }
        return true;
    }
    return false;
}

bool FCharacterCanBeKilled::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/Tests/EmptyTestLevel");

    UWorld* World = WorldHelper::GetWorld();
    if (!TestNotNull("World exists", World)) return false;

    const FTransform InitialTransform{FVector{0.0f, -240.0f, 110.0f}};
    ANSCharacter* Character = CreateBlueprintDeferred<ANSCharacter>(World, CharacterTestBPName, InitialTransform);
    if (!TestNotNull("Character exists", Character)) return false;

    FHealthData HealthData;
    HealthData.MaxHealth = 1000.0f;
    HealthData.LifeSpan = 1.5f;
    CallFuncByNameWithParams(Character, "SetHealthData", {HealthData.ToString()});

    Character->FinishSpawning(InitialTransform);

    TestEqual("Health is full", Character->GetHealthPercent(), 1.0f);

    const auto KillingDamageAmount = HealthData.MaxHealth;
    Character->TakeDamage(KillingDamageAmount, FDamageEvent{}, nullptr, nullptr);

    TestEqual("Health is empty", Character->GetHealthPercent(), 0.0f);
    TestTrueExpr(Character->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_None);

    ENUM_LOOP_START(ECollisionChannel, EElem)
    if (EElem != ECollisionChannel::ECC_OverlapAll_Deprecated)
    {
        TestTrueExpr(Character->GetCapsuleComponent()->GetCollisionResponseToChannel(EElem) == ECollisionResponse::ECR_Ignore);
    }
    ENUM_LOOP_END

    TestTrueExpr(Character->GetMesh()->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics);
    TestTrueExpr(Character->GetMesh()->IsSimulatingPhysics());
    TestTrueExpr(FMath::IsNearlyEqual(Character->GetLifeSpan(), HealthData.LifeSpan));

    // ADD_LATENT_AUTOMATION_COMMAND(FCharacterDestroyedLatentCommand(Character, HealthData.LifeSpan));
    ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand(
        [Character]()
        {
            if (IsValid(Character))
            {
                UE_LOG(LogNSCharacterTests, Error, TEXT("Character wasn't destroyed"));
            }
        },
        HealthData.LifeSpan));

    return true;
}
