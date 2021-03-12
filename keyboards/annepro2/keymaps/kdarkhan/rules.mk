NKRO_ENABLE = no
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
LTO_ENABLE = yes

UCIS_ENABLE = yes

# tech2077
# CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
DEBUG_EEPROM = no

ifeq ($(strip $(BOARD)), ANNEPRO2_C18)
ANNEPRO2_EEPROM = yes
endif

ifeq ($(strip $(ANNEPRO2_EEPROM)), yes)
    OPT_DEFS += -DANNEPRO2_EEPROM
    SRC += spi_master.c eeprom_w25x20cl.c
endif
