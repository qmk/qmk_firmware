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
    $(QUANTUM_DIR)/bitwise.c \
    $(QUANTUM_DIR)/led.c \
    $(QUANTUM_DIR)/action.c \
    $(QUANTUM_DIR)/action_layer.c \
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
    COMMON_VPATH += $(QUANTUM_PATH)/audio
    MUSIC_ENABLE = yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_audio.c
    SRC += $(QUANTUM_DIR)/process_keycode/process_clicky.c
    SRC += $(QUANTUM_DIR)/audio/audio.c ## common audio code, hardware agnostic
    SRC += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/audio_$(strip $(AUDIO_DRIVER)).c
    SRC += $(QUANTUM_DIR)/audio/voices.c
    SRC += $(QUANTUM_DIR)/audio/luts.c
endif

ifeq ($(strip $(SEQUENCER_ENABLE)), yes)
    MUSIC_ENABLE = yes
endif

ifeq ($(strip $(MIDI_ENABLE)), yes)
    OPT_DEFS += -DMIDI_ENABLE
    MUSIC_ENABLE = yes
    COMMON_VPATH += $(QUANTUM_PATH)/midi
    SRC += $(QUANTUM_DIR)/midi/midi.c
    SRC += $(QUANTUM_DIR)/midi/midi_device.c
    SRC += $(QUANTUM_DIR)/midi/qmk_midi.c
    SRC += $(QUANTUM_DIR)/midi/sysex_tools.c
    SRC += $(QUANTUM_DIR)/midi/bytequeue/bytequeue.c
    SRC += $(QUANTUM_DIR)/midi/bytequeue/interrupt_setting.c
    SRC += $(QUANTUM_DIR)/process_keycode/process_midi.c
endif

VALID_STENO_PROTOCOL_TYPES := geminipr txbolt all
STENO_PROTOCOL ?= all
ifeq ($(strip $(STENO_ENABLE)), yes)
    ifeq ($(filter $(STENO_PROTOCOL),$(VALID_STENO_PROTOCOL_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid STENO_PROTOCOL,STENO_PROTOCOL="$(STENO_PROTOCOL)" is not a valid stenography protocol)
    else
        OPT_DEFS += -DSTENO_ENABLE
        VIRTSER_ENABLE ?= yes

        ifeq ($(strip $(STENO_PROTOCOL)), geminipr)
            OPT_DEFS += -DSTENO_ENABLE_GEMINI
        endif
        ifeq ($(strip $(STENO_PROTOCOL)), txbolt)
            OPT_DEFS += -DSTENO_ENABLE_BOLT
        endif
        ifeq ($(strip $(STENO_PROTOCOL)), all)
            OPT_DEFS += -DSTENO_ENABLE_ALL
            OPT_DEFS += -DSTENO_ENABLE_GEMINI
            OPT_DEFS += -DSTENO_ENABLE_BOLT
        endif

        SRC += $(QUANTUM_DIR)/process_keycode/process_steno.c
    endif
endif

ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
    MOUSE_ENABLE := yes
endif

VALID_POINTING_DEVICE_DRIVER_TYPES := adns5050 adns9800 analog_joystick azoteq_iqs5xx cirque_pinnacle_i2c cirque_pinnacle_spi paw3204 pmw3320 pmw3360 pmw3389 pimoroni_trackball custom
ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
    ifeq ($(filter $(POINTING_DEVICE_DRIVER),$(VALID_POINTING_DEVICE_DRIVER_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid POINTING_DEVICE_DRIVER,POINTING_DEVICE_DRIVER="$(POINTING_DEVICE_DRIVER)" is not a valid pointing device type)
    else
        OPT_DEFS += -DPOINTING_DEVICE_ENABLE
        MOUSE_ENABLE := yes
        VPATH += $(QUANTUM_DIR)/pointing_device
        SRC += $(QUANTUM_DIR)/pointing_device/pointing_device.c
        SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_drivers.c
        SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_auto_mouse.c
        ifneq ($(strip $(POINTING_DEVICE_DRIVER)), custom)
            SRC += drivers/sensors/$(strip $(POINTING_DEVICE_DRIVER)).c
            OPT_DEFS += -DPOINTING_DEVICE_DRIVER_$(strip $(shell echo $(POINTING_DEVICE_DRIVER) | tr '[:lower:]' '[:upper:]'))
        endif
        OPT_DEFS += -DPOINTING_DEVICE_DRIVER_$(strip $(POINTING_DEVICE_DRIVER))
        ifeq ($(strip $(POINTING_DEVICE_DRIVER)), adns9800)
            SPI_DRIVER_REQUIRED = yes
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), analog_joystick)
            ANALOG_DRIVER_REQUIRED = yes
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), azoteq_iqs5xx)
            I2C_DRIVER_REQUIRED = yes
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), cirque_pinnacle_i2c)
            I2C_DRIVER_REQUIRED = yes
            SRC += drivers/sensors/cirque_pinnacle.c
            SRC += drivers/sensors/cirque_pinnacle_gestures.c
            SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_gestures.c
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), cirque_pinnacle_spi)
            SPI_DRIVER_REQUIRED = yes
            SRC += drivers/sensors/cirque_pinnacle.c
            SRC += drivers/sensors/cirque_pinnacle_gestures.c
            SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_gestures.c
        else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), pimoroni_trackball)
            I2C_DRIVER_REQUIRED = yes
        else ifneq ($(filter $(strip $(POINTING_DEVICE_DRIVER)),pmw3360 pmw3389),)
            SPI_DRIVER_REQUIRED = yes
            SRC += drivers/sensors/pmw33xx_common.c
        endif
    endif
