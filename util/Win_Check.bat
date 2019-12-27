@setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
@echo OFF
set BAT_VERSION=v1.0
set REPORT_NAME=Win_Check_Output.txt

:: -----------------------------------------------------------------------------

cls

echo QMK Windows Check Output %BAT_VERSION%
echo QMK Windows Check Output %BAT_VERSION%.>%REPORT_NAME%

:: -----------------------------------------------------------------------------

set MINGW_BASE_DIR=C:\MinGW

set KEYMAP=atomic-pvc
set KEYMAP_CLEAN=atomic-pvc-clean

:: -----------------------------------------------------------------------------

if /I "%1" EQU VERBOSE (goto :Verbose_Make) else (goto :Normal_Make)

:Normal_Make
set MAKE_CMD_LEVEL_0=make -r -f Makefile COLOR=FALSE
set MAKE_CMD_LEVEL_1=make -r -f ../Makefile COLOR=FALSE
set MAKE_CMD_LEVEL_2=make -r -f ../../Makefile COLOR=FALSE
goto :Start_Report

:Verbose_Make
echo Verbose Mode
set MAKE_CMD_LEVEL_0=make -r -d -f Makefile COLOR=FALSE VERBOSE=TRUE
set MAKE_CMD_LEVEL_1=make -r -d -f ../Makefile COLOR=FALSE VERBOSE=TRUE
set MAKE_CMD_LEVEL_2=make -r -d -f ../../Makefile COLOR=FALSE VERBOSE=TRUE
goto :Start_Report

:Start_Report


:: -----------------------------------------------------------------------------

set HEADER=CURRENT DIRECTORY & call :ReportHeader

echo %CD%>>%REPORT_NAME% 2>&1

echo.>>%REPORT_NAME% 2>&1

:: -----------------------------------------------------------------------------

set HEADER=CURRENT PATHS & call :ReportHeader

for %%A in ("%path:;=";"%") do (echo %%~A>>%REPORT_NAME% 2>&1)

echo.>>%REPORT_NAME% 2>&1

:: -----------------------------------------------------------------------------

rem set HEADER=CURRENT ENVIRONMENTAL SETTINGS & call :ReportHeader

rem set>>%REPORT_NAME% 2>&1
rem echo.>>%REPORT_NAME% 2>&1

:: -----------------------------------------------------------------------------

set HEADER=KEY EXECUTABLE LOCATIONS - GENERAL & call :ReportHeader

set FILENAME=make.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU Make" & call :ReportVersion
set FILENAME=git.exe & set VERSION_CMD=--version & set VERSION_FIND="git" & call :ReportVersion
set FILENAME=cmp.exe & set VERSION_CMD=--version & set VERSION_FIND="cmp" & call :ReportVersion

:: -----------------------------------------------------------------------------

set HEADER=EXECUTABLE LOCATIONS - AVR MCU COMPILERS & call :ReportHeader

set FILENAME=avr-gcc.exe & set VERSION_CMD=--version & set VERSION_FIND="avr" & call :ReportVersion
set FILENAME=avr-objcopy.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU objcopy" & call :ReportVersion
set FILENAME=avr-objdump.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU objdump" & call :ReportVersion
set FILENAME=avr-size.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU size" & call :ReportVersion
set FILENAME=avr-ar.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU ar" & call :ReportVersion
set FILENAME=avr-nm.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU nm" & call :ReportVersion

:: -----------------------------------------------------------------------------

set HEADER=EXECUTABLE LOCATIONS - ARM MCU COMPILERS & call :ReportHeader

set FILENAME=arm-none-eabi-gcc.exe & set VERSION_CMD=--version & set VERSION_FIND="arm-none-eabi-gcc" & call :ReportVersion
set FILENAME=arm-none-eabi-objcopy.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU objcopy" & call :ReportVersion
set FILENAME=arm-none-eabi-objdump.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU objdump" & call :ReportVersion
set FILENAME=arm-none-eabi-size.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU size" & call :ReportVersion
set FILENAME=arm-none-eabi-ar.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU ar" & call :ReportVersion
set FILENAME=arm-none-eabi-nm.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU nm" & call :ReportVersion

:: -----------------------------------------------------------------------------

set HEADER=EXECUTABLE LOCATIONS - NATIVE COMPILERS & call :ReportHeader

set FILENAME=gcc.exe & set VERSION_CMD=--version & set VERSION_FIND="gcc" & call :ReportVersion
set FILENAME=objcopy.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU objcopy" & call :ReportVersion
set FILENAME=objdump.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU objdump" & call :ReportVersion
set FILENAME=size.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU size" & call :ReportVersion
set FILENAME=ar.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU ar" & call :ReportVersion
set FILENAME=nm.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU nm" & call :ReportVersion

:: -----------------------------------------------------------------------------

