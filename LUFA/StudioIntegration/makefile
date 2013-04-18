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
LUFA_VERSION_NUM     := $(shell grep LUFA_VERSION_STRING $(LUFA_ROOT)/Version.h | cut -d'"' -f2)
DOXYGEN_TAG_FILE_XML := $(LUFA_ROOT)/Documentation/lufa_doc_tags.xml
DOXYGEN_COMBINED_XML := $(LUFA_ROOT)/Documentation/xml/lufa_doc.xml
TEMP_MANIFEST_XML    := manifest.xml
EXTENSION_OUTPUT_XML := $(LUFA_ROOT)/../extension.xml
MODULE_OUTPUT_XML    := $(LUFA_ROOT)/asf.xml
XML_FILES            := $(filter-out $(TEMP_MANIFEST_FILE), $(shell ls *.xml))
VSIX_ASSETS          := $(LUFA_ROOT)/DoxygenPages/Images/LUFA_thumb.png \
                        $(LUFA_ROOT)/DoxygenPages/Images/LUFA.png       \
                        $(LUFA_ROOT)/License.txt                        \
                        VSIX/"[Content_Types].xml"                      \
                        VSIX/ASFExplorer.png                            \
                        VSIX/ASFWizard.png                              \
                        VSIX/NewExampleWizard.png                       \
                        VSIX/GettingStarted.htm                         \
                        Blob/Atmel.Studio.Services.Interfaces.dll       \
                        Blob/LUFA.dll                                   \
                        Blob/LUFA.pkgdef

ifneq ($(LUFA_VERSION_NUM),000000)
  EXT_VERSION_NUM    := $(shell date +"%y.%m.%d").$(LUFA_VERSION_NUM)
  EXT_VSIX_NAME      := LUFA-RELEASE-$(LUFA_VERSION_NUM).vsix
else
  EXT_VERSION_NUM    := 0.$(shell date +"%y%m%d.%H%M%S")
  EXT_VSIX_NAME      := LUFA-TESTING-$(shell date +"%y.%m.%d-%H.%M.%S").vsix

  $(warning No LUFA version set - assuming a test version should be created.)
endif

all: generate_xml check_filenames generate_vsix

clean:
	@rm -f $(TEMP_MANIFEST_XML) $(MODULE_OUTPUT_XML) $(EXTENSION_OUTPUT_XML) $(DOXYGEN_TAG_FILE_XML) $(DOXYGEN_COMBINED_XML)

$(DOXYGEN_TAG_FILE_XML):
	@$(MAKE) -C ../ doxygen DOXYGEN_OVERRIDE_PARAMS="GENERATE_TAGFILE=Documentation/lufa_doc_tags.xml GENERATE_HTML=no GENERATE_XML=yes"

$(DOXYGEN_COMBINED_XML): $(DOXYGEN_TAG_FILE_XML)
	@xsltproc $(dir $@)/combine.xslt $(dir $@)/index.xml > $(DOXYGEN_COMBINED_XML)

$(TEMP_MANIFEST_XML): $(DOXYGEN_TAG_FILE_XML) $(DOXYGEN_COMBINED_XML)
	@echo "Generating Manifest XML..."

	@printf "<lufa-manifest version=\"%s\" tagfile=\"%s\" docfile=\"%s\">\n" $(LUFA_VERSION_NUM) $(DOXYGEN_TAG_FILE_XML) $(DOXYGEN_COMBINED_XML) > $@
	@for i in $(XML_FILES); do \
		printf "\t<xml-source filename=\"%s\"/>\n" $$i >> $@; \
	done;
	@echo '</lufa-manifest>' >> $@

	@echo "Manifest XML file generated."

$(MODULE_OUTPUT_XML): $(TEMP_MANIFEST_XML)
	@echo "Processing asf.xml file..."
	@xsltproc XDK/lufa_module_transform.xslt $< | xsltproc XDK/lufa_indent_transform.xslt - > $(MODULE_OUTPUT_XML)
	@echo "Atmel Studio asf.xml file generated."

$(EXTENSION_OUTPUT_XML): $(TEMP_MANIFEST_XML)
	@echo "Processing extension.xml file..."
	@xsltproc XDK/lufa_extension_transform.xslt $< | xsltproc XDK/lufa_indent_transform.xslt - > $(EXTENSION_OUTPUT_XML)
	@echo "Atmel Studio extension.xml file generated."


generate_xml: $(EXTENSION_OUTPUT_XML) $(MODULE_OUTPUT_XML)

generate_vsix: $(EXTENSION_OUTPUT_XML) $(MODULE_OUTPUT_XML)
	@echo "Cleaning all Projects..."
	@make -C $(LUFA_ROOT)/../ clean

	@echo "Generating ASF cache files..."
	@rm -f $(LUFA_ROOT)/../content.xml.cache
	@rm -f $(LUFA_ROOT)/../ExampleProjects.xml
	@python VSIX/generate_caches.py $(LUFA_ROOT)/../

	@echo "Archiving Content..."
	@rm -f contents.zip
	@cd $(LUFA_ROOT)/../ && zip contents.zip -q -0 -r --exclude=*Documentation* --exclude=*StudioIntegration* LUFA Bootloaders Demos Projects README.txt

	@echo "Creating VSIX Dependencies..."
	@cp $(VSIX_ASSETS) $(LUFA_ROOT)/..
	@xsltproc --stringparam extension-version "$(EXT_VERSION_NUM)" VSIX/lufa_vsmanifest_transform.xslt VSIX/extension.vsixmanifest > $(LUFA_ROOT)/../extension.vsixmanifest
	@xsltproc --stringparam lufa-version "$(LUFA_VERSION_NUM)" VSIX/lufa_asfmanifest_transform.xslt VSIX/asf-manifest.xml > $(LUFA_ROOT)/../asf-manifest.xml

	@echo "Generating Atmel Studio VSIX Extension file..."
	cd $(LUFA_ROOT)/../ && zip $(EXT_VSIX_NAME) -q -9 contents.zip exampleProjects.xml content.xml.cache extension.vsixmanifest asf-manifest.xml extension.xml $(notdir $(VSIX_ASSETS))
	@echo "Atmel Studio VSIX Extension file generated."

check_filenames: $(MODULE_OUTPUT_XML)
	@echo Verifying referenced filenames of ASF.xml modules...
	@for f in `find $(LUFA_ROOT)/../ -name "asf.xml"`; do \
		echo "Checking $$f..."; \
		asf_file_dir=`dirname $$f`; \
		xsltproc XDK/lufa_filelist_transform.xslt $$f | sed -e "/^$$/d" | while read -r i; do \
			if ( ! test -f "$$asf_file_dir/$$i" ); then \
				echo "Source file \"$$i\" referenced in $$f does not exist!"; \
				exit 1; \
			fi; \
		done || exit 1; \
	done;
	@echo Verified referenced filenames of ASF.xml modules.

sanity_check:
	python ProjectGenerator/project_generator.py -b $(LUFA_ROOT)/../ --main-ext-uuid=0e160d5c-e331-48d9-850b-e0387912171b CHECK

.PHONY: all clean generate_xml generate_vsix check_filenames
