@ECHO OFF & SETLOCAL ENABLEDELAYEDEXPANSION & CHCP 936
CLS


:BF
  :B1
	IF NOT EXIST "C:\NINI\WallPaper\IM\WallPaper.DAT" (
		ECHO ���ڸ����б�...
		START /WAIT C:\NINI\WallPaper\�����б�.vbs
	)
	FOR /F "TOKENS=*" %%I IN (C:\NINI\WallPaper\IM\WallPaper.DAT) DO (
		SET NUM=%%I
		GOTO B2
	)
  :B2
	IF EXIST C:\NINI\WallPaper\IM\_WallPaper.DAT DEL C:\NINI\WallPaper\IM\_WallPaper.DAT
	FOR /F "SKIP=1 TOKENS=*" %%I IN (C:\NINI\WallPaper\IM\WallPaper.DAT) DO (ECHO %%I>>C:\NINI\WallPaper\IM\_WallPaper.DAT)
	IF NOT EXIST C:\NINI\WallPaper\IM\_WallPaper.DAT (
		DEL C:\NINI\WallPaper\IM\WallPaper.DAT
		ECHO ���ڸ����б�...
		START /WAIT C:\NINI\WallPaper\�����б�.vbs
		GOTO BF
	)

	MOVE C:\NINI\WallPaper\IM\_WallPaper.DAT C:\NINI\WallPaper\IM\WallPaper.DAT

	IF NOT EXIST "%NUM%" GOTO B1
  :B3
	ver|findstr /i "xp">nul 2>nul&& GOTO WORK1 || GOTO WORK2

  :WORK1
	ECHO ����ת��ͼƬ...
	C:\NINI\WallPaper\NINI_WallPaper.EXE "%NUM%" "C:\NINI\WallPaper\WallPaper.BMP"
	::REG ADD "HKEY_CURRENT_USER\CONTROL PANEL\DESKTOP" /V WALLPAPER /D "C:\NINI\WallPaper\WallPaper.BMP" /F
	::REG ADD "HKEY_CURRENT_USER\CONTROL PANEL\DESKTOP" /V WALLPAPERSTYLE /D "2" /F
	ECHO ����ˢ������...
	RunDll32.exe USER32.DLL,UpdatePerUserSystemParameters

	GOTO END

  :WORK2
	ECHO Set f =  CreateObject("Scripting.FileSystemObject").GetFile("%NUM%")>C:\NINI\WallPaper\_WALLPAPER_WIN7.VBS
	ECHO Set vs = CreateObject("Shell.Application").NameSpace(f.ParentFolder.Path).ParseName(f.Name).Verbs>>C:\NINI\WallPaper\_WALLPAPER_WIN7.VBS
	ECHO For Each v In vs>>C:\NINI\WallPaper\_WALLPAPER_WIN7.VBS
	ECHO If v.Name = "����Ϊ���汳��(&B)" Then v.DoIt>>C:\NINI\WallPaper\_WALLPAPER_WIN7.VBS
	ECHO Next>>C:\NINI\WallPaper\_WALLPAPER_WIN7.VBS
	ECHO WScript.Sleep 500>>C:\NINI\WallPaper\_WALLPAPER_WIN7.VBS

	C:\NINI\WallPaper\_WALLPAPER_WIN7.VBS
:END
	ECHO �޸�����ɹ�...

EXIT