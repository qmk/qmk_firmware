# MCU: Holtek HT32F52352, booted by the TEX bootloader at 0x0000
MCU = cortex-m0plus
ARMV = 6
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52352_TEX_SHURA
MCU_STARTUP = ht32f523xx
BOARD = HT_HT32F52342_52
BOOTLOADER = custom

PROGRAM_CMD = tex-flash flash --model shura \
    --updater "$${TEX_FLASH_UPDATER:?set TEX_FLASH_UPDATER to the original Shura 0.18 updater}" \
    --backup "$${TEX_FLASH_BACKUP:?set TEX_FLASH_BACKUP to a new metadata backup path}" \
    --bin "$(BUILD_DIR)/$(TARGET).bin" --elf "$(BUILD_DIR)/$(TARGET).elf"

SRC += shura_fn.c shura_trackpoint.c shura_vendor.c wear_leveling_shura.c
# The custom pointing driver reads the TrackPoint through the PS/2 vendor transport.
SRC += ps2_io.c
POINTING_DEVICE_DRIVER = custom
BLUETOOTH_DRIVER = custom
FLASH_DRIVER = spi

# The application starts at 0x3200, above the TEX bootloader; point VTOR there.
ADEFS += -DCRT0_VTOR_INIT=1
OPT_DEFS += -DCRT0_AREAS_NUMBER=1
# Keep the ELF program headers out of the region below the application.
LDFLAGS += -Wl,--nmagic
