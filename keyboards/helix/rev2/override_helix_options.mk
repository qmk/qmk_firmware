$(info -------------------------)
$(info override_helix_options.mk)
$(info -------------------------)

define HELIX_OVERRIDE_PARSE
      ifeq ($(strip $1),back)
        LED_BACK_ENABLE = yes
        LED_UNDERGLOW_ENABLE = no
      endif
      ifeq ($(strip $1),under)
        LED_BACK_ENABLE = no
        LED_UNDERGLOW_ENABLE = yes
      endif
      ifneq ($(filter led-off led_off noback no-back nounder no-under,$(strip $1)),)
        LED_BACK_ENABLE = no
        LED_UNDERGLOW_ENABLE = no
      endif
      ifneq ($(filter core-oled core_oled newoled new-oled olednew oled-new,$(strip $1)),)
        OLED_ENABLE = yes
        OLED_SELECT = core
      endif
      ifneq ($(filter local-oled local_oled oldoled old-oled oledold oled-old,$(strip $1)),)
        OLED_ENABLE = yes
        OLED_SELECT = local
      endif
      ifneq ($(filter sc split-common split_common,$(strip $1)),)
        SPLIT_KEYBOARD = yes
      endif
      ifneq ($(filter nosc no-sc no-split-common no-split_common,$(strip $1)),)
        SPLIT_KEYBOARD = no
      endif
      ifeq ($(strip $1),scan)
          DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
      endif
      ifeq ($(strip $1),scan-api)
          DEBUG_MATRIX_SCAN_RATE_ENABLE = api
      endif
      ifeq ($(strip $1),lto)
          LTO_ENABLE = yes
      endif
      ifneq ($(filter nolto no-lto no_lto,$(strip $1)),)
          LTO_ENABLE = no
      endif
endef # end of HELIX_OVERRIDE_PARSE
