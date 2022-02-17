# Copyright 2017 Fred Sundvik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

QUANTUM_SRC += \
    $(QUANTUM_DIR)/quantum.c \
    $(QUANTUM_DIR)/send_string.c \
    $(QUANTUM_DIR)/bitwise.c \
    $(QUANTUM_DIR)/led.c \
    $(QUANTUM_DIR)/action.c \
    $(QUANTUM_DIR)/action_layer.c \
    $(QUANTUM_DIR)/action_macro.c \
    $(QUANTUM_DIR)/action_tapping.c \
    $(QUANTUM_DIR)/action_util.c \
    $(QUANTUM_DIR)/eeconfig.c \
    $(QUANTUM_DIR)/keyboard.c \
    $(QUANTUM_DIR)/keymap_common.c \
    $(QUANTUM_DIR)/keycode_config.c \
    $(QUANTUM_DIR)/sync_timer.c \
    $(QUANTUM_DIR)/logging/debug.c \
    $(QUANTUM_DIR)/logging/sendchar.c \

VPATH += $(QUANTUM_DIR)/logging
# Fall back to lib/printf if there is no platform provided print
ifeq ("$(wildcard $(PLATFORM_PATH)/$(PLATFORM_KEY)/printf.mk)","")
    include $(QUANTUM_PATH)/logging/print.mk
else
    include $(PLATFORM_PATH)/$(PLATFORM_KEY)/printf.mk
endif

ifeq ($(strip $(DEBUG_MATRIX_SCAN_RATE_ENABLE)), yes)
    OPT_DEFS += -DDEBUG_MATRIX_SCAN_RATE
    CONSOLE_ENABLE = yes
else ifeq ($(strip $(DEBUG_MATRIX_SCAN_RATE_ENABLE)), api)
    OPT_DEFS += -DDEBUG_MATRIX_SCAN_RATE
endif

AUDIO_ENABLE ?= no
ifeq ($(strip $(AUDIO_ENABLE)), yes)
    ifeq ($(PLATFORM),CHIBIOS)
        AUDIO_DRIVER ?= dac_basic
        ifeq ($(strip $(AUDIO_DRIVER)), dac_basic)
            OPT_DEFS += -DAUDIO_DRIVER_DAC
        else ifeq ($(strip $(AUDIO_DRIVER)), dac_additive)
            OPT_DEFS += -DAUDIO_DRIVER_DAC
        ## stm32f2 and above have a usable DAC unit, f1 do not, and need to use pwm instead
        else ifeq ($(strip $(AUDIO_DRIVER)), pwm_software)
            OPT_DEFS += -DAUDIO_DRIVER_PWM
        else ifeq ($(strip $(AUDIO_DRIVER)), pwm_hardware)
            OPT_DEFS += -DAUDIO_DRIVER_PWM
        endif
    else
        # fallback for all other platforms is pwm
        AUDIO_DRIVER ?= pwm_hardware
        OPT_DEFS += -DAUDIO_DRIVER_PWM
    endif
    OPT_DEFS += -DAUDIO_ENABLE
    MUSIC_ENABLE = yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_audio.c
    SRC += $(QUANTUM_DIR)/process_keycode/process_clicky.c
    SRC += $(QUANTUM_DIR)/audio/audio.c ## common audio code, hardware agnostic
    SRC += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/audio_$(strip $(AUDIO_DRIVER)).c
    SRC += $(QUANTUM_DIR)/audio/voices.c
    SRC += $(QUANTUM_DIR)/audio/luts.c
endif

ifeq ($(strip $(SEQUENCER_ENABLE)), yes)
    OPT_DEFS += -DSEQUENCER_ENABLE
    MUSIC_ENABLE = yes
    SRC += $(QUANTUM_DIR)/sequencer/sequencer.c
    SRC += $(QUANTUM_DIR)/process_keycode/process_sequencer.c
endif

ifeq ($(strip $(MIDI_ENABLE)), yes)
    OPT_DEFS += -DMIDI_ENABLE
    MUSIC_ENABLE = yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_midi.c
endif

MUSIC_ENABLE ?= no
ifeq ($(MUSIC_ENABLE), yes)
    SRC += $(QUANTUM_DIR)/process_keycode/process_music.c
endif

