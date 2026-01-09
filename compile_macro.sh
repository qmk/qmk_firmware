#!/bin/bash
# Keychron V1 Macro Keymap Build Script
# Run this in QMK MSYS terminal

echo "========================================"
echo "Keychron V1 Command Macro - Quick Build"
echo "========================================"
echo ""

# Navigate to QMK firmware directory
cd "$(dirname "$0")"

echo "Building keychron/v1/ansi_encoder:macro"
echo ""

# Compile the firmware
qmk compile -kb keychron/v1/ansi_encoder -km macro

# Check if build was successful
if [ $? -eq 0 ]; then
    echo ""
    echo "========================================"
    echo "✓ Build Successful!"
    echo "========================================"
    echo ""
    echo "Firmware location:"
    echo "$(pwd)/.build/keychron_v1_ansi_encoder_macro.bin"
    echo ""
    echo "Next step: Flash with QMK Toolbox"
    echo "See C:/CLIPALS/docs/BUILD_AND_FLASH.md for flash instructions"
    echo ""
else
    echo ""
    echo "========================================"
    echo "✗ Build Failed"
    echo "========================================"
    echo ""
    echo "Check errors above"
    echo "Common fixes:"
    echo "  - Run 'qmk setup' if this is first time"
    echo "  - Check that files exist in keymaps/macro/"
    echo ""
    exit 1
fi
