@ECHO OFF & CHCP 936
:WORK
   IF NOT EXIST D:\桌面BACKUP MD D:\桌面BACKUP
   XCOPY /C/E/Y/F "C:\Documents and Settings\Administrator\桌面" "D:\桌面BACKUP"

EXIT