ifeq ($(strip $(STENO_ENABLE)), yes)
    OPT_DEFS += -DSTENO_ENABLE
    VIRTSER_ENABLE ?= yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_steno.c
endif

ifeq ($(strip $(VIRTSER_ENABLE)), yes)
    OPT_DEFS += -DVIRTSER_ENABLE
endif

ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
    OPT_DEFS += -DMOUSEKEY_ENABLE
    MOUSE_ENABLE := yes
    SRC += $(QUANTUM_DIR)/mousekey.c
endif

VALID_POINTING_DEVICE_DRIVER_TYPES := adns5050 adns9800 analog_joystick cirque_pinnacle_i2c cirque_pinnacle_spi pmw3360 pimoroni_trackball custom
POINTING_DEVICE_DRIVER ?= custom
ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
    ifeq ($(filter $(POINTING_DEVICE_DRIVER),$(VALID_POINTING_DEVICE_DRIVER_TYPES)),)
        $(error POINTING_DEVICE_DRIVER="$(POINTING_DEVICE_DRIVER)" is not a valid pointing device type)
    else
        OPT_DEFS += -DPOINTING_DEVICE_ENABLE
        MOUSE_ENABLE := yes
        SRC += $(QUANTUM_DIR)/pointing_device.c
        SRC += $(QUANTUM_DIR)/pointing_device_drivers.c
        ifneq ($(strip $(POINTING_DEVICE_DRIVER)), custom)
            SRC += drivers/sensors/$(strip $(POINTING_DEVICE_DRIVER)).c
            OPT_DEFS += -DPOINTING_DEVICE_DRIVER_$(strip $(shell echo $(POINTING_DEVICE_DRIVER) | tr '[:lower:]' '[:upper:]'))
        endif
        OPT_DEFS += -DPOINTING_DEVICE_DRIVER_$(strip $(POINTING_DEVICE_DRIVER))
        ifeq ($(strip $(POINTING_DEVICE_DRIVER)), adns9800)
            OPT_DEFS += -DSTM32_SPI -DHAL_USE_SPI=TRUE
            QUANTUM_LIB_SRC += spi_master.c
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), analog_joystick)
            OPT_DEFS += -DSTM32_ADC -DHAL_USE_ADC=TRUE
            LIB_SRC += analog.c
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), cirque_pinnacle_i2c)
            OPT_DEFS += -DSTM32_I2C -DHAL_USE_I2C=TRUE
            SRC += drivers/sensors/cirque_pinnacle.c
            QUANTUM_LIB_SRC += i2c_master.c
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), cirque_pinnacle_spi)
            OPT_DEFS += -DSTM32_SPI -DHAL_USE_SPI=TRUE
            SRC += drivers/sensors/cirque_pinnacle.c
            QUANTUM_LIB_SRC += spi_master.c
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), pimoroni_trackball)
            OPT_DEFS += -DSTM32_SPI -DHAL_USE_I2C=TRUE
            QUANTUM_LIB_SRC += i2c_master.c
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), pmw3360)
            OPT_DEFS += -DSTM32_SPI -DHAL_USE_SPI=TRUE
            QUANTUM_LIB_SRC += spi_master.c
        endif
    endif
endif

VALID_EEPROM_DRIVER_TYPES := vendor custom transient i2c spi
EEPROM_DRIVER ?= vendor
ifeq ($(filter $(EEPROM_DRIVER),$(VALID_EEPROM_DRIVER_TYPES)),)
  $(error EEPROM_DRIVER="$(EEPROM_DRIVER)" is not a valid EEPROM driver)
