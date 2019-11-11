# Build Options
#   change to "no" to disable the options, or define them in the Makefile in 
#   the appropriate keymap folder that will get included automatically
#

MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = yes
COMMAND_ENABLE = no
NKRO_ENABLE = yes
UNICODE_ENABLE = yes

# make keebio/bfo9000:deepbluealchemy:avrdude SPLIT_LEFT=yes

ifeq ($(strip $(SPLIT_LEFT)), yes) 
    OLED_DRIVER_ENABLE=yes
else
    OLED_DRIVER_ENABLE=no
endif
