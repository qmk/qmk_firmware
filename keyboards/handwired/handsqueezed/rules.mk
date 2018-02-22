# MCU name
MCU = atmega32u4

# Processor frequency.
F_CPU = 8000000

#
# LUFA specific

# Target architecture
ARCH = AVR8

# Input clock frequency.
F_USB = $(F_CPU)

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Boot Section Size in *bytes*
OPT_DEFS += -DBOOTLOADER_SIZE=4096

# Build Options
BOOTMAGIC_ENABLE ?= no
MOUSEKEY_ENABLE ?= yes
EXTRAKEY_ENABLE ?= yes
CONSOLE_ENABLE ?= yes
COMMAND_ENABLE ?= yes
SLEEP_LED_ENABLE ?= no
NKRO_ENABLE ?= no
BACKLIGHT_ENABLE ?= no
MIDI_ENABLE ?= no
UNICODE_ENABLE ?= no
BLUETOOTH_ENABLE ?= no
AUDIO_ENABLE ?= no
BLUETOOTH = AdafruitBLE

# Layouts
LAYOUTS = ortho_4x12
