#
#             LUFA Library
#     Copyright (C) Dean Camera, 2013.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# ---------------------------------------
#  Makefile for the LUFA Atmel Studio Integration.
# ---------------------------------------

LUFA_ROOT            := ..
DOXYGEN_TAG_FILE_XML := $(LUFA_ROOT)/Documentation/lufa_doc_tags.xml
TEMP_MANIFEST_XML    := manifest.xml
EXTENSION_OUTPUT_XML := $(LUFA_ROOT)/../extension.xml
MODULE_OUTPUT_XML    := $(LUFA_ROOT)/asf.xml
XML_FILES            := $(filter-out $(TEMP_MANIFEST_FILE), $(shell ls *.xml))
LUFA_VERSION_NUM     := $(shell grep LUFA_VERSION_STRING $(LUFA_ROOT)/Version.h | cut -d'"' -f2)
EXT_VERSION_NUM      := $(shell date +"%y.%m.%d").$(LUFA_VERSION_NUM)

all: generate_xml check_filenames generate_vsix

clean:
	@rm -f $(TEMP_MANIFEST_XML) $(MODULE_OUTPUT_XML) $(EXTENSION_OUTPUT_XML)

$(DOXYGEN_TAG_FILE_XML):
	$(MAKE) -C ../ doxygen

$(TEMP_MANIFEST_XML): $(DOXYGEN_TAG_FILE_XML)
	@echo "Generating Manifest XML..."

	@printf "<lufa-manifest version=\"%s\" tagfile=\"%s\">\n" $(LUFA_VERSION_NUM) $(DOXYGEN_TAG_FILE_XML) > $@
	@for i in $(XML_FILES); do \
		printf "\t<xml-source filename=\"%s\"/>\n" $$i >> $@; \
	done;
	@echo '</lufa-manifest>' >> $@

	@echo "Manifest XML file generated."

generate_xml: $(TEMP_MANIFEST_XML)
	@echo "Processing asf.xml file..."
	@xsltproc XSLT/lufa_module_transform.xslt $< | xsltproc XSLT/lufa_indent_transform.xslt - > $(MODULE_OUTPUT_XML)
	@echo "Atmel Studio asf.xml file generated."

	@echo "Processing extension.xml file..."
	@xsltproc XSLT/lufa_extension_transform.xslt $< | xsltproc XSLT/lufa_indent_transform.xslt - > $(EXTENSION_OUTPUT_XML)
	@echo "Atmel Studio extension.xml file generated."

	@rm $(TEMP_MANIFEST_XML)

generate_vsix: $(EXTENSION_OUTPUT_XML) $(MODULE_OUTPUT_XML)
	@echo "Generating ASF cache files..."
	@rm -f $(LUFA_ROOT)/../content.xml.cache
	@rm -f $(LUFA_ROOT)/../ExampleProjects.xml
	@python generate_caches.py $(LUFA_ROOT)/../

	@echo "Archiving Content..."
	@cd $(LUFA_ROOT)/../ && zip contents.zip -q -0 -r --exclude=*Documentation* --exclude=*StudioIntegration* LUFA Bootloaders Demos Projects extension.xml README.txt

	@echo "Creating VSIX Dependencies..."
	@cp $(LUFA_ROOT)/DoxygenPages/Images/LUFA_thumb.png $(LUFA_ROOT)/../PreviewThumb.png
	@cp $(LUFA_ROOT)/DoxygenPages/Images/LUFA.png $(LUFA_ROOT)/../Preview.png
	@cp $(LUFA_ROOT)/License.txt $(LUFA_ROOT)/../
	@cp "VSIX/[Content_Types].xml" $(LUFA_ROOT)/../
	@xsltproc --stringparam extension-version "$(EXT_VERSION_NUM)" XSLT/lufa_vsmanifest_transform.xslt VSIX/extension.vsixmanifest > $(LUFA_ROOT)/../extension.vsixmanifest
	@xsltproc --stringparam lufa-version "$(LUFA_VERSION_NUM)" XSLT/lufa_asfmanifest_transform.xslt VSIX/asf-manifest.xml > $(LUFA_ROOT)/../asf-manifest.xml

	@echo "Generating Atmel Studio VSIX Extension file..."
	@cd $(LUFA_ROOT)/../ && zip LUFA-$(LUFA_VERSION_NUM).vsix -q -9 contents.zip exampleProjects.xml content.xml.cache License.txt Preview.png PreviewThumb.png "[Content_Types].xml" extension.vsixmanifest asf-manifest.xml extension.xml
	@echo "Atmel Studio VSIX Extension file generated."

check_filenames: $(MODULE_OUTPUT_XML)
	@echo Verifying referenced filenames of ASF.xml modules...
	@for f in `find $(LUFA_ROOT)/../ -name "asf.xml"`; do \
		echo "Checking $$f..."; \
		asf_file_dir=`dirname $$f`; \
		xsltproc XSLT/lufa_filelist_transform.xslt $$f | sed -e "/^$$/d" | while read -r i; do \
			if ( ! test -f "$$asf_file_dir/$$i" ); then \
				echo "Source file \"$$i\" referenced in $$f does not exist!"; \
				exit 1; \
			fi; \
		done || exit 1; \
	done;
	@echo Verified referenced filenames of ASF.xml modules.

.PHONY: all clean generate_xml generate_vsix check_filenames