endif

QUANTUM_PAINTER_ENABLE ?= no
ifeq ($(strip $(QUANTUM_PAINTER_ENABLE)), yes)
    include $(QUANTUM_DIR)/painter/rules.mk
endif

VALID_EEPROM_DRIVER_TYPES := vendor custom transient i2c spi wear_leveling legacy_stm32_flash
EEPROM_DRIVER ?= vendor
ifeq ($(filter $(EEPROM_DRIVER),$(VALID_EEPROM_DRIVER_TYPES)),)
  $(call CATASTROPHIC_ERROR,Invalid EEPROM_DRIVER,EEPROM_DRIVER="$(EEPROM_DRIVER)" is not a valid EEPROM driver)
else
  OPT_DEFS += -DEEPROM_ENABLE
  COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/eeprom
  COMMON_VPATH += $(DRIVER_PATH)/eeprom
  COMMON_VPATH += $(PLATFORM_COMMON_DIR)
  ifeq ($(strip $(EEPROM_DRIVER)), custom)
    # Custom EEPROM implementation -- only needs to implement init/erase/read_block/write_block
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_CUSTOM
    SRC += eeprom_driver.c
  else ifeq ($(strip $(EEPROM_DRIVER)), wear_leveling)
    # Wear-leveling EEPROM implementation
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_WEAR_LEVELING
    SRC += eeprom_driver.c eeprom_wear_leveling.c
  else ifeq ($(strip $(EEPROM_DRIVER)), i2c)
    # External I2C EEPROM implementation
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_I2C
    I2C_DRIVER_REQUIRED = yes
    SRC += eeprom_driver.c eeprom_i2c.c
  else ifeq ($(strip $(EEPROM_DRIVER)), spi)
    # External SPI EEPROM implementation
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_SPI
    SPI_DRIVER_REQUIRED = yes
    SRC += eeprom_driver.c eeprom_spi.c
  else ifeq ($(strip $(EEPROM_DRIVER)), legacy_stm32_flash)
    # STM32 Emulated EEPROM, backed by MCU flash (soon to be deprecated)
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_LEGACY_EMULATED_FLASH
    COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/flash
    COMMON_VPATH += $(DRIVER_PATH)/flash
    SRC += eeprom_driver.c eeprom_legacy_emulated_flash.c legacy_flash_ops.c
  else ifeq ($(strip $(EEPROM_DRIVER)), transient)
    # Transient EEPROM implementation -- no data storage but provides runtime area for it
    OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_TRANSIENT
    SRC += eeprom_driver.c eeprom_transient.c
  else ifeq ($(strip $(EEPROM_DRIVER)), vendor)
    # Vendor-implemented EEPROM
    OPT_DEFS += -DEEPROM_VENDOR
    ifeq ($(PLATFORM),AVR)
      # Automatically provided by avr-libc, nothing required
    else ifeq ($(PLATFORM),CHIBIOS)
      ifneq ($(filter %_STM32F072xB %_STM32F042x6, $(MCU_SERIES)_$(MCU_LDSCRIPT)),)
        # STM32 Emulated EEPROM, backed by MCU flash (soon to be deprecated)
        OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_LEGACY_EMULATED_FLASH
        COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/flash
        COMMON_VPATH += $(DRIVER_PATH)/flash
        SRC += eeprom_driver.c eeprom_legacy_emulated_flash.c legacy_flash_ops.c
      else ifneq ($(filter $(MCU_SERIES),STM32F1xx STM32F3xx STM32F4xx STM32L4xx STM32G4xx WB32F3G71xx WB32FQ95xx GD32VF103),)
        # Wear-leveling EEPROM implementation, backed by MCU flash
        OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_WEAR_LEVELING
        SRC += eeprom_driver.c eeprom_wear_leveling.c
        WEAR_LEVELING_DRIVER ?= embedded_flash
      else ifneq ($(filter $(MCU_SERIES),STM32L0xx STM32L1xx),)
        # True EEPROM on STM32L0xx, L1xx
        OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_STM32_L0_L1
        SRC += eeprom_driver.c eeprom_stm32_L0_L1.c
      else ifneq ($(filter $(MCU_SERIES),RP2040),)
        # Wear-leveling EEPROM implementation, backed by RP2040 flash
        OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_WEAR_LEVELING
        SRC += eeprom_driver.c eeprom_wear_leveling.c
        WEAR_LEVELING_DRIVER ?= rp2040_flash
      else ifneq ($(filter $(MCU_SERIES),KL2x K20x),)
        # Teensy EEPROM implementations
        OPT_DEFS += -DEEPROM_KINETIS_FLEXRAM
        SRC += eeprom_kinetis_flexram.c
      else
        # Fall back to transient, i.e. non-persistent
        OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_TRANSIENT
        SRC += eeprom_driver.c eeprom_transient.c
      endif
    else ifeq ($(PLATFORM),ARM_ATSAM)
      # arm_atsam EEPROM
      OPT_DEFS += -DEEPROM_SAMD
      SRC += eeprom_samd.c
    else ifeq ($(PLATFORM),TEST)
      # Test harness "EEPROM"
      OPT_DEFS += -DEEPROM_TEST_HARNESS
      SRC += eeprom.c
    endif
  endif
