@echo off

rem Use this batch file from within an IDE to automatically build your firmware.
rem You can pass command-line arguments to indicate which keyboard and keymap to build.
rem
rem Usage:
rem vscode-build.bat "Working directory" "Keyboard" "Keymap"
rem
rem Ex. vscode-build.bat C:\Projects\qmk_firmware Planck default

SET ROOTDIR="%~dp0..\"

rem Modify this to define your keyboard
rem SET KEYBOARD="ergodox_ez"
if [%1]==[] (
    echo. Keyboard is undefined; defaulting to Planck
    SET KEYBOARD="Planck"
) ELSE (
    SET KEYBOARD="%1"
)

rem Modify this line to adjust your keymap.
rem SET KEYMAP="replicaJunction"
if [%2]==[] (
    echo. Keyboard is undefined; defaulting to default
    SET KEYMAP="default"
) ELSE (
    SET KEYMAP="%2"
)

echo.
echo. --------------
echo. Build started.
echo. --------------
echo.
echo. Working directory: %ROOTDIR%
echo. Keyboard: %KEYBOARD%
echo. Keymap: %KEYMAP%
echo.
echo.
CD /D "%ROOTDIR%"
echo. Cleaning build directory...
make clean KEYBOARD=%KEYBOARD% KEYMAP=%KEYMAP%
echo.
echo. Making keyboard %KEYBOARD% with keymap %KEYMAP%
make KEYBOARD=%KEYBOARD% KEYMAP=%KEYMAP%
echo.
echo. ----------------
echo. Build completed.
echo. ----------------
exit /b