

SET OBJ=CREATEOBJECT("WSCRIPT.SHELL")


'���ǵ��Ե�������Ŀ������ɾ��...'

'��������...'
	OBJ.RUN "CMD.EXE /C POWERCFG -H OFF",0

'ע�����...'
	OBJ.RUN "C:\NINI\RESET\WALLPAPER.REG"
