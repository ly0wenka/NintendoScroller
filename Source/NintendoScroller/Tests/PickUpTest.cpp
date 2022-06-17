#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(PickUpTest, "Tests.MushRoom",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool PickUpTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	// Move Character to point
	// Check score
	return true;
}
