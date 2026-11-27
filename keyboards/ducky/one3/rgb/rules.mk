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

SRC += mbi5042.c fmc.c dip.c

# `qmk flash` with the board in its bootloader (QK_BOOT or D+L); needs nu-isp-cli and access to 0416:3f00
PROGRAM_CMD = nu-isp-cli 0416:3f00 flash $(BUILD_DIR)/$(TARGET).bin
