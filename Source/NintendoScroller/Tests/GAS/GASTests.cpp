#include "Misc/AutomationTest.h"
//#include "Tests/GASTests.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Tests/AutomationEditorCommon.h" 
#include "Character/NSCharacter.h"
#include "GameFrameworK/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/GameplayAbilitySystem/GASAttributes.h"
#include "Components/GameplayAbilitySystem/GASGameplayAbility.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GASTests, "NintendoScroller.NintendoScroller.Tests.GAS.GASTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool GASTests::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