else
  OPT_DEFS += -DEEPROM_ENABLE
  ifeq ($(strip $(EEPROM_DRIVER)), custom)
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_CUSTOM
    COMMON_VPATH += $(DRIVER_PATH)/eeprom
    SRC += eeprom_driver.c
  else ifeq ($(strip $(EEPROM_DRIVER)), i2c)
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_I2C
    COMMON_VPATH += $(DRIVER_PATH)/eeprom
    QUANTUM_LIB_SRC += i2c_master.c
    SRC += eeprom_driver.c eeprom_i2c.c
  else ifeq ($(strip $(EEPROM_DRIVER)), spi)
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_SPI
    COMMON_VPATH += $(DRIVER_PATH)/eeprom
    QUANTUM_LIB_SRC += spi_master.c
    SRC += eeprom_driver.c eeprom_spi.c
  else ifeq ($(strip $(EEPROM_DRIVER)), transient)
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_TRANSIENT
    COMMON_VPATH += $(DRIVER_PATH)/eeprom
    SRC += eeprom_driver.c eeprom_transient.c
  else ifeq ($(strip $(EEPROM_DRIVER)), vendor)
    OPT_DEFS += -DEEPROM_VENDOR
    ifeq ($(PLATFORM),AVR)
      # Automatically provided by avr-libc, nothing required
    else ifeq ($(PLATFORM),CHIBIOS)
      ifneq ($(filter STM32F3xx_% STM32F1xx_% %_STM32F401xC %_STM32F401xE %_STM32F405xG %_STM32F411xE %_STM32F072xB %_STM32F042x6 %_GD32VF103xB %_GD32VF103x8, $(MCU_SERIES)_$(MCU_LDSCRIPT)),)
        OPT_DEFS += -DEEPROM_DRIVER
        COMMON_VPATH += $(DRIVER_PATH)/eeprom
        SRC += eeprom_driver.c
        SRC += $(PLATFORM_COMMON_DIR)/eeprom_stm32.c
        SRC += $(PLATFORM_COMMON_DIR)/flash_stm32.c
      else ifneq ($(filter $(MCU_SERIES),STM32L0xx STM32L1xx),)
        OPT_DEFS += -DEEPROM_DRIVER
        COMMON_VPATH += $(DRIVER_PATH)/eeprom
        COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/eeprom
        SRC += eeprom_driver.c
        SRC += eeprom_stm32_L0_L1.c
      else
        # This will effectively work the same as "transient" if not supported by the chip
        SRC += $(PLATFORM_COMMON_DIR)/eeprom_teensy.c
      endif
    else ifeq ($(PLATFORM),ARM_ATSAM)
      SRC += $(PLATFORM_COMMON_DIR)/eeprom.c
    else ifeq ($(PLATFORM),TEST)
      SRC += $(PLATFORM_COMMON_DIR)/eeprom.c
    endif
  endif
endif

RGBLIGHT_ENABLE ?= no
VALID_RGBLIGHT_TYPES := WS2812 APA102 custom

ifeq ($(strip $(RGBLIGHT_CUSTOM_DRIVER)), yes)
    RGBLIGHT_DRIVER ?= custom
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    RGBLIGHT_DRIVER ?= WS2812

    ifeq ($(filter $(RGBLIGHT_DRIVER),$(VALID_RGBLIGHT_TYPES)),)
        $(error RGBLIGHT_DRIVER="$(RGBLIGHT_DRIVER)" is not a valid RGB type)
    else
        COMMON_VPATH += $(QUANTUM_DIR)/rgblight
        POST_CONFIG_H += $(QUANTUM_DIR)/rgblight/rgblight_post_config.h
        OPT_DEFS += -DRGBLIGHT_ENABLE
        SRC += $(QUANTUM_DIR)/color.c
        SRC += $(QUANTUM_DIR)/rgblight/rgblight.c
        CIE1931_CURVE := yes
        RGB_KEYCODES_ENABLE := yes
    endif

    ifeq ($(strip $(RGBLIGHT_DRIVER)), WS2812)
        WS2812_DRIVER_REQUIRED := yes
    endif

    ifeq ($(strip $(RGBLIGHT_DRIVER)), APA102)
        APA102_DRIVER_REQUIRED := yes
    endif

    ifeq ($(strip $(RGBLIGHT_DRIVER)), custom)
        OPT_DEFS += -DRGBLIGHT_CUSTOM_DRIVER
    endif
endif

LED_MATRIX_ENABLE ?= no
VALID_LED_MATRIX_TYPES := IS31FL3731 custom
# TODO: IS31FL3733 IS31FL3737 IS31FL3741

ifeq ($(strip $(LED_MATRIX_ENABLE)), yes)
    ifeq ($(filter $(LED_MATRIX_DRIVER),$(VALID_LED_MATRIX_TYPES)),)
        $(error "$(LED_MATRIX_DRIVER)" is not a valid matrix type)
    endif
    OPT_DEFS += -DLED_MATRIX_ENABLE
