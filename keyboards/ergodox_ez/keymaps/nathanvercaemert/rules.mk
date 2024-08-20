# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LTO_ENABLE = yes
COMMAND_ENABLE = no # need to enable this for some debugging stuff
RGBLIGHT_ENABLE = no
DYNAMIC_MACRO_ENABLE = yes

# allow computer to sleep
NO_USB_STARTUP_CHECK = yes

# Debugging
CONSOLE_ENABLE = yes

# Trying to save space
EXTRAFLAGS        += -flto
UNICODE_ENABLE   = no # Unicode

# deferred execution
DEFERRED_EXEC_ENABLE = yes
