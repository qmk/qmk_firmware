# Build Options
#   change yes to no to disable
#
MCU = STM32F103

# BOOTLOADER = custom
OPT_DEFS = -DBOOTLOADER_STM32DUINO
MCU_LDSCRIPT = STM32F103xC_stm32duino_bootloader
BOARD = STM32_F103_STM32DUINO
BOOTLOADER_TYPE = stm32duino
DFU_ARGS = -d 1EAF:0003 -a 2 -R
DFU_SUFFIX_ARGS = -v 1EAF -p 0003

# BOOTMAGIC_ENABLE = yes
RGB_MATRIX_ENABLE = yes

# Toggle switch
DIP_SWITCH_ENABLE = yes

# Pointer Devices Customized as the keyboard has multiple pointer sensors.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom

# Analog joystick
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

# Encoder
ENCODER_ENABLE = yes

# Audio and System Control
MIDI_ENABLE = yes

# Debugging
CONSOLE_ENABLE = no
NKRO_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes

# Set VIA to yes by default
VIA_ENABLE = yes

EXTRALDFLAGS = keyboards/$(KEYBOARD)/lib/user_lib.a
