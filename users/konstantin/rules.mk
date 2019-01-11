SRC += konstantin.c

EXTRAFLAGS += -flto

BOOTMAGIC_ENABLE = full # TODO: Disable once Command is fixed
COMMAND_ENABLE   = no
CONSOLE_ENABLE   = yes
EXTRAKEY_ENABLE  = yes
MOUSEKEY_ENABLE  = yes
NKRO_ENABLE      = yes
TAP_DANCE_ENABLE = yes
UNICODE_ENABLE   = yes
