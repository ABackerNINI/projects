@echo off

chcp 65001

REM imdisk -a -s 10G -p "/fs:ntfs /q /y" -m R:

:wait
if not exist R: (
    echo waiting
    ping -n 2 127.0.0.1 > nul
    goto wait
)

REM 创建缓存文件夹

    md R:\Download 1> C:\NINI\RamDisk\RamDiskUserInit.log 2>&1
    md R:\TEMP
    md R:\TEMP\USER
    md R:\TEMP\SYS

    REM 创建VMware Ubuntu20.04挂起快照文件夹
    REM md R:\TEMP\Ubuntu20.04

    REM 创建腾讯和优酷视频缓存文件夹
    md R:\TEMP\TFXPSIPY\e2bcedced23b5622f1bf5d76ea8c0f4f 1>> C:\NINI\RamDisk\RamDiskUserInit.log 2>&1
    md R:\TEMP\youkudisk

    REM 创建QQ音乐缓存文件夹
    md R:\TEMP\QQMusicCache 1>> C:\NINI\RamDisk\RamDiskUserInit.log 2>&1

    REM 创建EDGE缓存文件夹
    md R:\TEMP\EDGE 1>> C:\NINI\RamDisk\RamDiskUserInit.log 2>&1
    md R:\TEMP\EDGE\Default
    md R:\TEMP\EDGE\Default\Cache
    md "R:\TEMP\EDGE\Default\Code Cache"
    rd /S/Q "C:\Users\ABacker\AppData\Local\Microsoft\Edge\User Data\Default\Cache" 1>> C:\NINI\RamDisk\RamDiskUserInit.log 2>&1
    rd /S/Q "C:\Users\ABacker\AppData\Local\Microsoft\Edge\User Data\Default\Code Cache"
    mklink /D "C:\Users\ABacker\AppData\Local\Microsoft\Edge\User Data\Default\Cache" "R:\TEMP\EDGE\Default\Cache" 1>> C:\NINI\RamDisk\RamDiskUserInit.log 2>&1
    mklink /D "C:\Users\ABacker\AppData\Local\Microsoft\Edge\User Data\Default\Code Cache" "R:\TEMP\EDGE\Default\Code Cache"

echo Done 1>> C:\NINI\RamDisk\RamDiskUserInit.log 2>&1

REM pause
