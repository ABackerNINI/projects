@ ECHO.
@ ECHO.
@ ECHO.                               说   明
@ ECHO --------------------------------------------------------------------------
@ ECHO  IDE通道在这里看：设备管理器---IDE ATA/ATAPI控制器。一般可看到两个或多个。
@ ECHO  其属性内的“设备类型”，系统默认是“自动检测”，把它设为“无”可以提高
@ ECHO  开机速度。但如果以后要接硬盘或光驱，请记得把相应的通道改为“自动检测”，
@ ECHO  否则进系统后看不到它们。
@ ECHO --------------------------------------------------------------------------
@ ECHO.
@ pause
@shift
:: 修改IDE通道检测设备模式，不接设备的设置为无，提高XP启动速度
:: 建议在系统第二次重新启动检测到所有已经安装的IDE设备后运行
:: Author: Climbing(xclimbing@msn.com)
:: Date: 2006.10.28
:: 修正:顽固不化(http://zzz.sogho.cn) 
:: Date:2008.04.02
@set _debug=
@echo %_debug% off & setlocal ENABLEDELAYEDEXPANSION
set hkey1=HKLM\SYSTEM\CurrentControlSet\Enum\PCIIDE\IDEChannel
set hkey2=HKLM\SYSTEM\CurrentControlSet\Control\Class
echo 检测开始.........
for /f "usebackq tokens=*" %%I in (`reg query %hkey1% ^| find /i "IDEChannel\"`) do call :_check "%%I"
@ ECHO.
@ ECHO.
@ ECHO.
echo IED通道检测设备模式设置完成。
@ ECHO.
pause 
goto :eof

:_check
::echo %1
set subkey=
for /f "usebackq tokens=3*" %%J in (`reg query %1 ^| find /i "driver"`) do set subkey=%%J
set DriverDesc=
for /f "usebackq tokens=3,4*" %%K in (`reg query "%hkey2%\%subkey%" /v DriverDesc ^| find /i "driverdesc"`) do set DriverDesc=%%K %%L 通道
reg query "%hkey2%\%subkey%" /v MasterDeviceType | find /i "0x0" > nul
if not %errorlevel%==1 goto _ChgMaster
echo “%DriverDesc%”的设备0上有设备存在。
goto _CheckSlave

:_ChgMaster
reg add "%hkey2%\%subkey%" /v UserMasterDeviceType /t REG_DWORD /d 3 /f >nul
echo “%DriverDesc%”的设备0上无设备，系统“检测方式”设置为无。

:_CheckSlave
reg query "%hkey2%\%subkey%" /v SlaveDeviceType | find /i "0x0" > nul
if not %errorlevel%==1 goto _ChgSlave
echo “%DriverDesc%”的设备1上有设备存在。
goto :eof

:_ChgSlave
reg add "%hkey2%\%subkey%" /v UserSlaveDeviceType /t REG_DWORD /d 3 /f >nul
echo “%DriverDesc%”的设备1上无设备，系统“检测方式”设置为无。
goto :eof
