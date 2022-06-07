@echo off

set dirsToRemove=Intermediate ^
DerivedDataCache ^
Binaries ^
Saved ^
.vscode ^
.vs ^
set filesToRemove=*.sln

FOR /R %%f IN (%dirsToRemove%) DO (
    rmdir /s /q %%f
)

FOR /R %%f IN (%filesToRemove%) DO (
    del /q %%f
)

rmdir /s /q Intermediate
rmdir /s /q DerivedDataCache
rmdir /s /q Binaries
rmdir /s /q Saved
rmdir /s /q .vscode
rmdir /s /q .vs

del /q *.sln