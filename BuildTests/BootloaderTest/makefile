#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile for the bootloader build test. This
# test attempts to build all the bootloaders
# with all supported device configurations.

# Path to the LUFA library core
LUFA_PATH         = ../../LUFA/


all: begin testbootloaders clean end

begin:
	@echo Executing build test "BootloaderTest".
	@echo

end:
	@echo Build test "BootloaderTest" complete.
	@echo
	
testbootloaders:
	@echo "buildtest:" > BuildMakefile
	
	@while read line;                                         \
	 do                                                       \
	   build_cfg=`echo $$line | grep -v "#" | sed 's/ //g'`;  \
	                                                          \
	   if ( test -n "$$build_cfg" ); then                     \
	     build_bootloader=`echo $$build_cfg | cut -d'=' -f1`; \
		 build_cfg=`echo $$build_cfg | cut -d'=' -f2-`;       \
		                                                      \
	     build_arch=`echo $$build_cfg | cut -d':' -f1`;       \
	     build_mcu=`echo $$build_cfg | cut -d':' -f2`;        \
	     build_board=`echo $$build_cfg | cut -d':' -f3`;      \
	     build_flashsize=`echo $$build_cfg | cut -d':' -f4`;  \
	     build_bootsize=`echo $$build_cfg | cut -d':' -f5`;   \
	                                                          \
	     printf "Found '%s' bootloader configuration (FLASH: %3s KB | BOOT: %3s KB | MCU: %12s / %4s)\n" $$build_bootloader $$build_flashsize $$build_bootsize $$build_mcu $$build_arch; \
	                                                          \
	     printf "\t@echo Building bootloader %s - %s - FLASH: %s KB, BOOT: %s KB\n" $$build_bootloader $$build_mcu $$build_flashsize $$build_bootsize >> BuildMakefile; \
	     printf "\t$(MAKE) -s -C $(patsubst %/,%,$(LUFA_PATH))/../Bootloaders/%s/ clean elf ARCH=%s MCU=%s BOARD=%s FLASH_SIZE_KB=%s BOOT_SECTION_SIZE_KB=%s\n\n" $$build_bootloader $$build_arch $$build_mcu $$build_board $$build_flashsize $$build_bootsize >> BuildMakefile; \
	   fi;                                                    \
	 done < BootloaderDeviceMap.cfg
	 
	 $(MAKE) -f BuildMakefile buildtest

clean:
	rm -f BuildMakefile

%:

.PHONY: all begin end testbootloaders clean

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa.core.in
