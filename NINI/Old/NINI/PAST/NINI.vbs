
SET OBJ=CREATEOBJECT("WSCRIPT.SHELL")

'���ǵ��Ե�������Ŀ,����ɾ��...',O SETUP

	'OBJ.RUN "C:\NINI\NINI\RUN\RUN.VBS"

'���ǵ��Ե��ӳ�������Ŀ,����ɾ��...'

'REGBACKUP'
	'OBJ.RUN "C:\NINI\NINI\RUN\DELAY\RUN1.VBS"

'���ǵ��Ե��Զ�������������汳���޸���,����ɾ��...'

	WSCRIPT.SLEEP 20000
	DIM CHI
DO
	'CHI=OBJ.POPUP("       �Ƿ�����汸�ݳ��򲢸�������?   /4 Hours    ",60,"SYSTEM MESSAGE:",VBYESNO+32)
	'IF CHI=6 OR CHI=-1 THEN
		OBJ.RUN """C:\NINI\NINI\Desktop Backup\Desktop Backup.exe"" 0",0,FALSE
		OBJ.RUN "C:\NINI\NINI\WALLPAPER.BAT",0,TRUE
	'END IF
	WSCRIPT.SLEEP 14400000
LOOP












                                                     'SIGN BY NINI'