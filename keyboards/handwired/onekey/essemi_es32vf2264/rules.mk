# RISC-V
MCU = risc-v

# RISC-V extensions and abi configuration
MCU_ARCH = rv32emc
MCU_ABI = ilp32e
MCU_CMODEL = medlow

## chip/board settings
# - the next two should match the directories in
#   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
#   OR
#   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_PORT_NAME = ES32
MCU_FAMILY = ES32
MCU_SERIES = ES32VF2264

# Linker script to use
# - it should exist either in <chibios>/os/common/startup/RISCV-CLIC/compilers/GCC/ld/
#   or <keyboard_dir>/ld/
MCU_LDSCRIPT ?= ES32VF2264

# Startup code to use
#  - it should exist in <chibios>/os/common/startup/RISCV-CLIC/compilers/GCC/mk/
MCU_STARTUP ?= es32vf2264

# Board: it should exist either in <chibios>/os/hal/boards/,
# <keyboard_dir>/boards/, or drivers/boards/
BOARD ?= ES32VF2264

USE_FPU ?= no