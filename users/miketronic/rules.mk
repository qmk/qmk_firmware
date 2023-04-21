SRC += miketronic.c tapdances.c process_records.c


# Common feature for all keyboards
BOOTMAGIC_ENABLE  = yes
EXTRAKEY_ENABLE   = yes
TAP_DANCE_ENABLE  = yes
MACROS_ENABLED    = yes
RGBLIGHT_ENABLE   = no
RGB_MATRIX_ENABLE = no

# idobao/id75
ifeq ($(strip $(KEYBOARD)), idobao/id75/v1)
  RGBLIGHT_ENABLE    = yes        # Enable keyboard RGB underglow
  LEADER_ENABLE      = yes
  NKRO_ENABLE        = yes
  AUTO_SHIFT_ENABLE  = no
  VIA_ENABLE         = no
  MOUSEKEY_ENABLE    = no
  EXTRAKEY_ENABLE    = no
  CONSOLE_ENABLE     = no
  COMMAND_ENABLE     = no
endif

# Satpad
ifeq ($(strip $(KEYBOARD)), hazel/satpad)
  BOOTMAGIC_ENABLE      = yes      # Enable Bootmagic Lite
  MOUSEKEY_ENABLE       = yes      # Mouse keys
  EXTRAKEY_ENABLE       = yes      # Audio control and System control
  NKRO_ENABLE           = yes      # USB Nkey Rollover
  CAPS_WORD_ENABLE		= yes
  KEY_OVERRIDE_ENABLE	= yes
  TAP_DANCE_ENABLE		= yes
  OLED_ENABLE 			= yes
  OLED_DRIVER 			= SSD1306
  ENCODER_ENABLE 	    = yes
  ENCODER_MAP_ENABLE 	= yes


  LTO_ENABLE 	        = no       # Enabled this causes longer build time, but smaller file.
  AUTO_SHIFT_ENABLE     = no     
  UNICODE_ENABLE        = no       # Unicode
  CONSOLE_ENABLE        = no       # Console for debug
  COMMAND_ENABLE        = no       # Commands for debug and configuration
  RGBLIGHT_ENABLE       = no
  BACKLIGHT_ENABLE      = no       # Enable keyboard backlight functionality
  SLEEP_LED_ENABLE      = no       # Breathing sleep LED during USB suspend (it uses the same timer as BACKLIGHT_ENABLE)
  AUDIO_ENABLE          = no       # Audio output on port C6
  MIDI_ENABLE           = no       # MIDI support
  BLUETOOTH_ENABLE      = no       # Enable Bluetooth with the Adafruit EZ-Key HID
  GRAVE_ESC_ENABLE	    = no
  SPACE_CADET_ENABLE    = no
  COMBO_ENABLE			= no

  # OLED WIDGETS

  # WPM_ENABLE 			= no
  # KEYCOUNT_ENABLE 	= yes
  # KEYLOG_ENABLE		= no
  # KEYLOG_DEBUG		= no
endif


# 1upkeyboards/pi40
ifeq ($(strip $(KEYBOARD)), 1upkeyboards/pi40/mit_v1_0)
  BOOTMAGIC_ENABLE      = yes       # Enable Bootmagic Lite
  EXTRAKEY_ENABLE       = yes       # Audio control and System control
  TAP_DANCE_ENABLE      = yes       # Tap Dance keys
  NKRO_ENABLE           = yes       # Enable N-Key Rollover
  MACROS_ENABLED        = yes

  AUTO_SHIFT_ENABLE     = no 
  CONSOLE_ENABLE        = no        # Console for debug
  COMMAND_ENABLE        = no        # Commands for debug and configuration
  BACKLIGHT_ENABLE      = no        # Enable keyboard backlight functionality
  RGBLIGHT_ENABLE       = no        # Enable keyboard RGB underglow
  AUDIO_ENABLE          = no        # Audio output
  MOUSEKEY_ENABLE       = no        # Mouse keys

  RGB_MATRIX_ENABLE     = yes
  RGB_MATRIX_DRIVER     = WS2812
  WS2812_DRIVER         = vendor
  ENCODER_ENABLE        = yes
  ENCODER_MAP_ENABLE    = yes
  OLED_ENABLE           = yes
  OLED_DRIVER           = SSD1306
endif




