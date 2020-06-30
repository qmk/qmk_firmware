#!/bin/sh
ALL_CONFIGS=$*
GREP="grep"

cat <<- EOF > lib/lufa/Bootloaders/DFU/Keyboard.h
#ifndef QMK_KEYBOARD
#define QMK_KEYBOARD

$($GREP "MANUFACTURER[ \t]" $ALL_CONFIGS -h | tail -1)
$($GREP "PRODUCT[ \t]" $ALL_CONFIGS -h | tail -1 | tr -d '\r') Bootloader
$($GREP "QMK_ESC_OUTPUT[ \t]" $ALL_CONFIGS -h | tail -1)
$($GREP "QMK_ESC_INPUT[ \t]" $ALL_CONFIGS -h | tail -1)
$($GREP "QMK_LED[ \t]" $ALL_CONFIGS -h | tail -1)
$($GREP "QMK_SPEAKER[ \t]" $ALL_CONFIGS -h | tail -1)
#endif
EOF
