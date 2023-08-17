RGB_MATRIX_ENABLE = no
CUSTOM_UNICODE_ENABLE = no
CUSTOM_POINTING_DEVICE = no
CUSTOM_SPLIT_TRANSPORT_SYNC = no


ifeq ($(strip $(KEYBOARD)), bastardkb/charybdis/3x5/blackpill)
    # Bootloader selection
    BOOTLOADER := tinyuf2

    LTO_ENABLE := no

    AUDIO_SUPPORTED = yes
    AUDIO_ENABLE = yes
    AUDIO_DRIVER = pwm_hardware

    OVERLOAD_FEATURES = yes
endif

ifeq ($(strip $(KEYBOARD)), bastardkb/charybdis/3x5/v2/stemcell)
    OVERLOAD_FEATURES = yes
endif
ifeq ($(strip $(KEYBOARD)), bastardkb/charybdis/3x5/v2/splinky)
    OVERLOAD_FEATURES = yes
endif


ifeq ($(strip $(OVERLOAD_FEATURES)), yes)
    BOOTMAGIC_ENABLE = yes     # Enable Bootmagic Lite
    KEYBOARD_SHARED_EP = yes
    MOUSE_SHARED_EP = yes

    MOUSEKEY_ENABLE = yes
    NKRO_ENABLE = yes
    CONSOLE_ENABLE = yes
    RGB_MATRIX_ENABLE = yes

    AUTOCORRECT_ENABLE = yes

    CUSTOM_UNICODE_ENABLE = yes
    CUSTOM_POINTING_DEVICE = yes
    CUSTOM_SPLIT_TRANSPORT_SYNC = yes
endif
