#
#             LUFA Library
#     Copyright (C) Dean Camera, 2017.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile for the board driver build test. This
# test attempts to build a dummy project with all
# possible board targets using their respective
# compiler.

# Path to the LUFA library core
LUFA_PATH := ../../LUFA/

# Build test cannot be run with multiple parallel jobs
.NOTPARALLEL:

all: begin makeboardlist testboards clean end

begin:
	@echo Executing build test "BoardDriverTest".
	@echo

end:
	@echo Build test "BoardDriverTest" complete.
	@echo

makeboardlist:
	@grep "BOARD_" $(patsubst %/,%,$(LUFA_PATH))/Common/BoardTypes.h | cut -d'#' -f2 | cut -d' ' -f2 | grep "BOARD_" > BoardList.txt

testboards:
	@echo "buildtest:" > BuildMakefile

	@while read line;                                                                               \
	 do                                                                                             \
	   build_cfg=`grep "$$line " BoardDeviceMap.cfg | grep -v "#" | cut -d'=' -f2- | sed 's/ //g'`; \
	                                                                                                \
	   build_board=$$line;                                                                          \
	   build_arch=`echo $$build_cfg | cut -d':' -f1`;                                               \
	   build_mcu=`echo $$build_cfg | cut -d':' -f2`;                                                \
	                                                                                                \
	   if ( test -z "$$build_cfg" ); then                                                           \
	     echo "No matching information set for board $$build_board";                                \
	   else                                                                                         \
	     echo "Found board configuration for $$build_board - $$build_arch, $$build_mcu";            \
		                                                                                            \
		 printf "\t@echo Building dummy project for $$build_board...\n" >> BuildMakefile;           \
		 printf "\t$(MAKE) -f makefile.test clean elf MCU=%s ARCH=%s BOARD=%s\n\n" $$build_mcu $$build_arch $$build_board >> BuildMakefile; \
	   fi;                                                                                          \
	 done < BoardList.txt

	 $(MAKE) -f BuildMakefile buildtest

clean:
	rm -f BuildMakefile
	rm -f BoardList.txt
	$(MAKE) -f makefile.test clean BOARD=NONE ARCH=AVR8 MCU=at90usb1287
	$(MAKE) -f makefile.test clean BOARD=NONE ARCH=XMEGA MCU=atxmega128a1u
	$(MAKE) -f makefile.test clean BOARD=NONE ARCH=UC3 MCU=uc3a0256

%:

.PHONY: all begin end makeboardlist testboards clean

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
