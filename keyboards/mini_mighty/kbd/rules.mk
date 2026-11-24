# GCC compiles the switch in QMK's KEYCODE2CONSUMER() (tmk_core/protocol/report.h) into
# a 54 B lookup table, twice, and on AVR a const table is copied into RAM: 108 of the
# 16U2's 512 B. That left too little stack, and a USB control request (e.g. a Windows app
# enumerating HID devices) could run it into tapping_key and waiting_buffer, which showed
# up as phantom key presses. This compiles switches as compare chains instead, for a
# little flash, and keeps the RAM free for every keymap.
CFLAGS += -fno-tree-switch-conversion
