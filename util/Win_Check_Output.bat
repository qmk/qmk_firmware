@setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
@echo OFF
set BAT_VERSION=v1.0

cls

echo QMK Windows Check Output %BAT_VERSION%
echo QMK Windows Check Output %BAT_VERSION%.>%REPORT_NAME%

:: -----------------------------------------------------------------------------

set MINGW_BASE_DIR=C:\MinGW
set REPORT_NAME=Win_Check_Output.txt

set KEYMAP=atomic-pvc
set KEYMAP_CLEAN=atomic-pvc-clean

:: -----------------------------------------------------------------------------

if %0 == VERBOSE (goto :Verbose_Make) else (goto :Normal_Make)

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

set header=CURRENT DIRECTORY & call :ReportHeader

echo %CD%>>%REPORT_NAME% 2>&1

echo.>>%REPORT_NAME% 2>&1
:: -----------------------------------------------------------------------------

set header=CURRENT PATHS & call :ReportHeader

for %%A in ("%path:;=";"%") do (echo %%~A>>%REPORT_NAME% 2>&1)

echo.>>%REPORT_NAME% 2>&1

:: -----------------------------------------------------------------------------

set header=CURRENT ENVIRONMENTAL SETTINGS & call :ReportHeader

set>>%REPORT_NAME% 2>&1
echo.>>%REPORT_NAME% 2>&1

:: -----------------------------------------------------------------------------

set header=KEY EXECUTABLE LOCATIONS - GENERAL & call :ReportHeader

set filename=make.exe & set version_cmd=--version & set version_find="GNU Make" & call :ReportVersion
set filename=git.exe & set version_cmd=--version & set version_find="git" & call :ReportVersion
set filename=cmp.exe & set version_cmd=--version & set version_find="cmp" & call :ReportVersion

:: -----------------------------------------------------------------------------

set header=EXECUTABLE LOCATIONS - AVR MCU COMPILERS & call :ReportHeader

set filename=avr-gcc.exe & set version_cmd=--version & set version_find="avr" & call :ReportVersion
set filename=avr-objcopy.exe & set version_cmd=--version & set version_find="GNU objcopy" & call :ReportVersion
set filename=avr-objdump.exe & set version_cmd=--version & set version_find="GNU objdump" & call :ReportVersion
set filename=avr-size.exe & set version_cmd=--version & set version_find="GNU size" & call :ReportVersion
set filename=avr-ar.exe & set version_cmd=--version & set version_find="GNU ar" & call :ReportVersion
set filename=avr-nm.exe & set version_cmd=--version & set version_find="GNU nm" & call :ReportVersion

:: -----------------------------------------------------------------------------

set header=EXECUTABLE LOCATIONS - ARM MCU COMPILERS & call :ReportHeader

set filename=arm-none-eabi-gcc.exe & set version_cmd=--version & set version_find="arm-none-eabi-gcc" & call :ReportVersion
set filename=arm-none-eabi-objcopy.exe & set version_cmd=--version & set version_find="GNU objcopy" & call :ReportVersion
set filename=arm-none-eabi-objdump.exe & set version_cmd=--version & set version_find="GNU objdump" & call :ReportVersion
set filename=arm-none-eabi-size.exe & set version_cmd=--version & set version_find="GNU size" & call :ReportVersion
set filename=arm-none-eabi-ar.exe & set version_cmd=--version & set version_find="GNU ar" & call :ReportVersion
set filename=arm-none-eabi-nm.exe & set version_cmd=--version & set version_find="GNU nm" & call :ReportVersion

:: -----------------------------------------------------------------------------

set header=EXECUTABLE LOCATIONS - NATIVE COMPILERS & call :ReportHeader

set filename=gcc.exe & set version_cmd=--version & set version_find="gcc" & call :ReportVersion
set filename=objcopy.exe & set version_cmd=--version & set version_find="GNU objcopy" & call :ReportVersion
set filename=objdump.exe & set version_cmd=--version & set version_find="GNU objdump" & call :ReportVersion
set filename=size.exe & set version_cmd=--version & set version_find="GNU size" & call :ReportVersion
set filename=ar.exe & set version_cmd=--version & set version_find="GNU ar" & call :ReportVersion
set filename=nm.exe & set version_cmd=--version & set version_find="GNU nm" & call :ReportVersion

:: -----------------------------------------------------------------------------

