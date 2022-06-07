::set ProjectRoot=S:\repos\unreal\NintendoScroller
set BackupFolder=Backup
set dirs=Intermediate DerivedDataCache Saved Binaries .vs Build

::pushd "%ProjectRoot%"
FOR %%d IN (%dirs%) DO (
    move %%d %BackupFolder%
)
::popd