ifneq (,$(filter $(MCU), atmega16u2 atmega32u2 at90usb162))
    # ATmegaxxU2 does not have hardware MUL instruction - lib8tion must be told to use software multiplication routines
    OPT_DEFS += -DLIB8_ATTINY
endif
    COMMON_VPATH += $(QUANTUM_DIR)/led_matrix
    COMMON_VPATH += $(QUANTUM_DIR)/led_matrix/animations
    COMMON_VPATH += $(QUANTUM_DIR)/led_matrix/animations/runners
    SRC += $(QUANTUM_DIR)/process_keycode/process_backlight.c
    SRC += $(QUANTUM_DIR)/led_matrix/led_matrix.c
    SRC += $(QUANTUM_DIR)/led_matrix/led_matrix_drivers.c
    SRC += $(LIB_PATH)/lib8tion/lib8tion.c
    CIE1931_CURVE := yes

    ifeq ($(strip $(LED_MATRIX_DRIVER)), IS31FL3731)
        OPT_DEFS += -DIS31FL3731 -DSTM32_I2C -DHAL_USE_I2C=TRUE
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3731-simple.c
        QUANTUM_LIB_SRC += i2c_master.c
    endif
endif

RGB_MATRIX_ENABLE ?= no
VALID_RGB_MATRIX_TYPES := AW20216 IS31FL3731 IS31FL3733 IS31FL3737 IS31FL3741 CKLED2001 WS2812 custom

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    ifeq ($(filter $(RGB_MATRIX_DRIVER),$(VALID_RGB_MATRIX_TYPES)),)
        $(error "$(RGB_MATRIX_DRIVER)" is not a valid matrix type)
    endif
    OPT_DEFS += -DRGB_MATRIX_ENABLE
ifneq (,$(filter $(MCU), atmega16u2 atmega32u2 at90usb162))
    # ATmegaxxU2 does not have hardware MUL instruction - lib8tion must be told to use software multiplication routines
    OPT_DEFS += -DLIB8_ATTINY
endif
    COMMON_VPATH += $(QUANTUM_DIR)/rgb_matrix
    COMMON_VPATH += $(QUANTUM_DIR)/rgb_matrix/animations
    COMMON_VPATH += $(QUANTUM_DIR)/rgb_matrix/animations/runners
    SRC += $(QUANTUM_DIR)/color.c
    SRC += $(QUANTUM_DIR)/rgb_matrix/rgb_matrix.c
    SRC += $(QUANTUM_DIR)/rgb_matrix/rgb_matrix_drivers.c
    SRC += $(LIB_PATH)/lib8tion/lib8tion.c
    CIE1931_CURVE := yes
    RGB_KEYCODES_ENABLE := yes

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), AW20216)
        OPT_DEFS += -DAW20216 -DSTM32_SPI -DHAL_USE_SPI=TRUE
        COMMON_VPATH += $(DRIVER_PATH)/led
        SRC += aw20216.c
        QUANTUM_LIB_SRC += spi_master.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), IS31FL3731)
        OPT_DEFS += -DIS31FL3731 -DSTM32_I2C -DHAL_USE_I2C=TRUE
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3731.c
        QUANTUM_LIB_SRC += i2c_master.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), IS31FL3733)
        OPT_DEFS += -DIS31FL3733 -DSTM32_I2C -DHAL_USE_I2C=TRUE
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3733.c
        QUANTUM_LIB_SRC += i2c_master.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), IS31FL3737)
        OPT_DEFS += -DIS31FL3737 -DSTM32_I2C -DHAL_USE_I2C=TRUE
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3737.c
        QUANTUM_LIB_SRC += i2c_master.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), IS31FL3741)
        OPT_DEFS += -DIS31FL3741 -DSTM32_I2C -DHAL_USE_I2C=TRUE
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3741.c
        QUANTUM_LIB_SRC += i2c_master.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), CKLED2001)
        OPT_DEFS += -DCKLED2001 -DSTM32_I2C -DHAL_USE_I2C=TRUE
        COMMON_VPATH += $(DRIVER_PATH)/led
        SRC += ckled2001.c
        QUANTUM_LIB_SRC += i2c_master.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), WS2812)
        OPT_DEFS += -DWS2812
        WS2812_DRIVER_REQUIRED := yes
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), APA102)
        OPT_DEFS += -DAPA102
        APA102_DRIVER_REQUIRED := yes
    endif

    ifeq ($(strip $(RGB_MATRIX_CUSTOM_KB)), yes)
        OPT_DEFS += -DRGB_MATRIX_CUSTOM_KB
    endif

    ifeq ($(strip $(RGB_MATRIX_CUSTOM_USER)), yes)
        OPT_DEFS += -DRGB_MATRIX_CUSTOM_USER
    endif
