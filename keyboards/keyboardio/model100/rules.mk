CUSTOM_MATRIX = lite
I2C_DRIVER_REQUIRED = yes
SRC += leds.c \
	   matrix.c

# We deliberately do NOT set `bootloader: stm32duino` in keyboard.json. That
# would pull in platforms/chibios/bootloader.mk's stm32duino block, which
# hard-assigns (with `=`, not `?=`) the Maple defaults
# `DFU_ARGS = -d 1EAF:0003 -a 2 -R` / `DFU_SUFFIX_ARGS = -v 1EAF -p 0003`
# *after* this file is read, clobbering any override we set here. Instead we set
# the same flags the stm32duino block would have (board is declared in
# keyboard.json) and supply our own DFU identifiers. Same approach as
# keyboards/handwired/onekey/bluepill_f103c6.
OPT_DEFS += -DBOOTLOADER_STM32DUINO
BOOTLOADER_TYPE = stm32duino
# Because we don't set BOOTLOADER=stm32duino, the ld-script auto-selection in
# platforms/chibios/platform.mk (which appends `_$(BOOTLOADER)`) won't find the
# offset script, and we'd silently fall back to plain STM32F103x8.ld linking at
# 0x08000000 — the firmware then flashes but never runs, because DAPBoot hands
# control to 0x08002000. Name the stm32duino offset script explicitly so the
# app vector table lands at 0x08002000 (matches keyboards/mlego/m65/rev2).
MCU_LDSCRIPT = STM32F103x8_stm32duino

# The Model 100 ships Keyboardio's DAPBoot DFU bootloader, which enumerates as
# 3496:0005 rather than the Maple default 1EAF:0003. DAPBoot is a plain-DFU
# (non-DfuSe) bootloader that writes to its own fixed app base (0x08002000) via
# alt setting 0, so we must NOT pass a DfuSe `-s <addr>:leave` specifier — some
# dfu-util builds error out parsing it. Just select the device + alt 0 and reset.
DFU_ARGS = -d 3496:0005 -a 0 -R
DFU_SUFFIX_ARGS = -v 3496 -p 0005
