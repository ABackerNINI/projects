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

    md R:\Download > C:\NINI\ImDisk\RamDiskUserInit.log
    md R:\TEMP
    md R:\TEMP\USER
    md R:\TEMP\SYS

    REM 创建腾讯视频缓存文件夹
    md R:\TEMP\TFXPSIPY\e2bcedced23b5622f1bf5d76ea8c0f4f >> C:\NINI\ImDisk\RamDiskUserInit.log

    REM 创建QQ音乐缓存文件夹
    md R:\TEMP\QQMusicCache >> C:\NINI\ImDisk\RamDiskUserInit.log

    REM 创建EDGE缓存文件夹
    md R:\TEMP\EDGE >> C:\NINI\ImDisk\RamDiskUserInit.log
    md R:\TEMP\EDGE\Default
    md R:\TEMP\EDGE\Default\Cache
    md "R:\TEMP\EDGE\Default\Code Cache"
    rd /S/Q "C:\Users\ABacker\AppData\Local\Microsoft\Edge\User Data\Default\Cache" >> C:\NINI\ImDisk\RamDiskUserInit.log
    rd /S/Q "C:\Users\ABacker\AppData\Local\Microsoft\Edge\User Data\Default\Code Cache"
    mklink /D "C:\Users\ABacker\AppData\Local\Microsoft\Edge\User Data\Default\Cache" "R:\TEMP\EDGE\Default\Cache" >> C:\NINI\ImDisk\RamDiskUserInit.log
    mklink /D "C:\Users\ABacker\AppData\Local\Microsoft\Edge\User Data\Default\Code Cache" "R:\TEMP\EDGE\Default\Code Cache"

echo Done >> C:\NINI\ImDisk\RamDiskUserInit.log

REM pause
