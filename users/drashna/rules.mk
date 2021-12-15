SRC += $(USER_PATH)/drashna.c \
<<<<<<< HEAD
       $(USER_PATH)/process_records.c
=======
       $(USER_PATH)/keyrecords/process_records.c
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565

ifneq ($(PLATFORM),CHIBIOS)
    ifneq ($(strip $(LTO_SUPPORTED)), no)
        LTO_ENABLE        = yes
    endif
endif
SPACE_CADET_ENABLE    = no
GRAVE_ESC_ENABLE      = no

ifneq ($(strip $(NO_SECRETS)), yes)
<<<<<<< HEAD
    ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
        SRC += $(USER_PATH)/secrets.c
=======
    ifneq ("$(wildcard $(USER_PATH)/keyrecords/secrets.c)","")
        SRC += $(USER_PATH)/keyrecords/secrets.c
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
    endif
    ifeq ($(strip $(NO_SECRETS)), lite)
        OPT_DEFS += -DNO_SECRETS
    endif
endif

CUSTOM_UNICODE_ENABLE ?= yes
ifeq ($(strip $(CUSTOM_UNICODE_ENABLE)), yes)
    UNICODE_ENABLE        = no
    UNICODEMAP_ENABLE     = no
    UCIS_ENABLE           = no
    UNICODE_COMMON        = yes
    OPT_DEFS += -DCUSTOM_UNICODE_ENABLE
<<<<<<< HEAD
    SRC += unicoooode.c
=======
    SRC += $(USER_PATH)/keyrecords/unicode.c
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
endif

CUSTOM_TAP_DANCE ?= yes
ifeq ($(strip $(CUSTOM_TAP_DANCE)), yes)
    ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
<<<<<<< HEAD
        SRC += $(USER_PATH)/tap_dances.c
=======
        SRC += $(USER_PATH)/keyrecords/tap_dances.c
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
    endif
endif

CUSTOM_RGBLIGHT ?= yes
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_RGBLIGHT)), yes)
<<<<<<< HEAD
        SRC += $(USER_PATH)/rgb_stuff.c
=======
        SRC += $(USER_PATH)/rgb/rgb_stuff.c
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
        ifeq ($(strip $(RGBLIGHT_NOEEPROM)), yes)
            OPT_DEFS += -DRGBLIGHT_NOEEPROM
        endif
        ifeq ($(strip $(RGBLIGHT_STARTUP_ANIMATION)), yes)
            OPT_DEFS += -DRGBLIGHT_STARTUP_ANIMATION
        endif
    endif
endif

CUSTOM_RGB_MATRIX ?= yes
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_RGB_MATRIX)), yes)
<<<<<<< HEAD
        SRC += $(USER_PATH)/rgb_matrix_stuff.c
=======
        SRC += $(USER_PATH)/rgb/rgb_matrix_stuff.c
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
    endif
endif

KEYLOGGER_ENABLE ?= no
ifdef CONSOLE_ENABLE
    ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
        OPT_DEFS += -DKEYLOGGER_ENABLE
    endif
endif

ifeq ($(strip $(MAKE_BOOTLOADER)), yes)
    OPT_DEFS += -DMAKE_BOOTLOADER
endif

# At least until build.mk or the like drops, this is here to prevent
# VUSB boards from enabling NKRO, as they do not support it. Ideally
# this should be handled per keyboard, but until that happens ...
ifeq ($(strip $(PROTOCOL)), VUSB)
    NKRO_ENABLE       = no
endif

CUSTOM_OLED_DRIVER ?= yes
ifeq ($(strip $(OLED_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_OLED_DRIVER)), yes)
<<<<<<< HEAD
        SRC += $(USER_PATH)/oled_stuff.c
=======
        SRC += $(USER_PATH)/oled/oled_stuff.c
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
        OPT_DEFS += -DCUSTOM_OLED_DRIVER_CODE
    endif
endif

<<<<<<< HEAD
ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    POINTING_DEVICE_ENABLE := yes
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    SRC += drivers/sensors/pimoroni_trackball.c
    QUANTUM_LIB_SRC += i2c_master.c
=======
CUSTOM_POINTING_DEVICE ?= yes
ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_POINTING_DEVICE)), yes)
        SRC += $(USER_PATH)/pointing/pointing.c
    endif
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
endif

CUSTOM_SPLIT_TRANSPORT_SYNC ?= yes
ifeq ($(strip $(CUSTOM_SPLIT_TRANSPORT_SYNC)), yes)
    ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
<<<<<<< HEAD
        QUANTUM_LIB_SRC += $(USER_PATH)/transport_sync.c
=======
        QUANTUM_LIB_SRC += $(USER_PATH)/split/transport_sync.c
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
        OPT_DEFS += -DCUSTOM_SPLIT_TRANSPORT_SYNC
    endif
endif

# DEBUG_MATRIX_SCAN_RATE_ENABLE = api

AUTOCORRECTION_ENABLE ?= yes
ifeq ($(strip $(AUTOCORRECTION_ENABLE)), yes)
    SRC += $(USER_PATH)/keyrecords/autocorrection/autocorrection.c
    OPT_DEFS += -DAUTOCORRECTION_ENABLE
endif

CAPS_WORD_ENABLE ?= yes
ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
    SRC += $(USER_PATH)/keyrecords/caps_word.c
    OPT_DEFS += -DCAPS_WORD_ENABLE
endif
