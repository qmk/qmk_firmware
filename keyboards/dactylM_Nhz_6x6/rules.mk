# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = halfkay


BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
MOUSEKEY_ENABLE  = no # Mouse keys
EXTRAKEY_ENABLE  = yes # Audio control and System control
CONSOLE_ENABLE   = yes  # Console for debug
COMMAND_ENABLE   = yes # Commands for debug and configuration
AUTO_SHIFT_ENABLE = no

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no     # Virtual DIP switch configuration
MOUSEKEY_ENABLE  = yes    	   # Mouse keys
EXTRAKEY_ENABLE  = yes   	    # Audio control and System control
CONSOLE_ENABLE   = yes   	      # Console for debug
COMMAND_ENABLE   = yes   	      # Commands for debug and configuration
# Do not enable SLEEP_LED	_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    	   # Breathing sleep LED during USB suspend
# if this doesn't work, s	ee here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE 	 = no    	        # USB Nkey Rollover
BACKLIGHT_ENABLE = no    	   # Enable keyboard backlight functionality
RGBLIGHT_ENABLE  = no    	    # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no    	   # Enable Bluetooth
AUDIO_ENABLE	 = no    	       # Audio output

# FROM ERGODOX_EZ
SWAP_HANDS_ENABLE= no # Allow swapping hands of keyboard
API_SYSEX_ENABLE = no
CUSTOM_MATRIX    = yes # Custom matrix file for the ErgoDox EZ
UNICODE_ENABLE   = yes # Unicode

SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
