MCU = nRF52840
BOOTLOADER = adafruit-nrfutil

MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = no       # Audio control and System control(+450)
CONSOLE_ENABLE = no        # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE = no

PROGRAM_CMD = adafruit-nrfutil dfu genpkg --dev-type 0x0052 --sd-req 0x00B6 --application .build/handwired_onekey_adafruit_itsybitsy_nrf52_default.hex $(BUILD_DIR)/$(TARGET).zip && adafruit-nrfutil --verbose dfu serial -p /dev/ttyACM1 -b 115200 --singlebank --package=$(BUILD_DIR)/$(TARGET).zip
