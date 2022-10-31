ifeq ($(strip $(KEYBOARD)), bastardkb/charybdis/3x5/v1/elitec)
    # MCU name
    MCU = STM32F411
    BOARD = BLACKPILL_STM32_F411

    # Bootloader selection
    BOOTLOADER := tinyuf2

    LTO_ENABLE := no

    EEPROM_DRIVER = spi
    WS2812_DRIVER = pwm
    SERIAL_DRIVER = usart
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
ifeq ($(strip $(KEYBOARD)), bastardkb/charybdis/3x5/blackpill)
    OVERLOAD_FEATURES = yes
endif


ifeq ($(strip $(OVERLOAD_FEATURES)), yes)
    BOOTMAGIC_ENABLE = yes     # Enable Bootmagic Lite
    KEYBOARD_SHARED_EP = yes
    MOUSE_SHARED_EP = yes

    MOUSEKEY_ENABLE = yes
    NKRO_ENABLE = yes
    CONSOLE_ENABLE = yes

    AUTOCORRECT_ENABLE = yes

    DEBOUNCE_TYPE = asym_eager_defer_pk
endif
