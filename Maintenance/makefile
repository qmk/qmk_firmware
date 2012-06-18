#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Maintenance scripts not required by general LUFA users, used for project development purposes.


# Path to the root of the LUFA tree
LUFA_ROOT = ../

all:

# Update all Doxygen configuration files to the latest Doxygen version - force Markdown support to be disabled
upgrade-doxygen:
	@echo Upgrading Doxygen.conf files...
	@for doxygen_conf in `find $(LUFA_ROOT) -name Doxygen.conf`; do                                       \
	  doxygen -u $$doxygen_conf;                                                                          \
	  sed "s/MARKDOWN_SUPPORT *= *YES/MARKDOWN_SUPPORT       = NO/1" $$doxygen_conf > $$doxygen_conf.new; \
	  sed "s/DISABLE_INDEX *= *NO/DISABLE_INDEX       = YES/1" $$doxygen_conf.new > $$doxygen_conf.new2;  \
	  mv -u $$doxygen_conf.new2 $$doxygen_conf;                                                           \
	  rm $$doxygen_conf.new;                                                                              \
	done;
	@echo Doxygen configuration update complete.

# Generate AVR Studio 4 project files for each project from a template
make-as4-projects:
	@echo Creating AVR Studio 4 project files for Demos...
	@for project_makefile in `find $(LUFA_ROOT)/Demos $(LUFA_ROOT)/Projects $(LUFA_ROOT)/Bootloaders -name makefile*`; do \
	  target_name=`grep "TARGET *=" $$project_makefile | cut -d'=' -f2 | sed 's/ //g'`; \
	  target_folder=`dirname $$project_makefile`;                                   \
	  as4_date=`date "+%-e-%b-%Y %-H:%-M:%-S"`;                                     \
	                                                                                \
	  if ( test -n "$$target_name" ); then                                          \
	    echo Creating AS4 project for project $$target_name;                        \
	                                                                                \
	    source_files="<OTHERFILE>`basename $$project_makefile`<\/OTHERFILE>";       \
	    gcc_source_files="";                                                        \
	    for c_source_file in `find $$target_folder -name *.c`; do                   \
	      source_filename=`basename $$c_source_file`;                               \
	                                                                                \
	      source_files="$$source_files<SOURCEFILE>$$source_filename<\/SOURCEFILE>"; \
	      gcc_source_files="$$gcc_source_files<Name>$$source_filename<\/Name>";     \
	    done;                                                                       \
	    for c_header_file in `find $$target_folder -name *.h`; do                   \
	      source_filename=`basename $$c_header_file`;                               \
	                                                                                \
	      source_files="$$source_files<HEADERFILE>$$source_filename<\/HEADERFILE>"; \
	      gcc_source_files="$$gcc_source_files<Name>$$source_filename<\/Name>";     \
	    done;                                                                       \
	    for assembly_file in `find $$target_folder -name *.S`; do                   \
	      source_filename=`basename $$assembly_file`;                               \
	                                                                                \
	      source_files="$$source_files<OTHERFILE>$$source_filename<\/OTHERFILE>";   \
	      gcc_source_files="$$gcc_source_files<Name>$$source_filename<\/Name>";     \
	    done;                                                                       \
	                                                                                \
	    sed "s/%TARGET%/$$target_name/g" AS4Template.aps > $$target_folder/$$target_name.aps.new;                                     \
	    sed "s/%CREATED%/$$as4_date/g" $$target_folder/$$target_name.aps.new > $$target_folder/$$target_name.aps.new2;                \
	    sed "s/%FILE_LIST%/$$source_files/g" $$target_folder/$$target_name.aps.new2 > $$target_folder/$$target_name.aps.new3;         \
	    sed "s/%GCC_FILE_LIST%/$$gcc_source_files/g" $$target_folder/$$target_name.aps.new3 > $$target_folder/$$target_name.aps.new4; \
	    mv $$target_folder/$$target_name.aps.new4 $$target_folder/$$target_name.aps;                                                  \
	    rm $$target_folder/$$target_name.aps.new $$target_folder/$$target_name.aps.new2 $$target_folder/$$target_name.aps.new3;       \
	  fi; \
	done;
	@echo AVR Studio 4 project generation complete.
	
# Check the working branch documentation, ensure no placeholder values
check-documentation-placeholders:
	@echo Checking for release suitability...
	@if ( grep "XXXXXX" $(LUFA_ROOT)/LUFA/DoxygenPages/*.txt > /dev/null ;); then \
	  echo "  ERROR: Doxygen documentation has not been updated for release!";    \
	  exit 1;                                                                     \
	fi;
	@if ( grep "000000" $(LUFA_ROOT)/LUFA/Version.h > /dev/null ;); then          \
	  echo "  ERROR: Version header has not been updated for release!";           \
	  exit 1;                                                                     \
	fi;
	@echo Done.

# Validate the working branch - compile all documentation, demos/projects/examples and run build tests
validate-branch:
	make -C $(LUFA_ROOT) doxygen
	make -C $(LUFA_ROOT) all
	make -C $(LUFA_ROOT)/BuildTests all

# Validate the working branch for general release, check for placeholder documentation then build and test everything
validate-release: check-documentation-placeholders validate-branch


.PHONY: all upgrade-doxygen make-as4-projects check-documentation-placeholders validate-branch