endif

VALID_WEAR_LEVELING_DRIVER_TYPES := custom embedded_flash spi_flash rp2040_flash legacy
WEAR_LEVELING_DRIVER ?= none
ifneq ($(strip $(WEAR_LEVELING_DRIVER)),none)
  ifeq ($(filter $(WEAR_LEVELING_DRIVER),$(VALID_WEAR_LEVELING_DRIVER_TYPES)),)
    $(call CATASTROPHIC_ERROR,Invalid WEAR_LEVELING_DRIVER,WEAR_LEVELING_DRIVER="$(WEAR_LEVELING_DRIVER)" is not a valid wear leveling driver)
  else
    FNV_ENABLE := yes
    OPT_DEFS += -DWEAR_LEVELING_ENABLE
    OPT_DEFS += -DWEAR_LEVELING_$(strip $(shell echo $(WEAR_LEVELING_DRIVER) | tr '[:lower:]' '[:upper:]'))
    COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/wear_leveling
    COMMON_VPATH += $(DRIVER_PATH)/wear_leveling
    COMMON_VPATH += $(QUANTUM_DIR)/wear_leveling
    SRC += wear_leveling.c
    ifeq ($(strip $(WEAR_LEVELING_DRIVER)), embedded_flash)
      OPT_DEFS += -DHAL_USE_EFL
      SRC += wear_leveling_efl.c
      POST_CONFIG_H += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/wear_leveling/wear_leveling_efl_config.h
    else ifeq ($(strip $(WEAR_LEVELING_DRIVER)), spi_flash)
      FLASH_DRIVER := spi
      SRC += wear_leveling_flash_spi.c
      POST_CONFIG_H += $(DRIVER_PATH)/wear_leveling/wear_leveling_flash_spi_config.h
    else ifeq ($(strip $(WEAR_LEVELING_DRIVER)), rp2040_flash)
      SRC += wear_leveling_rp2040_flash.c
      POST_CONFIG_H += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_PATH)/wear_leveling/wear_leveling_rp2040_flash_config.h
    else ifeq ($(strip $(WEAR_LEVELING_DRIVER)), legacy)
      COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/flash
      SRC += legacy_flash_ops.c wear_leveling_legacy.c
      POST_CONFIG_H += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/wear_leveling/wear_leveling_legacy_config.h
    endif
  endif
endif

