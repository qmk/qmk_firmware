@SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
@ECHO OFF
SET CMDLINERUNSTR=%SystemRoot%\system32\cmd.exe

DEL script1.log > NUL 2>&1
DEL add-paths.log > NUL 2>&1
DEL add-paths-detail.log > NUL 2>&1
DEL UPDATE > NUL 2>&1

ELEVATE -wait add-paths.bat >> script1.log 2>&1

IF ERRORLEVEL 1 (
	ECHO You denied admin access. Rerun the script, and be sure to press the yes button this time.
) ELSE (
	TYPE add-paths.log 2> NUL
)
ECHO.

:: Branch to UpdateEnv if we need to update
IF EXIST UPDATE (
	DEL UPDATE
	GOTO UpdateEnv
)

GOTO ExitBatch

:: -----------------------------------------------------------------------------

:UpdateEnv
ECHO Making updated PATH go live . . .
REG delete HKCU\Environment /F /V TEMPVAR > NUL 2>&1
setx TEMPVAR 1 > NUL
REG delete HKCU\Environment /F /V TEMPVAR > NUL 2>&1
IF NOT !cmdcmdline! == !CMDLINERUNSTR! (CALL :KillExplorer)
GOTO ExitBatch

:: -----------------------------------------------------------------------------

:ExitBatch
ENDLOCAL
PAUSE
EXIT /b

:: -----------------------------------------------------------------------------

:KillExplorer
ECHO.
ECHO.
ECHO Your desktop will be restarted. 
ECHO.
ECHO All file explorer windows except for the one you launched this script from WILL BE CLOSED.
ECHO.
ECHO Press enter when ready, or close this window if you would rather do a full restart of your computer at a later time.
ECHO.
PAUSE
ping -n 5 127.0.0.1 > NUL 2>&1
ECHO Killing process Explorer.exe. . . 
ECHO.  
taskkill /f /im explorer.exe > NUL
ECHO.   
ECHO Your desktop is now loading. . . 
ECHO.   
ping -n 5 127.0.0.1 > NUL 2>&1
START explorer.exe
START explorer.exe %CD%
EXIT /b