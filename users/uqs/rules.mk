# don't include for keyboards/ploopyco/mouse/keymaps/uqs
ifeq ($(filter $(strip $(KEYBOARD)),ploopyco/mouse),)
    SRC += uqs.c

    RGBLIGHT_ENABLE ?= yes      # Enable keyboard RGB underglow
    LTO_ENABLE ?= yes  # disables the legacy TMK Macros and Functions features

    UCIS_ENABLE = yes
    LEADER_ENABLE = yes
    COMBO_ENABLE = yes
    MOUSEKEY_ENABLE = yes

    # Disable all the unused stuff.
    SPACE_CADET_ENABLE = no
    COMMAND_ENABLE = no
    MAGIC_ENABLE = no
endif

# From https://michael.stapelberg.ch/posts/2021-05-08-keyboard-input-latency-qmk-kinesis/
# adds about 900 bytes! Don't use it on puny AVR though.
# ifeq (,$(filter $(MCU), atmega16u2 atmega32u2 at90usb162)) # doesn't work MCU not set yet
ifneq (,$(filter $(KEYBOARD),ploopyco/mouse preonic/rev3))
    DEBOUNCE_TYPE = asym_eager_defer_pk
endif
