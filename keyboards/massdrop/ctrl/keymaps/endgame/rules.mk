# RGBLIGHT_ENABLE is not for MD boards. This is here in case you forget.
# RGBLIGHT_ENABLE = no				# Enable keyboard underlight functionality
COMMAND_ENABLE = yes				# Commands for debug and configuration
# BOOTMAGIC_ENABLE = full			# Virtual DIP switch configuration
# BOOTMAGIC_ENABLE = lite
# AUTO_SHIFT_ENABLE = yes      	# Auto Shift
NKRO_ENABLE = yes           	# USB Nkey Rollover
DYNAMIC_MACRO_ENABLE = yes		# Dynamic macro recording and play
MOUSEKEY_ENABLE = yes			# Enable mouse control keycodes. Increases firmware size.
TAP_DANCE_ENABLE = yes			# Enable tap dance keys
CONSOLE_ENABLE = yes			# Enable debugging console. Increases firmware size.
SRC += config_led.c				# Used to add files to the compilation/linking list.
TERMINAL_ENABLE = yes
EXTRAKEY_ENABLE = yes			# Audio control and System control
# RAW_ENABLE = yes				# Raw HID has not yet been implemented for this keyboard

# FIRMWARE_FORMAT				# Defines which format (bin, hex) is copied to the root qmk_firmware folder after building.
# LAYOUTS						# A list of layouts this keyboard supports.
# COMBO_ENABLE					# Key combo feature
# AUDIO_ENABLE					# Enable the audio subsystem.
# LEADER_ENABLE					# Enable leader key chording
# CUSTOM_MATRIX					# Allows replacing the standard matrix scanning routine with a custom one.
# DEBOUNCE_TYPE					# Allows replacing the standard key debouncing routine with an alternative or custom one.
# WAIT_FOR_USB					# Forces the keyboard to wait for a USB connection to be established before it starts up
# NO_USB_STARTUP_CHECK			# Disables usb suspend check after keyboard startup. Usually the keyboard waits for the host to wake it up before any tasks are performed. This is useful for split keyboards as one half will not get a wakeup call but must send commands to the master.
# LINK_TIME_OPTIMIZATION_ENABLE	# Enables Link Time Optimization (LTO) when compiling the keyboard.  This makes the process take longer, but can significantly reduce the compiled size (and since the firmware is small, the added time is not noticeable).  However, this will automatically disable the old Macros and Functions features automatically, as these break when LTO is enabled.  It does this by automatically defining NO_ACTION_MACRO and NO_ACTION_FUNCTION. Alternatively, you can use LTO_ENABLE instead of LINK_TIME_OPTIMIZATION_ENABLE.
# MIDI_ENABLE
# MIDI controls
# UNICODE_ENABLE
# Unicode
