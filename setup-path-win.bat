@echo off
setx /M path "%PATH%;C:\MinGW\bin" > nul 2>&1
if NOT ["%errorlevel%"]==["0"] (
	echo FAILED. Rerun with administrator privileges.
	pause
) else (
	echo Success!
	pause
)