endif

ifeq ($(strip $(RGB_KEYCODES_ENABLE)), yes)
    SRC += $(QUANTUM_DIR)/process_keycode/process_rgb.c
endif

ifeq ($(strip $(PRINTING_ENABLE)), yes)
    OPT_DEFS += -DPRINTING_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_printer.c
    SRC += $(TMK_DIR)/protocol/serial_uart.c
endif

VARIABLE_TRACE ?= no
ifneq ($(strip $(VARIABLE_TRACE)),no)
    SRC += $(QUANTUM_DIR)/variable_trace.c
    OPT_DEFS += -DNUM_TRACED_VARIABLES=$(strip $(VARIABLE_TRACE))
    ifneq ($(strip $(MAX_VARIABLE_TRACE_SIZE)),)
        OPT_DEFS += -DMAX_VARIABLE_TRACE_SIZE=$(strip $(MAX_VARIABLE_TRACE_SIZE))
    endif
endif

ifeq ($(strip $(SLEEP_LED_ENABLE)), yes)
    SRC += $(PLATFORM_COMMON_DIR)/sleep_led.c
    OPT_DEFS += -DSLEEP_LED_ENABLE

    NO_SUSPEND_POWER_DOWN := yes
endif

VALID_BACKLIGHT_TYPES := pwm timer software custom

BACKLIGHT_ENABLE ?= no
ifeq ($(strip $(CONVERT_TO_PROTON_C)), yes)
    BACKLIGHT_DRIVER ?= software
else
    BACKLIGHT_DRIVER ?= pwm
endif
ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
    ifeq ($(filter $(BACKLIGHT_DRIVER),$(VALID_BACKLIGHT_TYPES)),)
        $(error BACKLIGHT_DRIVER="$(BACKLIGHT_DRIVER)" is not a valid backlight type)
    endif

    COMMON_VPATH += $(QUANTUM_DIR)/backlight
    SRC += $(QUANTUM_DIR)/backlight/backlight.c
    SRC += $(QUANTUM_DIR)/process_keycode/process_backlight.c
    OPT_DEFS += -DBACKLIGHT_ENABLE

    ifeq ($(strip $(BACKLIGHT_DRIVER)), custom)
        OPT_DEFS += -DBACKLIGHT_CUSTOM_DRIVER
    else
        SRC += $(QUANTUM_DIR)/backlight/backlight_driver_common.c
        ifeq ($(strip $(BACKLIGHT_DRIVER)), pwm)
            SRC += $(QUANTUM_DIR)/backlight/backlight_$(PLATFORM_KEY).c
        else
            SRC += $(QUANTUM_DIR)/backlight/backlight_$(strip $(BACKLIGHT_DRIVER)).c
        endif
    endif
endif

VALID_WS2812_DRIVER_TYPES := bitbang pwm spi i2c

WS2812_DRIVER ?= bitbang
ifeq ($(strip $(WS2812_DRIVER_REQUIRED)), yes)
    ifeq ($(filter $(WS2812_DRIVER),$(VALID_WS2812_DRIVER_TYPES)),)
        $(error WS2812_DRIVER="$(WS2812_DRIVER)" is not a valid WS2812 driver)
    endif

    OPT_DEFS += -DWS2812_DRIVER_$(strip $(shell echo $(WS2812_DRIVER) | tr '[:lower:]' '[:upper:]'))

    ifeq ($(strip $(WS2812_DRIVER)), bitbang)
        SRC += ws2812.c
    else
        SRC += ws2812_$(strip $(WS2812_DRIVER)).c

        ifeq ($(strip $(PLATFORM)), CHIBIOS)
            ifeq ($(strip $(WS2812_DRIVER)), pwm)
                OPT_DEFS += -DSTM32_DMA_REQUIRED=TRUE
            endif
        endif
    endif

    # add extra deps
    ifeq ($(strip $(WS2812_DRIVER)), i2c)
        QUANTUM_LIB_SRC += i2c_master.c
    endif
