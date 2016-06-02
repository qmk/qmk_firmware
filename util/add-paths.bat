@SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
@ECHO off

SET NEWPATH1="C:\MinGW\msys\1.0\bin"
SET NEWPATH2="C:\MinGW\bin"

CD %~dp0

ECHO. > add-paths.log

CALL :AddPath %NEWPATH1%
CALL :AddPath %NEWPATH2%

EXIT /b

:AddPath <pathToAdd>
ECHO %PATH% | FINDSTR /C:"%~1" > nul
IF ERRORLEVEL 1 (
	 REG add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /f /v PATH /t REG_SZ /d "%PATH%;%~1" >> add-paths-detail.log
	IF ERRORLEVEL 0 (
		ECHO Adding   %1 . . . Success! >> add-paths.log
		SET "PATH=%PATH%;%~1"
		COPY NUL UPDATE
	) ELSE (
		ECHO Adding   %1 . . . FAILED. Run this script with administrator privileges. >> add-paths.log
	)	
) ELSE (
	ECHO Skipping %1 - Already in PATH >> add-paths.log
	)
EXIT /b