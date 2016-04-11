@SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
@ECHO OFF
SET CMDLINERUNSTR=%SystemRoot%\system32\cmd.exe

SET NEWPATH1="C:\MinGW\msys\1.0\bin"
SET NEWPATH2="C:\MinGW\bin"

:: Make sure we're running with administrator privileges
NET SESSION >nul 2>&1
IF ERRORLEVEL 1 (
	ECHO FAILED. Run this script with administrator privileges.
	GOTO ExitBatch
)

:: Make sure the second path exists. The first path won't be created until the second script is run
IF NOT EXIST !NEWPATH2! (ECHO Path not found: %NEWPATH2% && GOTO ExitBatch)

:: Add paths
CALL :AddPath %NEWPATH1%
CALL :AddPath %NEWPATH2%

:: Branch to UpdateEnv if we need to update
IF DEFINED UPDATE (GOTO UpdateEnv)

GOTO ExitBatch

:: -----------------------------------------------------------------------------

:UpdateEnv
ECHO Making updated PATH go live . . .
REG delete HKCU\Environment /F /V TEMPVAR > nul 2>&1
setx TEMPVAR 1 > nul 2>&1
REG delete HKCU\Environment /F /V TEMPVAR > nul 2>&1
IF NOT !cmdcmdline! == !CMDLINERUNSTR! (CALL :KillExplorer)
GOTO ExitBatch

:: -----------------------------------------------------------------------------

:ExitBatch
ENDLOCAL
PAUSE
EXIT /b

:: -----------------------------------------------------------------------------

:AddPath <pathToAdd>
ECHO %PATH% | FINDSTR /C:"%~1" > nul
IF ERRORLEVEL 1 (
	REG add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /f /v PATH /t REG_SZ /d "%PATH%;%~1"  > nul 2>&1
	IF ERRORLEVEL 0 (
		ECHO Adding   %1 . . . Success!
		SET "PATH=%PATH%;%~1"
		SET UPDATE=1
	) ELSE (
		ECHO Adding   %1 . . . FAILED. Run this script with administrator privileges.
	)	
) ELSE (
	ECHO Skipping %1 - Already in PATH
	)
EXIT /b

:: -----------------------------------------------------------------------------

:KillExplorer

ECHO Your desktop is being restarted, please wait. . .   
ping -n 5 127.0.0.1 > NUL 2>&1   
ECHO Killing process Explorer.exe. . .   
taskkill /f /im explorer.exe   
ECHO.   
ECHO Your desktop is now loading. . .   
ping -n 5 127.0.0.1 > NUL 2>&1   
ECHO.   
ping -n 5 127.0.0.1 > NUL 2>&1   
START explorer.exe
START explorer.exe %CD%
EXIT /b