set HEADER=EXECUTABLE LOCATIONS - PROGRAMMERS & call :ReportHeader

set FILENAME=dfu-programmer.exe & set VERSION_CMD=--version & set VERSION_FIND="dfu" & call :ReportVersion
set FILENAME=batchisp.exe & set VERSION_CMD=-version & set VERSION_FIND="batchisp" & call :ReportVersion
set FILENAME=dfu-util.exe & call :Report
set FILENAME=teensy_loader_cli.exe & call :Report
set FILENAME=hid_bootloader_cli.exe & call :Report
set FILENAME=avrdude.exe & call :Report

:: -----------------------------------------------------------------------------

set HEADER=EXECUTABLE LOCATIONS - OPTIONAL & call :ReportHeader
set FILENAME=cppcheck.exe & call :Report
set FILENAME=doxygen.exe & call :Report
set FILENAME=gdb-config.exe & call :Report
set FILENAME=wget.exe & call :Report
set FILENAME=unzip.exe & call :Report

:: -----------------------------------------------------------------------------

set HEADER=MINGW CHECK - OPTIONAL & call :ReportHeader
if exist %MINGW_BASE_DIR% (echo Expected MinGW Base Dir = %MINGW_BASE_DIR%>>%REPORT_NAME% 2>&1) else (echo Expected MinGW Base Dir = %MINGW_BASE_DIR% - Not Found>>%REPORT_NAME% 2>&1)
echo.>>%REPORT_NAME% 2>&1
set FILENAME=mingw32-make.exe & set VERSION_CMD=--version & set VERSION_FIND="GNU Make" & call :ReportVersion
if exist %MINGW_BASE_DIR%\bin\make.exe (ECHO It is not recommended to have make.exe in mingw/bin.>>%REPORT_NAME% 2>&1 & echo.>>%REPORT_NAME% 2>&1)

:: -----------------------------------------------------------------------------

set HEADER=MAKE CHECK & call :ReportHeader
if exist Makefile (set MAKE_CMD=%MAKE_CMD_LEVEL_0% & goto MakeFound)
if exist ..\Makefile (set MAKE_CMD=%MAKE_CMD_LEVEL_1% & goto MakeFound)
if exist ..\..\Makefile (set MAKE_CMD=%MAKE_CMD_LEVEL_2% & goto MakeFound)

echo No Makfile Found.>>%REPORT_NAME% 2>&1
echo.>>%REPORT_NAME% 2>&1
echo ------------------------------------------------------------------------->>%REPORT_NAME% 2>&1

goto :ContinueAfterMake

:MakeFound
call :RunMake

:ContinueAfterMake
goto :ExitBatch

:ExitBatch
	echo Done!
	echo.
	rem type %REPORT_NAME%
	echo.
	echo See %REPORT_NAME% for the report.
	endlocal
exit /b

:: -----------------------------------------------------------------------------

:RunMake

	echo Makfile Found.>>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
	set HEADER=MAKE CLEAN & call :ReportHeader
	echo Make Command = %MAKE_CMD% %KEYMAP_CLEAN%>>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
	%MAKE_CMD% %KEYMAP_CLEAN%>>%REPORT_NAME% 2>&1
	set HEADER=MAKE & call :ReportHeader
	echo Make Command = %MAKE_CMD% %KEYMAP%>>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
	%MAKE_CMD% %KEYMAP%>>%REPORT_NAME% 2>&1
	echo ------------------------------------------------------------------------->>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
exit /b

:ReportHeader
	echo ------------------------------------------------------------------------->>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
	echo %HEADER%>>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
exit /b

:Report
	echo Filename = %FILENAME% >>%REPORT_NAME% 2>&1
	<nul set /p output="Location = " >>%REPORT_NAME% 2>&1
	where %FILENAME%  >>%REPORT_NAME% 2> NUL
	if ERRORLEVEL 1 (echo Not Found >>%REPORT_NAME% 2>&1 & goto :EndReport)

	:EndReport
	echo.>>%REPORT_NAME% 2>&1
	<nul set /p output="."
exit /b

:ReportVersion
	echo Filename = %FILENAME% >>%REPORT_NAME% 2>&1
	<nul set /p output="Location = " >>%REPORT_NAME% 2>&1
	where %FILENAME%  >>%REPORT_NAME% 2> NUL
	if ERRORLEVEL 1 (echo Not Found >>%REPORT_NAME% 2>&1 & goto :EndReportVersion)
	<nul set /p output ="Version  = " >>%REPORT_NAME% 2>&1

	(%FILENAME% %VERSION_CMD% | find %VERSION_FIND%) >>%REPORT_NAME% 2>&1

	:EndReportVersion
	echo.>>%REPORT_NAME% 2>&1
	<nul set /p output="."
exit /b