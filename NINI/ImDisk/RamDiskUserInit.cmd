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

    md R:\Download
    md R:\TEMP
    md R:\TEMP\USER
    md R:\TEMP\SYS

    REM 创建腾讯视频缓存文件夹
    md R:\TEMP\TFXPSIPY\e2bcedced23b5622f1bf5d76ea8c0f4f

    REM 创建QQ音乐缓存文件夹
    md R:\TEMP\QQMusicCache

echo Done > C:\NINI\ImDisk\RamDiskUserInit.log

REM pause
