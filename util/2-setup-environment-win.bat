@SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
@ECHO OFF

SET STARTINGDIR=%CD%

:: Check for admin privilages
SETX /M test test > nul 2>&1
IF NOT ["%ERRORLEVEL%"]==["0"] (
	ECHO FAILED. Rerun with administrator privileges.
	GOTO ExitBatch
) 

:: Make sure path to MinGW exists - if so, CD to it
SET MINGWPATH="C:\MinGW\bin"
IF NOT EXIST !MINGWPATH! (ECHO Path not found: %MINGWPATH% && GOTO ExitBatch)
CD /D %MINGWPATH%


ECHO ------------------------------------------
ECHO Installing wget and unzip
ECHO ------------------------------------------
mingw-get install msys-wget-bin msys-unzip-bin

MKDIR temp
CD temp

ECHO ------------------------------------------
ECHO Installing dfu-programmer.
ECHO ------------------------------------------
wget http://iweb.dl.sourceforge.net/project/dfu-programmer/dfu-programmer/0.7.2/dfu-programmer-win-0.7.2.zip
unzip dfu-programmer-win-0.7.2.zip
COPY dfu-programmer.exe ..

ECHO ------------------------------------------
ECHO Downloading driver
ECHO ------------------------------------------
wget http://iweb.dl.sourceforge.net/project/libusb-win32/libusb-win32-releases/1.2.6.0/libusb-win32-bin-1.2.6.0.zip
unzip libusb-win32-bin-1.2.6.0.zip
COPY libusb-win32-bin-1.2.6.0\bin\x86\libusb0_x86.dll ../libusb0.dll

ECHO ------------------------------------------
ECHO Installing driver. Accept prompt.
ECHO ------------------------------------------
IF EXIST "%WinDir%\System32\PnPUtil.exe" (%WinDir%\System32\PnPUtil.exe -i -a dfu-prog-usb-1.2.2\atmel_usb_dfu.inf && GOTO PNPUTILFOUND)
IF EXIST "%WinDir%\Sysnative\PnPUtil.exe" (%WinDir%\Sysnative\PnPUtil.exe -i -a dfu-prog-usb-1.2.2\atmel_usb_dfu.inf && GOTO PNPUTILFOUND)

ECHO FAILED. Could not find PnPUtil.exe in "%WinDir%\System32" or "%WinDir%\Sysnative".

:PNPUTILFOUND

:: Wait then delete directory
ping -n 5 127.0.0.1 > NUL 2>&1
CD ..
RD /s /q temp

ECHO ------------------------------------------
ECHO Finished!

:ExitBatch
CD /D %STARTINGDIR%
ENDLOCAL
PAUSE
EXIT /b