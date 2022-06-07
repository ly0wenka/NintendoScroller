@echo off

set VersionSelector=S:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe
set ProjectName=NintendoScroller.uproject
set ProjectPath=%CD%\%ProjectName%

"%VersionSelector%" -switchversion