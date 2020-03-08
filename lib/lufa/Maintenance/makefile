#
#             LUFA Library
#     Copyright (C) Dean Camera, 2019.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Maintenance scripts not required by general LUFA users, used for project development purposes.


# Path to the root of the LUFA tree
LUFA_ROOT := ../

all:

# Generate a header containing all library functions
function-list:
	$(MAKE) -C $(patsubst %/,%,$(LUFA_ROOT))/LUFA doxygen DOXYGEN_OVERRIDE_PARAMS="GENERATE_HTML=no GENERATE_XML=yes"
	@xsltproc $(patsubst %/,%,$(LUFA_ROOT))/LUFA/Documentation/xml/combine.xslt $(patsubst %/,%,$(LUFA_ROOT))/LUFA/Documentation/xml/index.xml > temp.xml
	@xsltproc lufa_functionlist_transform.xslt temp.xml > function_list.h
	@sort function_list.h | uniq > function_list_unique.h
	@rm temp.xml

# Update all Doxygen configuration files to the latest Doxygen version
upgrade-doxygen:
	@echo Upgrading Doxygen files...
	@for doxygen_conf in `find $(LUFA_ROOT) -name doxyfile`; do \
	  doxygen -u $$doxygen_conf;                                \
	done;
	@echo Doxygen configuration update complete.

# Make all possible bootloaders for all targets and configurations as set by the BootloaderTest build test
# and store them in a separate directory called "Bootloaders"
bootloaders:
	@echo "build_bootloaders:" > BuildMakefile
	@printf "\t-mkdir Bootloaders 2>/dev/null\n\n" >> BuildMakefile

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
	     build_fusb=`echo $$build_cfg | cut -d':' -f6`;       \
	                                                          \
	     printf "Found '%s' with FLASH: %3s KB, BOOT: %3s KB, MCU: %12s / %4s, BOARD: %s, F_USB: %sMHz\n" $$build_bootloader $$build_flashsize $$build_bootsize $$build_mcu $$build_arch $$build_board $$build_fusb; \
	                                                          \
	     printf "\t-mkdir Bootloaders/%s 2>/dev/null\n" $$build_bootloader >> BuildMakefile; \
	     printf "\t@echo Building '%s' with FLASH: %3s KB, BOOT: %3s KB, MCU: %12s, BOARD: %s, F_USB: %sMHz\n" $$build_bootloader $$build_flashsize $$build_bootsize $$build_mcu $$build_board $$build_fusb >> BuildMakefile; \
	     printf "\t$(MAKE) -C $(patsubst %/,%,$(LUFA_ROOT))/Bootloaders/%s/ clean hex ARCH=%s MCU=%s BOARD=%s FLASH_SIZE_KB=%s BOOT_SECTION_SIZE_KB=%s F_USB=%s000000 DEBUG_LEVEL=0\n" $$build_bootloader $$build_arch $$build_mcu $$build_board $$build_flashsize $$build_bootsize $$build_fusb >> BuildMakefile; \
		 printf "\tmv $(patsubst %/,%,$(LUFA_ROOT))/Bootloaders/%s/Bootloader%s.hex Bootloaders/%s/%s-%s-%s-BOARD_%s-BOOT_%sKB-%sMHz.hex\n\n" $$build_bootloader $$build_bootloader $$build_bootloader $$build_bootloader $$build_arch $$build_mcu $$build_board $$build_bootsize $$build_fusb >> BuildMakefile; \
	   fi;                                                    \
	 done < $(patsubst %/,%,$(LUFA_ROOT))/BuildTests/BootloaderTest/BootloaderDeviceMap.cfg

	 $(MAKE) -f BuildMakefile build_bootloaders
	 cp $(patsubst %/,%,$(LUFA_ROOT))/LUFA/License.txt Bootloaders
	 rm -f BuildMakefile

# Check the working branch documentation, ensure no placeholder values
check-release:
	@echo Checking for release suitability...
	@if ( grep " LUFA_VERSION_RELEASE_TYPE " $(patsubst %/,%,$(LUFA_ROOT))/LUFA/Version.h | grep "LUFA_VERSION_RELEASE_TYPE_DEVELOPMENT" > /dev/null ;); then          \
	  echo "  ERROR: Version header has not been updated for release!";           \
	  exit 1;                                                                     \
	fi;
	@if ( grep "XXXXXX" $(patsubst %/,%,$(LUFA_ROOT))/LUFA/DoxygenPages/*.txt > /dev/null ;); then \
	  echo "  ERROR: Doxygen documentation has not been updated for release!";    \
	  exit 1;                                                                     \
	fi;

	@echo Done.

.PHONY: all function-list upgrade-doxygen bootloaders check-release
