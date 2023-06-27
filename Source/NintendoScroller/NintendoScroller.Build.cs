// Fill out your copyright notice in the Description page of Project Settings.

using Internal;
using UnrealBuildTool;

public class NintendoScroller : ModuleRules {
  public NintendoScroller(ReadOnlyTargetRules Target) : base(Target) {

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
    Console.WriteLine(
        $"Unreal version {Target.Version.MajorVersion}.{Target.Version.MinorVersion}.{Target.Version.PatchVersion}");
    PublicDependencyModuleNames.AddRange(
        new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Json", "JsonUtilities", "UMG" });

    PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks"});
    PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd"});
    // PrivateDependencyModuleNames.AddRange(new string[] {"GameplayAbilities", "GameplayTags", "GameplayTasks"});
    PublicIncludePaths.Add("NintendoScroller");
    // Uncomment if you are using Slate UI
    // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"
    // });

    // Uncomment if you are using online features
    // PrivateDependencyModuleNames.Add("OnlineSubsystem");

    // To include OnlineSubsystemSteam, add it to the plugins section in your
    // uproject file with the Enabled attribute set to true
  }
}
