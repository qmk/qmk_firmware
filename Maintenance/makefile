#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Maintenance scripts not required by general LUFA users, used for project development purposes.

LUFA_ROOT = ../

all:


# Update all Doxygen configuration files to the latest Doxygen version - force Markdown support to be disabled
upgrade-doxygen:
	@echo Upgrading Doxygen.conf files...
	@for doxygen_conf in `find $(LUFA_ROOT) -name Doxygen.conf`; do \
	  doxygen -u $$doxygen_conf; \
	  sed "s/MARKDOWN_SUPPORT *= *YES/MARKDOWN_SUPPORT       = NO/1" $$doxygen_conf > $$doxygen_conf.new; \
	  mv -u $$doxygen_conf.new $$doxygen_conf; \
	done;
	@echo Doxygen configuration update complete.

# Check the working branch documentation, ensure no placeholder values
check-documentation-placeholders:
	@echo Checking for release suitability...
	@if ( grep "XXXXXX" $(LUFA_ROOT)/LUFA/DoxygenPages/*.txt > /dev/null ;); then \
	  echo "  ERROR: Doxygen documentation has not been updated for release!"; \
	  exit 1; \
	fi;
	@if ( grep "000000" $(LUFA_ROOT)/LUFA/Version.h > /dev/null ;); then \
	  echo "  ERROR: Version header has not been updated for release!"; \
	  exit 1; \
	fi;
	@echo Done.

# Validate the working branch - compile all documentation, demos/projects/examples and run build tests
validate-branch:
	make -s -C $(LUFA_ROOT) doxygen
	make -s -C $(LUFA_ROOT) all	
	make -s -C $(LUFA_ROOT)/BuildTests all

# Validate the working branch for general release, check for placeholder documentation then build and test everything
validate-release: check-documentation-placeholders validate-branch