VALID_FLASH_DRIVER_TYPES := spi
FLASH_DRIVER ?= none
ifneq ($(strip $(FLASH_DRIVER)), none)
    ifeq ($(filter $(FLASH_DRIVER),$(VALID_FLASH_DRIVER_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid FLASH_DRIVER,FLASH_DRIVER="$(FLASH_DRIVER)" is not a valid flash driver)
    else
        OPT_DEFS += -DFLASH_ENABLE
        ifeq ($(strip $(FLASH_DRIVER)),spi)
            SPI_DRIVER_REQUIRED = yes
            OPT_DEFS += -DFLASH_DRIVER -DFLASH_SPI
            COMMON_VPATH += $(DRIVER_PATH)/flash
            SRC += flash_spi.c
        endif
    endif
endif

RGBLIGHT_ENABLE ?= no
VALID_RGBLIGHT_TYPES := ws2812 apa102 custom

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    RGBLIGHT_DRIVER ?= ws2812

    ifeq ($(filter $(RGBLIGHT_DRIVER),$(VALID_RGBLIGHT_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid RGBLIGHT_DRIVER,RGBLIGHT_DRIVER="$(RGBLIGHT_DRIVER)" is not a valid RGB type)
    else
        COMMON_VPATH += $(QUANTUM_DIR)/rgblight
        POST_CONFIG_H += $(QUANTUM_DIR)/rgblight/rgblight_post_config.h
        OPT_DEFS += -DRGBLIGHT_ENABLE
        OPT_DEFS += -DRGBLIGHT_$(strip $(shell echo $(RGBLIGHT_DRIVER) | tr '[:lower:]' '[:upper:]'))
        SRC += $(QUANTUM_DIR)/color.c
        SRC += $(QUANTUM_DIR)/rgblight/rgblight.c
        SRC += $(QUANTUM_DIR)/rgblight/rgblight_drivers.c
        CIE1931_CURVE := yes
        RGB_KEYCODES_ENABLE := yes
    endif

    ifeq ($(strip $(RGBLIGHT_DRIVER)), ws2812)
        WS2812_DRIVER_REQUIRED := yes
    endif

    ifeq ($(strip $(RGBLIGHT_DRIVER)), apa102)
        APA102_DRIVER_REQUIRED := yes
    endif

    ifeq ($(strip $(VELOCIKEY_ENABLE)), yes)
        OPT_DEFS += -DVELOCIKEY_ENABLE
    endif
endif

# Deprecated driver names - do not use
ifeq ($(strip $(LED_MATRIX_DRIVER)), aw20216)
LED_MATRIX_DRIVER := aw20216s
endif
ifeq ($(strip $(LED_MATRIX_DRIVER)), ckled2001)
LED_MATRIX_DRIVER := snled27351
endif

LED_MATRIX_ENABLE ?= no
VALID_LED_MATRIX_TYPES := is31fl3218 is31fl3731 is31fl3733 is31fl3736 is31fl3737 is31fl3741 is31fl3742a is31fl3743a is31fl3745 is31fl3746a snled27351 custom

ifeq ($(strip $(LED_MATRIX_ENABLE)), yes)
    ifeq ($(filter $(LED_MATRIX_DRIVER),$(VALID_LED_MATRIX_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid LED_MATRIX_DRIVER,LED_MATRIX_DRIVER="$(LED_MATRIX_DRIVER)" is not a valid matrix type)
    endif
    OPT_DEFS += -DLED_MATRIX_ENABLE
    OPT_DEFS += -DLED_MATRIX_$(strip $(shell echo $(LED_MATRIX_DRIVER) | tr '[:lower:]' '[:upper:]'))

    COMMON_VPATH += $(QUANTUM_DIR)/led_matrix
    COMMON_VPATH += $(QUANTUM_DIR)/led_matrix/animations
    COMMON_VPATH += $(QUANTUM_DIR)/led_matrix/animations/runners
    POST_CONFIG_H += $(QUANTUM_DIR)/led_matrix/post_config.h
    SRC += $(QUANTUM_DIR)/process_keycode/process_backlight.c
    SRC += $(QUANTUM_DIR)/led_matrix/led_matrix.c
    SRC += $(QUANTUM_DIR)/led_matrix/led_matrix_drivers.c
    LIB8TION_ENABLE := yes
    CIE1931_CURVE := yes

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3218)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3218-simple.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3731)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3731-simple.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3733)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3733-simple.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3736)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3736-simple.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3737)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3737-simple.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3741)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3741-simple.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3742a)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3742a-simple.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3743a)
        OPT_DEFS += -DIS31FLCOMMON
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31flcommon.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3745)
        OPT_DEFS += -DIS31FLCOMMON
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31flcommon.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), is31fl3746a)
        OPT_DEFS += -DIS31FLCOMMON
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31flcommon.c
    endif

    ifeq ($(strip $(LED_MATRIX_DRIVER)), snled27351)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led
        SRC += snled27351-simple.c
    endif

endif

# Deprecated driver names - do not use
ifeq ($(strip $(RGB_MATRIX_DRIVER)), aw20216)
RGB_MATRIX_DRIVER := aw20216s
endif
ifeq ($(strip $(RGB_MATRIX_DRIVER)), ckled2001)
RGB_MATRIX_DRIVER := snled27351
endif

