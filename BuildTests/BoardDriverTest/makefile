#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile for the board driver build test. This
# test attempts to build a dummy project with all
# possible board targets using their respective
# compiler.

# Path to the root of the LUFA tree to scan
LUFA_ROOT_PATH    = ../..


all: begin makeboardlist testboards clean end

begin:
	@echo Executing build test "BoardDriverTest".
	@echo

end:
	@echo Build test "BoardDriverTest" complete.
	@echo

makeboardlist:
	@grep "BOARD_" $(LUFA_ROOT_PATH)/LUFA/Common/BoardTypes.h | cut -d'#' -f2 | cut -d' ' -f2 | grep "BOARD_" > BoardList.txt
	
testboards:
	echo "%:" > BuildMakefile
	@while read line; \
	 do \
	   build_cfg=`grep "$$line " BoardDeviceMap.cfg | cut -d'=' -f2-`; \
	   \
	   build_board=$$line; \
	   build_arch=`echo $$build_cfg | cut -d':' -f1 | cut -d' ' -f1`; \
	   build_mcu=`echo $$build_cfg | cut -d':' -f2 | cut -d' ' -f2`; \
	   \
	   if ( test -z "$$build_cfg" ); then \
	     echo "No matching information set for board $$line"; \
	   else \
		 printf "\tmake -f makefile.$$build_arch clean\n" >> BuildMakefile; \
		 printf "\tmake -f makefile.$$build_arch MCU=$$build_mcu BOARD=$$build_board\n" >> BuildMakefile; \
	   fi; \
	 done < BoardList.txt
	 $(MAKE) -f BuildMakefile all

clean:
	rm -f BuildMakefile
	rm -f BoardList.txt
	$(MAKE) -f makefile.avr8 clean
	$(MAKE) -f makefile.xmega clean
	$(MAKE) -f makefile.uc3 clean

%:
	