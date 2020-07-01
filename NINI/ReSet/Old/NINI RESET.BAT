@ECHO OFF & SETLOCAL ENABLEDELAYEDEXPANSION
  TITLE "NINI RESTE"
  
:ECHOS
  ECHO 此程序包含如下功能:
  ECHO  1^).NINI WallPaper(需配合NINI WallPaper.bat使用)及"我的电脑右键加载项"
  ECHO  2^).去除桌面图标小箭头
  ECHO  3^).桌面右键菜单清理
  ECHO  4^).关闭自动播放
  ECHO  5^).禁用休眠
  ECHO 要恢复设置，请打开程序所在文件夹下的"Backup"文件夹
PAUSE>NUL

:BF
  ECHO 正在做备份:
  MD Backup
  REG EXPORT "HKEY_CLASSES_ROOT\Directory\Background\shellex\ContextMenuHandlers" "Backup\恢复桌面右键菜单1.reg"
  REG EXPORT "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" "Backup\恢复桌面右键菜单2.reg"
  REG EXPORT "HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" "Backup\恢复自动播放.reg"
  REG EXPORT "HKEY_CLASSES_ROOT\lnkfile" "Backup\恢复桌面图标小箭头1.reg"
  REG EXPORT "HKEY_CLASSES_ROOT\piffile" "Backup\恢复桌面图标小箭头2.reg"
  ECHO @POWERCFG -H ON>"Backup\恢复休眠.BAT"
  ECHO @REG DELETE "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{20D04FE0-3AEA-1069-A2D8-08002B30309D}\shell\修改背景" /F>"Backup\删除NINI WallPaper项.BAT"

:WORK1
  ECHO 正在加载注册表项:

  ECHO 1^).NINI WallPaper
  REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{20D04FE0-3AEA-1069-A2D8-08002B30309D}\shell\修改背景\command" /V "" /T REG_EXPAND_SZ /D "C:\NINI\WallPaper\WallPaper.BAT" /F
  REG ADD "HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{20D04FE0-3AEA-1069-A2D8-08002B30309D}\shell\打开注册表\command" /V "" /T REG_EXPAND_SZ /D "REGEDIT" /F
PAUSE
  ECHO 2^).去除桌面图标小箭头
  REG DELETE "HKEY_CLASSES_ROOT\lnkfile" /V "IsShortcut" /F
  REG DELETE "HKEY_CLASSES_ROOT\piffile" /V "IsShortcut" /F
  
  ECHO 3^).桌面右键菜单清理
  REG DELETE "HKEY_CLASSES_ROOT\Directory\Background\shellex\ContextMenuHandlers" /F
  REG ADD "HKEY_CLASSES_ROOT\Directory\Background\shellex\ContextMenuHandlers\new" /VE /D "{D969A300-E7FF-11d0-A93B-00A0C90F2719}"
  REG DELETE "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" /V "HotKeysCmds" /F
  REG DELETE "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" /V "IgfxTray" /F
  
  ECHO 4^).关闭自动播放
  REG DELETE "HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /V "NoDriveTypeAutoRun" /F
  REG ADD "HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer" /V "NoDriveTypeAutoRun" /T REG_DWORD /D "0xdd" /F
  
:WORK2
CLS
  ECHO 正在加载其他项:
  
  ECHO 1^).禁用休眠
  POWERCFG -H OFF

:END
::CLS
  ::TASKKILL /F /IM "EXPLORER.EXE"
  ::START EXPLORER.EXE
CLS
  ECHO 正在刷新桌面,请稍等...
  RunDll32.exe USER32.DLL,UpdatePerUserSystemParameters
  ::ECHO WSCRIPT.SLEEP 5000>%TEMP%\SLEEP5000.VBS
  ::%TEMP%\SLEEP5000.VBS
CLS
  ECHO 要恢复设置，请打开程序所在文件夹下的"Backup"文件夹
  START "" "BACKUP"
  
  PAUSE>NUL
EXIT