endif

ifeq ($(strip $(APA102_DRIVER_REQUIRED)), yes)
    COMMON_VPATH += $(DRIVER_PATH)/led
    SRC += apa102.c
endif

ifeq ($(strip $(CIE1931_CURVE)), yes)
    OPT_DEFS += -DUSE_CIE1931_CURVE
    LED_TABLES := yes
endif

ifeq ($(strip $(LED_TABLES)), yes)
    SRC += $(QUANTUM_DIR)/led_tables.c
endif

ifeq ($(strip $(TERMINAL_ENABLE)), yes)
    SRC += $(QUANTUM_DIR)/process_keycode/process_terminal.c
    OPT_DEFS += -DTERMINAL_ENABLE
    OPT_DEFS += -DUSER_PRINT
endif

ifeq ($(strip $(VIA_ENABLE)), yes)
    DYNAMIC_KEYMAP_ENABLE := yes
    RAW_ENABLE := yes
    BOOTMAGIC_ENABLE := yes
    SRC += $(QUANTUM_DIR)/via.c
    OPT_DEFS += -DVIA_ENABLE
endif

VALID_MAGIC_TYPES := yes
BOOTMAGIC_ENABLE ?= no
ifneq ($(strip $(BOOTMAGIC_ENABLE)), no)
  ifeq ($(filter $(BOOTMAGIC_ENABLE),$(VALID_MAGIC_TYPES)),)
    $(error BOOTMAGIC_ENABLE="$(BOOTMAGIC_ENABLE)" is not a valid type of magic)
  endif
  ifneq ($(strip $(BOOTMAGIC_ENABLE)), no)
      OPT_DEFS += -DBOOTMAGIC_LITE
      QUANTUM_SRC += $(QUANTUM_DIR)/bootmagic/bootmagic_lite.c
  endif
endif
COMMON_VPATH += $(QUANTUM_DIR)/bootmagic
QUANTUM_SRC += $(QUANTUM_DIR)/bootmagic/magic.c

VALID_CUSTOM_MATRIX_TYPES:= yes lite no

CUSTOM_MATRIX ?= no

ifneq ($(strip $(CUSTOM_MATRIX)), yes)
    ifeq ($(filter $(CUSTOM_MATRIX),$(VALID_CUSTOM_MATRIX_TYPES)),)
        $(error CUSTOM_MATRIX="$(CUSTOM_MATRIX)" is not a valid custom matrix type)
    endif

    # Include common stuff for all non custom matrix users
    QUANTUM_SRC += $(QUANTUM_DIR)/matrix_common.c

    # if 'lite' then skip the actual matrix implementation
    ifneq ($(strip $(CUSTOM_MATRIX)), lite)
        # Include the standard or split matrix code if needed
        QUANTUM_SRC += $(QUANTUM_DIR)/matrix.c
    endif
endif

# Debounce Modules. Set DEBOUNCE_TYPE=custom if including one manually.
DEBOUNCE_TYPE ?= sym_defer_g
ifneq ($(strip $(DEBOUNCE_TYPE)), custom)
    QUANTUM_SRC += $(QUANTUM_DIR)/debounce/$(strip $(DEBOUNCE_TYPE)).c
endif

ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
    POST_CONFIG_H += $(QUANTUM_DIR)/split_common/post_config.h
    OPT_DEFS += -DSPLIT_KEYBOARD
    CRC_ENABLE := yes

    # Include files used by all split keyboards
    QUANTUM_SRC += $(QUANTUM_DIR)/split_common/split_util.c

    # Determine which (if any) transport files are required
    ifneq ($(strip $(SPLIT_TRANSPORT)), custom)
        QUANTUM_SRC += $(QUANTUM_DIR)/split_common/transport.c \
                       $(QUANTUM_DIR)/split_common/transactions.c

        OPT_DEFS += -DSPLIT_COMMON_TRANSACTIONS

        # Functions added via QUANTUM_LIB_SRC are only included in the final binary if they're called.
        # Unused functions are pruned away, which is why we can add multiple drivers here without bloat.
        ifeq ($(PLATFORM),AVR)
            ifneq ($(NO_I2C),yes)
                QUANTUM_LIB_SRC += i2c_master.c \
                                   i2c_slave.c
            endif
        endif

        SERIAL_DRIVER ?= bitbang
        OPT_DEFS += -DSERIAL_DRIVER_$(strip $(shell echo $(SERIAL_DRIVER) | tr '[:lower:]' '[:upper:]'))
        ifeq ($(strip $(SERIAL_DRIVER)), bitbang)
            QUANTUM_LIB_SRC += serial.c
        else
            QUANTUM_LIB_SRC += serial_$(strip $(SERIAL_DRIVER)).c
        endif
    endif
    COMMON_VPATH += $(QUANTUM_PATH)/split_common
