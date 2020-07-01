@echo off

REM CREATE ImDisk
REM WinTaskScheduler.exe "ImDisk" "C:\NINI\ImDisk\CreateImdisk.cmd"
WinTaskScheduler.exe "ImDisk" "C:\NINI\ImDisk\UACRunner.exe" "imdisk -a -s 10G -p \\\"/fs:ntfs /q /y\\\" -m R:"

REM RUN RamDiskUserInit in 5 seconds after login
WinTaskScheduler.exe "RamDiskUserInit" "C:\NINI\ImDisk\RamDiskUserInit.cmd" "" "PT3S"

pause
