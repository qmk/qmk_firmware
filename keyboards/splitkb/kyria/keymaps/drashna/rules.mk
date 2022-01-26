BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE            = no       # Mouse keys
EXTRAKEY_ENABLE            = yes      # Audio control and System control
CONSOLE_ENABLE             = no       # Console for debug
COMMAND_ENABLE             = no       # Commands for debug and configuration
NKRO_ENABLE                = yes      # USB Nkey Rollover
OLED_ENABLE                = yes
ENCODER_ENABLE             = yes      # Enables the use of one or more encoders
RGBLIGHT_ENABLE            = no       # Enable keyboard RGB underglow
KEY_LOCK_ENABLE            = no
WPM_ENABLE                 = yes

ifeq ($(strip $(KEYBOARD)), splitkb/kyria/rev1/proton_c)
    RGB_MATRIX_ENABLE      = yes
    CONSOLE_ENABLE         = yes      # Console for debug
    MOUSEKEY_ENABLE        = yes      # Mouse keys
    TAP_DANCE_ENABLE       = yes
    SWAP_HANDS_ENABLE      = yes
    LTO_ENABLE             = no
    CTPC                   = yes
    AUTOCORRECTION_ENABLE  = yes
    CAPS_WORD_ENABLE       = yes
else
    LTO_ENABLE             = yes
    BOOTLOADER             = qmk-hid
    BOOTLOADER_SIZE        = 512
endif