endif

ifeq ($(strip $(CRC_ENABLE)), yes)
    OPT_DEFS += -DCRC_ENABLE
    SRC += crc.c
endif

ifeq ($(strip $(HAPTIC_ENABLE)),yes)
    COMMON_VPATH += $(DRIVER_PATH)/haptic

    ifneq ($(filter DRV2605L, $(HAPTIC_DRIVER)), )
        SRC += DRV2605L.c
        QUANTUM_LIB_SRC += i2c_master.c
        OPT_DEFS += -DDRV2605L
    endif

    ifneq ($(filter SOLENOID, $(HAPTIC_DRIVER)), )
        SRC += solenoid.c
        OPT_DEFS += -DSOLENOID_ENABLE
    endif
endif

ifeq ($(strip $(HD44780_ENABLE)), yes)
    SRC += platforms/avr/drivers/hd44780.c
    OPT_DEFS += -DHD44780_ENABLE
endif

VALID_OLED_DRIVER_TYPES := SSD1306 custom
OLED_DRIVER ?= SSD1306
ifeq ($(strip $(OLED_ENABLE)), yes)
    ifeq ($(filter $(OLED_DRIVER),$(VALID_OLED_DRIVER_TYPES)),)
        $(error OLED_DRIVER="$(OLED_DRIVER)" is not a valid OLED driver)
    else
        OPT_DEFS += -DOLED_ENABLE
        COMMON_VPATH += $(DRIVER_PATH)/oled

        OPT_DEFS += -DOLED_DRIVER_$(strip $(shell echo $(OLED_DRIVER) | tr '[:lower:]' '[:upper:]'))
        ifeq ($(strip $(OLED_DRIVER)), SSD1306)
            SRC += ssd1306_sh1106.c
            QUANTUM_LIB_SRC += i2c_master.c
        endif
    endif
endif

ifeq ($(strip $(ST7565_ENABLE)), yes)
    OPT_DEFS += -DST7565_ENABLE
    COMMON_VPATH += $(DRIVER_PATH)/oled # For glcdfont.h
    COMMON_VPATH += $(DRIVER_PATH)/lcd
    QUANTUM_LIB_SRC += spi_master.c
    SRC += st7565.c
endif

ifeq ($(strip $(UCIS_ENABLE)), yes)
    OPT_DEFS += -DUCIS_ENABLE
    UNICODE_COMMON := yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_ucis.c
endif

ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
    OPT_DEFS += -DUNICODEMAP_ENABLE
    UNICODE_COMMON := yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicodemap.c
endif

ifeq ($(strip $(UNICODE_ENABLE)), yes)
    OPT_DEFS += -DUNICODE_ENABLE
    UNICODE_COMMON := yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicode.c
endif

ifeq ($(strip $(UNICODE_COMMON)), yes)
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicode_common.c
endif

MAGIC_ENABLE ?= yes
ifeq ($(strip $(MAGIC_ENABLE)), yes)
    SRC += $(QUANTUM_DIR)/process_keycode/process_magic.c
    OPT_DEFS += -DMAGIC_KEYCODE_ENABLE
endif

ifeq ($(strip $(AUTO_SHIFT_ENABLE)), yes)
    SRC += $(QUANTUM_DIR)/process_keycode/process_auto_shift.c
    OPT_DEFS += -DAUTO_SHIFT_ENABLE
    ifeq ($(strip $(AUTO_SHIFT_MODIFIERS)), yes)
        OPT_DEFS += -DAUTO_SHIFT_MODIFIERS
    endif
endif

