# Configure for 128K flash
MCU_LDSCRIPT = STM32F103xB

# Extra include
SRC += keycode_lookup.c

RAW_ENABLE = yes            # Enables HID RAW communication between the board and the PC
