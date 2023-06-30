// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NintendoScrollerEditorTarget : TargetRules {
  public NintendoScrollerEditorTarget(TargetInfo Target) : base(Target) {
    Type = TargetType.Editor;
    DefaultBuildSettings = BuildSettingsVersion.V2;
    IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;
    ExtraModuleNames.AddRange(new string[] { "NintendoScroller" });
  }
}
