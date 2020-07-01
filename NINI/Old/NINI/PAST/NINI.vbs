
SET OBJ=CREATEOBJECT("WSCRIPT.SHELL")

'这是电脑的启动项目,请勿删除...',O SETUP

	'OBJ.RUN "C:\NINI\NINI\RUN\RUN.VBS"

'这是电脑的延迟启动项目,请勿删除...'

'REGBACKUP'
	'OBJ.RUN "C:\NINI\NINI\RUN\DELAY\RUN1.VBS"

'这是电脑的自动备份桌面和桌面背景修改项,请勿删除...'

	WSCRIPT.SLEEP 20000
	DIM CHI
DO
	'CHI=OBJ.POPUP("       是否打开桌面备份程序并更换桌面?   /4 Hours    ",60,"SYSTEM MESSAGE:",VBYESNO+32)
	'IF CHI=6 OR CHI=-1 THEN
		OBJ.RUN """C:\NINI\NINI\Desktop Backup\Desktop Backup.exe"" 0",0,FALSE
		OBJ.RUN "C:\NINI\NINI\WALLPAPER.BAT",0,TRUE
	'END IF
	WSCRIPT.SLEEP 14400000
LOOP












                                                     'SIGN BY NINI'