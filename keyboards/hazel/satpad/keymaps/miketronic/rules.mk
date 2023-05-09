# Common feature for all keyboards
BOOTMAGIC_ENABLE  = yes		# Enable Bootmagic Lite
EXTRAKEY_ENABLE   = yes		# Audio control and System control
TAP_DANCE_ENABLE  = yes       	# Tap Dance keys
NKRO_ENABLE       = yes     	# Enable N-Key Rollover
MACROS_ENABLED    = yes

# Keyboard specific
MOUSEKEY_ENABLE     = yes      # Mouse keys
LEADER_ENABLE       = yes
CAPS_WORD_ENABLE		= yes
KEY_OVERRIDE_ENABLE	= yes
OLED_ENABLE 			  = yes
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