// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tests/Utils/InputRecordingUtils.h"
#include "CoreMinimal.h"


namespace Test
{
	class JsonUtils
	{
	public:
		static bool WriteInputData(const FString& FileName, const FInputData& InputData);
		static bool ReadInputData(const FString& FileName, FInputData& InputData);
	};
}  // namespace Test