RGB_MATRIX_ENABLE ?= no

VALID_RGB_MATRIX_TYPES := aw20216s is31fl3218 is31fl3731 is31fl3733 is31fl3736 is31fl3737 is31fl3741 is31fl3742a is31fl3743a is31fl3745 is31fl3746a snled27351 ws2812 custom
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    ifeq ($(filter $(RGB_MATRIX_DRIVER),$(VALID_RGB_MATRIX_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid RGB_MATRIX_DRIVER,RGB_MATRIX_DRIVER="$(RGB_MATRIX_DRIVER)" is not a valid matrix type)
    endif
    OPT_DEFS += -DRGB_MATRIX_ENABLE
    OPT_DEFS += -DRGB_MATRIX_$(strip $(shell echo $(RGB_MATRIX_DRIVER) | tr '[:lower:]' '[:upper:]'))

    COMMON_VPATH += $(QUANTUM_DIR)/rgb_matrix
    COMMON_VPATH += $(QUANTUM_DIR)/rgb_matrix/animations
    COMMON_VPATH += $(QUANTUM_DIR)/rgb_matrix/animations/runners
    POST_CONFIG_H += $(QUANTUM_DIR)/rgb_matrix/post_config.h
    SRC += $(QUANTUM_DIR)/color.c
    SRC += $(QUANTUM_DIR)/rgb_matrix/rgb_matrix.c
    SRC += $(QUANTUM_DIR)/rgb_matrix/rgb_matrix_drivers.c
    LIB8TION_ENABLE := yes
    CIE1931_CURVE := yes
    RGB_KEYCODES_ENABLE := yes

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), aw20216s)
        SPI_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led
        SRC += aw20216s.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3218)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3218.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3731)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3731.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3733)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3733.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3736)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3736.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3737)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3737.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3741)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3741.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3742a)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31fl3742a.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3743a)
        OPT_DEFS += -DIS31FLCOMMON
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31flcommon.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3745)
        OPT_DEFS += -DIS31FLCOMMON
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31flcommon.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), is31fl3746a)
        OPT_DEFS += -DIS31FLCOMMON
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led/issi
        SRC += is31flcommon.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), snled27351)
        I2C_DRIVER_REQUIRED = yes
        COMMON_VPATH += $(DRIVER_PATH)/led
        SRC += snled27351.c
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), ws2812)
        WS2812_DRIVER_REQUIRED := yes
    endif

    ifeq ($(strip $(RGB_MATRIX_DRIVER)), apa102)
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
BACKLIGHT_DRIVER ?= pwm
ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
    ifeq ($(filter $(BACKLIGHT_DRIVER),$(VALID_BACKLIGHT_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid BACKLIGHT_DRIVER,BACKLIGHT_DRIVER="$(BACKLIGHT_DRIVER)" is not a valid backlight type)
    endif

    COMMON_VPATH += $(QUANTUM_DIR)/backlight
    COMMON_VPATH += $(DRIVER_PATH)/backlight
    SRC += $(QUANTUM_DIR)/backlight/backlight.c
    SRC += $(QUANTUM_DIR)/process_keycode/process_backlight.c
    OPT_DEFS += -DBACKLIGHT_ENABLE
    OPT_DEFS += -DBACKLIGHT_$(strip $(shell echo $(BACKLIGHT_DRIVER) | tr '[:lower:]' '[:upper:]'))

    ifneq ($(strip $(BACKLIGHT_DRIVER)), custom)
        SRC += $(QUANTUM_DIR)/backlight/backlight_driver_common.c

        ifeq ($(strip $(BACKLIGHT_DRIVER)), software)
            SRC += $(DRIVER_PATH)/backlight/backlight_software.c
        else
            SRC += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/backlight_$(strip $(BACKLIGHT_DRIVER)).c
        endif
    endif
endif

ifeq ($(strip $(CIE1931_CURVE)), yes)
    OPT_DEFS += -DUSE_CIE1931_CURVE
    LED_TABLES := yes
endif

ifeq ($(strip $(LED_TABLES)), yes)
    SRC += $(QUANTUM_DIR)/led_tables.c
endif

ifeq ($(strip $(VIA_ENABLE)), yes)
    DYNAMIC_KEYMAP_ENABLE := yes
    RAW_ENABLE := yes
    BOOTMAGIC_ENABLE := yes
    TRI_LAYER_ENABLE := yes
endif

VALID_MAGIC_TYPES := yes
BOOTMAGIC_ENABLE ?= no
ifneq ($(strip $(BOOTMAGIC_ENABLE)), no)
  ifeq ($(filter $(BOOTMAGIC_ENABLE),$(VALID_MAGIC_TYPES)),)
    $(call CATASTROPHIC_ERROR,Invalid BOOTMAGIC_ENABLE,BOOTMAGIC_ENABLE="$(BOOTMAGIC_ENABLE)" is not a valid type of magic)
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
        $(call CATASTROPHIC_ERROR,Invalid CUSTOM_MATRIX,CUSTOM_MATRIX="$(CUSTOM_MATRIX)" is not a valid custom matrix type)
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


VALID_SERIAL_DRIVER_TYPES := bitbang usart vendor

SERIAL_DRIVER ?= bitbang
ifeq ($(filter $(SERIAL_DRIVER),$(VALID_SERIAL_DRIVER_TYPES)),)
    $(call CATASTROPHIC_ERROR,Invalid SERIAL_DRIVER,SERIAL_DRIVER="$(SERIAL_DRIVER)" is not a valid SERIAL driver)
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

        OPT_DEFS += -DSERIAL_DRIVER_$(strip $(shell echo $(SERIAL_DRIVER) | tr '[:lower:]' '[:upper:]'))
        ifeq ($(strip $(SERIAL_DRIVER)), bitbang)
            QUANTUM_LIB_SRC += serial.c
        else
            QUANTUM_LIB_SRC += serial_protocol.c
            QUANTUM_LIB_SRC += serial_$(strip $(SERIAL_DRIVER)).c
        endif
    endif
    COMMON_VPATH += $(QUANTUM_PATH)/split_common
endif

ifeq ($(strip $(FNV_ENABLE)), yes)
    OPT_DEFS += -DFNV_ENABLE
    VPATH += $(LIB_PATH)/fnv
    SRC += qmk_fnv_type_validation.c hash_32a.c hash_64a.c
endif

ifeq ($(strip $(LIB8TION_ENABLE)), yes)
    ifneq (,$(filter $(MCU), atmega16u2 atmega32u2 at90usb162))
        # ATmegaxxU2 does not have hardware MUL instruction - lib8tion must be told to use software multiplication routines
        OPT_DEFS += -DLIB8_ATTINY
    endif
    SRC += $(LIB_PATH)/lib8tion/lib8tion.c
endif

VALID_HAPTIC_DRIVER_TYPES := drv2605l solenoid
ifeq ($(strip $(HAPTIC_ENABLE)),yes)
    ifeq ($(filter $(HAPTIC_DRIVER),$(VALID_HAPTIC_DRIVER_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid HAPTIC_DRIVER,HAPTIC_DRIVER="$(HAPTIC_DRIVER)" is not a valid Haptic driver)
    else
        OPT_DEFS += -DHAPTIC_$(strip $(shell echo $(HAPTIC_DRIVER) | tr '[:lower:]' '[:upper:]'))
        COMMON_VPATH += $(DRIVER_PATH)/haptic

        ifeq ($(strip $(HAPTIC_DRIVER)), drv2605l)
            I2C_DRIVER_REQUIRED = yes
            SRC += drv2605l.c
        endif

        ifeq ($(strip $(HAPTIC_DRIVER)), solenoid)
            SRC += solenoid.c
        endif
    endif
endif

ifeq ($(strip $(HD44780_ENABLE)), yes)
    OPT_DEFS += -DHD44780_ENABLE
    COMMON_VPATH += $(DRIVER_PATH)/lcd
    SRC += hd44780.c
endif

VALID_OLED_DRIVER_TYPES := custom ssd1306
OLED_DRIVER ?= ssd1306
VALID_OLED_TRANSPORT_TYPES := i2c spi custom
OLED_TRANSPORT ?= i2c
ifeq ($(strip $(OLED_ENABLE)), yes)
    ifeq ($(filter $(OLED_DRIVER),$(VALID_OLED_DRIVER_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid OLED_DRIVER,OLED_DRIVER="$(OLED_DRIVER)" is not a valid OLED driver)
    else
        ifeq ($(filter $(OLED_TRANSPORT),$(VALID_OLED_TRANSPORT_TYPES)),)
            $(call CATASTROPHIC_ERROR,Invalid OLED_TRANSPORT,OLED_TRANSPORT="$(OLED_TRANSPORT)" is not a valid OLED transport)
        else
            OPT_DEFS += -DOLED_ENABLE
            OPT_DEFS += -DOLED_$(strip $(shell echo $(OLED_DRIVER) | tr '[:lower:]' '[:upper:]'))
            COMMON_VPATH += $(DRIVER_PATH)/oled
            ifneq ($(strip $(OLED_DRIVER)), custom)
                SRC += oled_driver.c
            endif

            OPT_DEFS += -DOLED_TRANSPORT_$(strip $(shell echo $(OLED_TRANSPORT) | tr '[:lower:]' '[:upper:]'))
            ifeq ($(strip $(OLED_TRANSPORT)), i2c)
                I2C_DRIVER_REQUIRED = yes
            endif
            ifeq ($(strip $(OLED_TRANSPORT)), spi)
                SPI_DRIVER_REQUIRED = yes
            endif
        endif
    endif
endif

ifeq ($(strip $(ST7565_ENABLE)), yes)
    OPT_DEFS += -DST7565_ENABLE
    SPI_DRIVER_REQUIRED = yes
    COMMON_VPATH += $(DRIVER_PATH)/oled # For glcdfont.h
    COMMON_VPATH += $(DRIVER_PATH)/lcd
    SRC += st7565.c
endif

ifeq ($(strip $(UCIS_ENABLE)), yes)
    OPT_DEFS += -DUCIS_ENABLE
    UNICODE_COMMON := yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_ucis.c \
           $(QUANTUM_DIR)/unicode/ucis.c
endif

ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
    OPT_DEFS += -DUNICODEMAP_ENABLE
    UNICODE_COMMON := yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicodemap.c \
           $(QUANTUM_DIR)/unicode/unicodemap.c
endif

ifeq ($(strip $(UNICODE_ENABLE)), yes)
    OPT_DEFS += -DUNICODE_ENABLE
    UNICODE_COMMON := yes
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicode.c
endif

ifeq ($(strip $(UNICODE_COMMON)), yes)
    OPT_DEFS += -DUNICODE_COMMON_ENABLE
    COMMON_VPATH += $(QUANTUM_DIR)/unicode
    SRC += $(QUANTUM_DIR)/process_keycode/process_unicode_common.c \
           $(QUANTUM_DIR)/unicode/unicode.c \
           $(QUANTUM_DIR)/unicode/utf8.c
endif

ifeq ($(strip $(PS2_MOUSE_ENABLE)), yes)
    PS2_ENABLE := yes
    MOUSE_ENABLE := yes
    SRC += ps2_mouse.c
    OPT_DEFS += -DPS2_MOUSE_ENABLE
endif

VALID_PS2_DRIVER_TYPES := busywait interrupt usart vendor

PS2_DRIVER ?= busywait
ifeq ($(strip $(PS2_ENABLE)), yes)
    ifeq ($(filter $(PS2_DRIVER),$(VALID_PS2_DRIVER_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid PS2_DRIVER,PS2_DRIVER="$(PS2_DRIVER)" is not a valid PS/2 driver)
    endif

    OPT_DEFS += -DPS2_DRIVER_$(strip $(shell echo $(PS2_DRIVER) | tr '[:lower:]' '[:upper:]'))

    COMMON_VPATH += $(DRIVER_PATH)/ps2
    COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/ps2
    OPT_DEFS += -DPS2_ENABLE

    ifneq ($(strip $(PS2_DRIVER)), vendor)
        SRC += ps2_io.c
    endif

    SRC += ps2_$(strip $(PS2_DRIVER)).c
endif

JOYSTICK_ENABLE ?= no
VALID_JOYSTICK_TYPES := analog digital
JOYSTICK_DRIVER ?= analog
ifeq ($(strip $(JOYSTICK_ENABLE)), yes)
    ifeq ($(filter $(JOYSTICK_DRIVER),$(VALID_JOYSTICK_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid JOYSTICK_DRIVER,JOYSTICK_DRIVER="$(JOYSTICK_DRIVER)" is not a valid joystick driver)
    endif
    OPT_DEFS += -DJOYSTICK_ENABLE
    SRC += $(QUANTUM_DIR)/process_keycode/process_joystick.c
    SRC += $(QUANTUM_DIR)/joystick.c

    ifeq ($(strip $(JOYSTICK_DRIVER)), analog)
        ANALOG_DRIVER_REQUIRED = yes
        OPT_DEFS += -DANALOG_JOYSTICK_ENABLE
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
        $(call CATASTROPHIC_ERROR,Invalid USBPD_DRIVER,USBPD_DRIVER="$(USBPD_DRIVER)" is not a valid USBPD driver)
    else
        OPT_DEFS += -DUSBPD_ENABLE
        ifeq ($(strip $(USBPD_DRIVER)), vendor)
            # Vendor-specific implementations
            OPT_DEFS += -DUSBPD_VENDOR
            ifeq ($(strip $(MCU_SERIES)), STM32G4xx)
                OPT_DEFS += -DUSBPD_STM32G4
                SRC += usbpd_stm32g4.c
            else
                $(call CATASTROPHIC_ERROR,Invalid USBPD_DRIVER,There is no vendor-provided USBPD driver available)
            endif
        else ifeq ($(strip $(USBPD_DRIVER)), custom)
            OPT_DEFS += -DUSBPD_CUSTOM
            # Board designers can add their own driver to $(SRC)
        endif
    endif
endif

BLUETOOTH_ENABLE ?= no
VALID_BLUETOOTH_DRIVER_TYPES := bluefruit_le custom rn42
ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
    ifeq ($(filter $(strip $(BLUETOOTH_DRIVER)),$(VALID_BLUETOOTH_DRIVER_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid BLUETOOTH_DRIVER,BLUETOOTH_DRIVER="$(BLUETOOTH_DRIVER)" is not a valid Bluetooth driver type)
    endif
    OPT_DEFS += -DBLUETOOTH_ENABLE
    OPT_DEFS += -DBLUETOOTH_$(strip $(shell echo $(BLUETOOTH_DRIVER) | tr '[:lower:]' '[:upper:]'))
    NO_USB_STARTUP_CHECK := yes
    COMMON_VPATH += $(DRIVER_PATH)/bluetooth
    SRC += outputselect.c

    ifeq ($(strip $(BLUETOOTH_DRIVER)), bluefruit_le)
        SPI_DRIVER_REQUIRED = yes
        ANALOG_DRIVER_REQUIRED = yes
        SRC += $(DRIVER_PATH)/bluetooth/bluetooth.c
        SRC += $(DRIVER_PATH)/bluetooth/bluefruit_le.cpp
    endif

    ifeq ($(strip $(BLUETOOTH_DRIVER)), rn42)
        UART_DRIVER_REQUIRED = yes
        SRC += $(DRIVER_PATH)/bluetooth/bluetooth.c
        SRC += $(DRIVER_PATH)/bluetooth/rn42.c
    endif
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += $(QUANTUM_DIR)/encoder.c
    OPT_DEFS += -DENCODER_ENABLE
    ifeq ($(strip $(ENCODER_MAP_ENABLE)), yes)
        OPT_DEFS += -DENCODER_MAP_ENABLE
    endif
endif

ifeq ($(strip $(DIP_SWITCH_ENABLE)), yes)
    ifeq ($(strip $(DIP_SWITCH_MAP_ENABLE)), yes)
        OPT_DEFS += -DDIP_SWITCH_MAP_ENABLE
    endif
endif

VALID_WS2812_DRIVER_TYPES := bitbang custom i2c pwm spi vendor

WS2812_DRIVER ?= bitbang
ifeq ($(strip $(WS2812_DRIVER_REQUIRED)), yes)
    ifeq ($(filter $(WS2812_DRIVER),$(VALID_WS2812_DRIVER_TYPES)),)
        $(call CATASTROPHIC_ERROR,Invalid WS2812_DRIVER,WS2812_DRIVER="$(WS2812_DRIVER)" is not a valid WS2812 driver)
    endif

    OPT_DEFS += -DWS2812_$(strip $(shell echo $(WS2812_DRIVER) | tr '[:lower:]' '[:upper:]'))

    SRC += ws2812_$(strip $(WS2812_DRIVER)).c

    ifeq ($(strip $(PLATFORM)), CHIBIOS)
        ifeq ($(strip $(WS2812_DRIVER)), pwm)
            OPT_DEFS += -DSTM32_DMA_REQUIRED=TRUE
        endif
    endif

    # add extra deps
    ifeq ($(strip $(WS2812_DRIVER)), i2c)
        I2C_DRIVER_REQUIRED = yes
    endif
endif

ifeq ($(strip $(APA102_DRIVER_REQUIRED)), yes)
    COMMON_VPATH += $(DRIVER_PATH)/led
    SRC += apa102.c
endif

ifeq ($(strip $(ANALOG_DRIVER_REQUIRED)), yes)
    OPT_DEFS += -DHAL_USE_ADC=TRUE
    QUANTUM_LIB_SRC += analog.c
endif

ifeq ($(strip $(I2C_DRIVER_REQUIRED)), yes)
    OPT_DEFS += -DHAL_USE_I2C=TRUE
    QUANTUM_LIB_SRC += i2c_master.c
endif

ifeq ($(strip $(SPI_DRIVER_REQUIRED)), yes)
    OPT_DEFS += -DHAL_USE_SPI=TRUE
    QUANTUM_LIB_SRC += spi_master.c
endif

ifeq ($(strip $(UART_DRIVER_REQUIRED)), yes)
    OPT_DEFS += -DHAL_USE_SERIAL=TRUE
    QUANTUM_LIB_SRC += uart.c
endif
