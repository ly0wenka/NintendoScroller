
set EngineVesion=5.1

for /f "skip=2 tokens=2*" %%a in ('reg query "HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine\%EngineVesion%" /v "InstalledDirectory"') do set "EnginePath=%%b"

for /r "%cd%" %%f in (*.uproject) do (
  set "UProjectName=%%~nf"
  goto done
)

:done

set EditorPath="%EnginePath%\Engine\Binaries\Win64\UnrealEditor.exe"
set BuildPath="%EnginePath%\Engine\Build\BatchFiles\Build.bat"
set ProjectPath="%cd%\%UProjectName%.uproject"

call %BuildPath% %UProjectName%Editor Win64 Development -Project=%ProjectPath% -WaitMutex -FromMsBuild -Rocket
%EditorPath% %ProjectPath% -ExecCmds="Automation RunTests Audio" -nosplash