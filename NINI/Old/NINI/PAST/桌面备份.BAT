@ECHO OFF & CHCP 936
:WORK
   IF NOT EXIST D:\����BACKUP MD D:\����BACKUP
   XCOPY /C/E/Y/F "C:\Documents and Settings\Administrator\����" "D:\����BACKUP"

EXIT