ifeq ($(strip $(PS2_MOUSE_ENABLE)), yes)
    PS2_ENABLE := yes
    SRC += ps2_mouse.c
    OPT_DEFS += -DPS2_MOUSE_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifeq ($(strip $(PS2_USE_BUSYWAIT)), yes)
    PS2_ENABLE := yes
    SRC += ps2_busywait.c
    SRC += ps2_io_avr.c
    OPT_DEFS += -DPS2_USE_BUSYWAIT
endif

ifeq ($(strip $(PS2_USE_INT)), yes)
    PS2_ENABLE := yes
    SRC += ps2_interrupt.c
    SRC += ps2_io.c
    OPT_DEFS += -DPS2_USE_INT
endif

ifeq ($(strip $(PS2_USE_USART)), yes)
    PS2_ENABLE := yes
    SRC += ps2_usart.c
    SRC += ps2_io.c
    OPT_DEFS += -DPS2_USE_USART
endif

ifeq ($(strip $(PS2_ENABLE)), yes)
    COMMON_VPATH += $(DRIVER_PATH)/ps2
    COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/ps2
    OPT_DEFS += -DPS2_ENABLE
endif

JOYSTICK_ENABLE ?= no
VALID_JOYSTICK_TYPES := analog digital
JOYSTICK_DRIVER ?= analog
ifeq ($(strip $(JOYSTICK_ENABLE)), yes)
    ifeq ($(filter $(JOYSTICK_DRIVER),$(VALID_JOYSTICK_TYPES)),)
        $(error "$(JOYSTICK_DRIVER)" is not a valid joystick driver)
    endif
    OPT_DEFS += -DJOYSTICK_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_joystick.c
    SRC += $(QUANTUM_DIR)/joystick.c

    ifeq ($(strip $(JOYSTICK_DRIVER)), analog)
        OPT_DEFS += -DANALOG_JOYSTICK_ENABLE
        SRC += analog.c
    endif
    ifeq ($(strip $(JOYSTICK_DRIVER)), digital)
        OPT_DEFS += -DDIGITAL_JOYSTICK_ENABLE
    endif
endif

USBPD_ENABLE ?= no
VALID_USBPD_DRIVER_TYPES = custom vendor
USBPD_DRIVER ?= vendor
ifeq ($(strip $(USBPD_ENABLE)), yes)
    ifeq ($(filter $(strip $(USBPD_DRIVER)),$(VALID_USBPD_DRIVER_TYPES)),)
        $(error USBPD_DRIVER="$(USBPD_DRIVER)" is not a valid USBPD driver)
    else
        OPT_DEFS += -DUSBPD_ENABLE
        ifeq ($(strip $(USBPD_DRIVER)), vendor)
            # Vendor-specific implementations
            OPT_DEFS += -DUSBPD_VENDOR
            ifeq ($(strip $(MCU_SERIES)), STM32G4xx)
                OPT_DEFS += -DUSBPD_STM32G4
                SRC += usbpd_stm32g4.c
            else
                $(error There is no vendor-provided USBPD driver available)
            endif
        else ifeq ($(strip $(USBPD_DRIVER)), custom)
            OPT_DEFS += -DUSBPD_CUSTOM
            # Board designers can add their own driver to $(SRC)
        endif
    endif
endif

BLUETOOTH_ENABLE ?= no
VALID_BLUETOOTH_DRIVER_TYPES := AdafruitBLE RN42 custom
ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
    ifeq ($(filter $(strip $(BLUETOOTH_DRIVER)),$(VALID_BLUETOOTH_DRIVER_TYPES)),)
        $(error "$(BLUETOOTH_DRIVER)" is not a valid Bluetooth driver type)
    endif
    OPT_DEFS += -DBLUETOOTH_ENABLE
    NO_USB_STARTUP_CHECK := yes
    COMMON_VPATH += $(DRIVER_PATH)/bluetooth
    SRC += outputselect.c

    ifeq ($(strip $(BLUETOOTH_DRIVER)), AdafruitBLE)
        OPT_DEFS += -DMODULE_ADAFRUIT_BLE
        SRC += analog.c
        SRC += $(DRIVER_PATH)/bluetooth/adafruit_ble.cpp
        QUANTUM_LIB_SRC += spi_master.c
    endif

    ifeq ($(strip $(BLUETOOTH_DRIVER)), RN42)
        OPT_DEFS += -DMODULE_RN42
        SRC += $(TMK_DIR)/protocol/serial_uart.c
    endif
endif
