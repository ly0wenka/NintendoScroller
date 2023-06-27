@echo off
setlocal EnableDelayedExpansion

set "dir=%cd%"

if not defined dir (
  echo Usage: %0 directory
  exit /b 1
)

set "uproject="

for /r "%CD%" %%f in (*.uproject) do (
  set "uproject=%%~nf"
  goto done
)

:done

if defined uproject (
  echo The .uproject file in %dir% is: %uproject%
  exit /b 0
) else (
  echo No .uproject file found in %dir%
  exit /b 1
)