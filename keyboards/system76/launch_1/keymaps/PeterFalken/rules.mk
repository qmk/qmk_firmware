# Enable VIA support
ENABLE_VIA = yes

# Enable Link-Time Optimization for smaller binary
LTO_ENABLE = yes

# Remove unused features to free up space
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
# EXTRAKEY_ENABLE = no
SPACE_CADET_ENABLE = no		# Need to check space difference
GRAVE_ESC_ENABLE = no		# Not needed - separate ESC key 
MAGIC_ENABLE = no			# No MAGIC functions needed
# MUSIC_ENABLE = no			# Not used