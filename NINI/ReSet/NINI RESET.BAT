@ECHO OFF & SETLOCAL ENABLEDELAYEDEXPANSION
  TITLE "NINI RESTE"
  
:ECHOS
  ECHO �˳���������¹���:
  ECHO  1^).ȥ������ͼ��С��ͷ
  ECHO  2^).�����Ҽ��˵�����
  ECHO Ҫ�ָ����ã���򿪳��������ļ����µ�"Backup"�ļ���
PAUSE>NUL

:BF
  ECHO ����������:
  MD Backup
  REG EXPORT "HKEY_CLASSES_ROOT\Directory\Background\shellex\ContextMenuHandlers" "Backup\�ָ������Ҽ��˵�1.reg"
  REG EXPORT "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" "Backup\�ָ������Ҽ��˵�2.reg"
  REG EXPORT "HKEY_CLASSES_ROOT\lnkfile" "Backup\�ָ�����ͼ��С��ͷ1.reg"
  REG EXPORT "HKEY_CLASSES_ROOT\piffile" "Backup\�ָ�����ͼ��С��ͷ2.reg"

:WORK1
  ECHO ���ڼ���ע�����:
  ECHO 2^).ȥ������ͼ��С��ͷ
  REG DELETE "HKEY_CLASSES_ROOT\lnkfile" /V "IsShortcut" /F
  REG DELETE "HKEY_CLASSES_ROOT\piffile" /V "IsShortcut" /F
  
  ECHO 3^).�����Ҽ��˵�����
  REG DELETE "HKEY_CLASSES_ROOT\Directory\Background\shellex\ContextMenuHandlers" /F
  REG ADD "HKEY_CLASSES_ROOT\Directory\Background\shellex\ContextMenuHandlers\new" /VE /D "{D969A300-E7FF-11d0-A93B-00A0C90F2719}"
  REG DELETE "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" /V "HotKeysCmds" /F
  REG DELETE "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" /V "IgfxTray" /F

:END
::CLS
  ::TASKKILL /F /IM "EXPLORER.EXE"
  ::START EXPLORER.EXE
CLS
  ECHO ����ˢ������,���Ե�...
  RunDll32.exe USER32.DLL,UpdatePerUserSystemParameters
  ::ECHO WSCRIPT.SLEEP 5000>%TEMP%\SLEEP5000.VBS
  ::%TEMP%\SLEEP5000.VBS
CLS
  ECHO Ҫ�ָ����ã���򿪳��������ļ����µ�"Backup"�ļ���
  START "" "BACKUP"
  
  PAUSE>NUL
EXIT