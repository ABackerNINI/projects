@echo off

REM 16GB+51M
imdisk -a -s 16435M -p "/fs:ntfs /q /y" -m R: 1> C:\NINI\RamDisk\RamDiskCreate.log 2>&1

REM pause
