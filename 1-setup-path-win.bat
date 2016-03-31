@echo off

reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /f /v Path /t REG_SZ /d "%path%;C:\MinGW\bin;C:\MinGW\msys\1.0\bin" > nul
echo.

if NOT ["%errorlevel%"]==["0"] (
	echo FAILED. You probably just need to run the script with administrator privileges.
) else (
	echo Success!
	setx QMK QMK > nul
)

echo.
pause
