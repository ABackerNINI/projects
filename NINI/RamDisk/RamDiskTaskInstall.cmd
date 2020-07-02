@echo off

REM CREATE RamDisk using ImDisk
WinTaskScheduler.exe "RamDiskCreate" "C:\NINI\RamDisk\RamDiskCreate.cmd"
REM WinTaskScheduler.exe "RamDisk" "C:\NINI\RamDisk\UACRunner.exe" "imdisk -a -s 16435M -p \\\"/fs:ntfs /q /y\\\" -m R:"

REM RUN RamDiskUserInit in 5 seconds after login
WinTaskScheduler.exe "RamDiskUserInit" "C:\NINI\RamDisk\RamDiskUserInit.cmd" "" "PT3S"

pause
