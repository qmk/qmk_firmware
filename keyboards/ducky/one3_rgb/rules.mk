MCU_FAMILY = NUMICRO
MCU_SERIES = NUC126
# NUC1261SG4AE: peripheral-identical to NUC126SG4AE (vendor headers diffed)
MCU_LDSCRIPT = NUC1261SG4AE
MCU_STARTUP = NUC126
BOARD = NUC1261SG4AE
MCU = cortex-m0
ARMV = 6

# EEPROM: wear-leveled in APROM 0x30000.. via FMC ISP (fmc.c); stock-owned flash untouched
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = custom

SRC += mbi5042.c fmc.c