set header=EXECUTABLE LOCATIONS - PROGRAMMERS & call :ReportHeader

set filename=dfu-programmer.exe & set version_cmd=--version & set version_find="dfu" & call :ReportVersion
set filename=batchisp.exe & set version_cmd=-version & set version_find="batchisp" & call :ReportVersion
set filename=dfu-util.exe & call :Report
set filename=teensy_loader_cli.exe & call :Report
set filename=hid_bootloader_cli.exe & call :Report
set filename=avrdude.exe & call :Report

:: -----------------------------------------------------------------------------

set header=EXECUTABLE LOCATIONS - OPTIONAL & call :ReportHeader
set filename=cppcheck.exe & call :Report
set filename=doxygen.exe & call :Report
set filename=gdb-config.exe & call :Report
set filename=wget.exe & call :Report
set filename=unzip.exe & call :Report

:: -----------------------------------------------------------------------------

set header=MINGW CHECK - OPTIONAL & call :ReportHeader
if exist %MINGW_BASE_DIR% (echo Expected MinGW Base Dir = %MINGW_BASE_DIR%>>%REPORT_NAME% 2>&1) else (echo Expected MinGW Base Dir = %MINGW_BASE_DIR% - Not Found>>%REPORT_NAME% 2>&1)
echo.>>%REPORT_NAME% 2>&1
set filename=mingw32-make.exe & set version_cmd=--version & set version_find="GNU Make" & call :ReportVersion
if exist %MINGW_BASE_DIR%\bin\gcc.exe (ECHO It is not recommended to have make.exe in mingw/bin.>>%REPORT_NAME% 2>&1 & echo.>>%REPORT_NAME% 2>&1)

:: -----------------------------------------------------------------------------

set header=MAKE CHECK & call :ReportHeader
if exist Makefile (set MAKE_CMD=%MAKE_CMD_LEVEL_0% & goto MakeFound)
if exist ..\Makefile (set MAKE_CMD=%MAKE_CMD_LEVEL_1% & goto MakeFound)
if exist ..\..\Makefile (set MAKE_CMD=%MAKE_CMD_LEVEL_2% & goto MakeFound)

echo No Makfile Found.>>%REPORT_NAME% 2>&1
echo.>>%REPORT_NAME% 2>&1
echo ------------------------------------------------------------------------->>%REPORT_NAME% 2>&1

goto ContinueAfterMake

:MakeFound
call :RunMake

:ContinueAfterMake
goto ExitBatch

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
	set header=MAKE CLEAN & call :ReportHeader
	echo Make Command = %MAKE_CMD% %KEYMAP_CLEAN%>>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
	%MAKE_CMD% %KEYMAP_CLEAN%>>%REPORT_NAME% 2>&1
	set header=MAKE & call :ReportHeader
	echo Make Command = %MAKE_CMD% %KEYMAP%>>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
	%MAKE_CMD% %KEYMAP%>>%REPORT_NAME% 2>&1
	echo ------------------------------------------------------------------------->>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
exit /b

:ReportHeader
	echo ------------------------------------------------------------------------->>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
	echo %header%>>%REPORT_NAME% 2>&1
	echo.>>%REPORT_NAME% 2>&1
exit /b

:Report
	echo Filename = %filename% >>%REPORT_NAME% 2>&1
	<nul set /p output="Location = " >>%REPORT_NAME% 2>&1
	where %filename%  >>%REPORT_NAME% 2> NUL
	if ERRORLEVEL 1 (echo Not Found >>%REPORT_NAME% 2>&1 & goto :EndReport)

	:EndReport
	echo.>>%REPORT_NAME% 2>&1
	<nul set /p output="."
exit /b

:ReportVersion
	echo Filename = %filename% >>%REPORT_NAME% 2>&1
	<nul set /p output="Location = " >>%REPORT_NAME% 2>&1
	where %filename%  >>%REPORT_NAME% 2> NUL
	if ERRORLEVEL 1 (echo Not Found >>%REPORT_NAME% 2>&1 & goto :EndReportVersion)
	<nul set /p output ="Version  = " >>%REPORT_NAME% 2>&1

	(%filename% %version_cmd% | find %version_find%) >>%REPORT_NAME% 2>&1

	:EndReportVersion
	echo.>>%REPORT_NAME% 2>&1
	<nul set /p output="."
exit /b