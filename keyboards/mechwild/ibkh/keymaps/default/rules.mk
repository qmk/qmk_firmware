# Needed options for Stenography:
STENO_ENABLE = yes          # Stenography  keys
NKRO_ENABLE = yes			# NKey Rollover
VIRTSER_ENABLE = yes		# Virtual Serial

# These options are disabled to free up endpoints
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
MIDI_ENABLE = no			# Needed to free up endpoints for steno
RAW_ENABLE = no				# Needed to free up endpoints for steno

# Shared endpoints is needed to free up endpoints
KEYBOARD_SHARED_EP = yes    # Needed to free up endpoints for steno