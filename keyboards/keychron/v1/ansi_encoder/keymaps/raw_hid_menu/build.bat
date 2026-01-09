@echo off
REM Build script for Keychron V1 Raw HID Menu firmware
REM 
REM This script must be run from QMK MSYS terminal
REM (Start Menu -> QMK MSYS)

echo ========================================
echo Keychron V1 Raw HID Menu - Build Script
echo ========================================
echo.

REM Change to QMK firmware directory
cd /c/Repos/Keyboard/qmk_firmware

echo Compiling firmware...
echo.

qmk compile -kb keychron/v1/ansi_encoder -km raw_hid_menu

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo SUCCESS! Firmware compiled successfully
    echo ========================================
    echo.
    echo Output file: keychron_v1_ansi_encoder_raw_hid_menu.bin
    echo Location: C:\Repos\Keyboard\qmk_firmware\.build\
    echo.
    echo Next steps:
    echo 1. Open QMK Toolbox
    echo 2. Select the .bin file
    echo 3. Put keyboard in bootloader mode (hold ESC while plugging in)
    echo 4. Click Flash
    echo.
) else (
    echo.
    echo ========================================
    echo BUILD FAILED - Check errors above
    echo ========================================
    echo.
    echo Common issues:
    echo   - Make sure you're running this in QMK MSYS terminal
    echo   - Check for syntax errors in keymap.c
    echo   - Run 'qmk doctor' to check environment
    echo.
)

pause
