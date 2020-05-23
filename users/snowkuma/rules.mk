BOOTMAGIC_ENABLE = no       # Disable Boot Magic (https://beta.docs.qmk.fm/features/feature_bootmagic)
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
TAP_DANCE_ENABLE = yes      # Enable Tap Dance.

SRC += snowkuma.c \
       process_records.c \
       tap_dances.c \
       oled.c

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
    SRC += secrets.c
endif