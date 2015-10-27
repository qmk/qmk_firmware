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

ifneq ($(LUFA_VERSION_NUM),000000)
  EXT_VERSION_NUM    := $(shell date +"%y.%m.%d").$(LUFA_VERSION_NUM)
  EXT_VSIX_NAME      := LUFA-RELEASE-$(LUFA_VERSION_NUM).vsix
else
  EXT_VERSION_NUM    := 0.$(shell date +"%y%m%d.%H%M%S")
  EXT_VSIX_NAME      := LUFA-TESTING-$(shell date +"%y.%m.%d-%H.%M.%S").vsix

  $(warning No LUFA version set - assuming a test version should be created.)
endif

DOXYGEN_TAG_FILE_XML := $(LUFA_ROOT)/Documentation/lufa_doc_tags.xml
DOXYGEN_COMBINED_XML := $(LUFA_ROOT)/Documentation/xml/lufa_doc.xml
TEMP_MANIFEST_XML    := manifest.xml
EXTENSION_OUTPUT_XML := $(LUFA_ROOT)/../extension.xml
MODULE_OUTPUT_XML    := $(LUFA_ROOT)/asf.xml
MSHELP_OUTPUT_XML    := $(LUFA_ROOT)/../lufa_help_$(EXT_VERSION_NUM).mshc
XML_FILES            := $(filter-out $(TEMP_MANIFEST_FILE), $(shell ls *.xml))
VSIX_ASSETS          := $(LUFA_ROOT)/DoxygenPages/Images/LUFA_thumb.png     \
                        $(LUFA_ROOT)/DoxygenPages/Images/LUFA.png           \
                        $(LUFA_ROOT)/License.txt                            \
                        VSIX/"[Content_Types].xml"                          \
                        VSIX/LUFA.dll                                       \
                        VSIX/LUFA.pkgdef
VSIX_GEN_PARAMS     := --stringparam extension-version "$(EXT_VERSION_NUM)" \
                       --stringparam lufa-version "$(LUFA_VERSION_NUM)"
MSHELP_GEN_PARAMS   := --stringparam generate.toc "book toc"                \
                       --stringparam chunk.quietly "1"                      \
                       --stringparam chunk.section.depth "3"                \
                       --stringparam chunk.first.sections "1"               \
                       --stringparam chapter.autolabel "0"                  \
                       --stringparam root.filename "LUFA"                   \
                       --stringparam html.stylesheet "lufa_studio_help_styling.css"

all: clear_project_dirs generate_xml check_filenames generate_vsix

clear_project_dirs:
	@make -s -C $(LUFA_ROOT)/.. clean

clean:
	@rm -f $(TEMP_MANIFEST_XML) $(MODULE_OUTPUT_XML) $(EXTENSION_OUTPUT_XML) $(DOXYGEN_TAG_FILE_XML) $(DOXYGEN_COMBINED_XML) $(MSHELP_OUTPUT_XML)
	@rm -rf mshelp
	@cd $(LUFA_ROOT)/.. && rm -f contents.zip exampleProjects.xml content.xml.cache extension.vsixmanifest asf-manifest.xml extension.xml helpcontentsetup.msha $(notdir $(VSIX_ASSETS)) *.vsix *.mshc

$(DOXYGEN_TAG_FILE_XML):
	@$(MAKE) -C ../ doxygen DOXYGEN_OVERRIDE_PARAMS="GENERATE_TAGFILE=Documentation/lufa_doc_tags.xml GENERATE_HTML=no GENERATE_XML=yes"

$(DOXYGEN_COMBINED_XML): $(DOXYGEN_TAG_FILE_XML)
	@xsltproc $(dir $@)/combine.xslt $(dir $@)/index.xml > $(DOXYGEN_COMBINED_XML)

$(TEMP_MANIFEST_XML): $(DOXYGEN_TAG_FILE_XML) $(DOXYGEN_COMBINED_XML)
	@echo Generating temporary module manifest XML...

	@printf "<lufa-manifest version=\"%s\" tagfile=\"%s\" docfile=\"%s\">\n" $(LUFA_VERSION_NUM) $(DOXYGEN_TAG_FILE_XML) $(DOXYGEN_COMBINED_XML) > $@
	@for i in $(XML_FILES); do \
		printf "\t<xml-source filename=\"%s\"/>\n" $$i >> $@; \
	done;
	@echo '</lufa-manifest>' >> $@

$(MODULE_OUTPUT_XML): $(TEMP_MANIFEST_XML)
	@echo Generating library core XDK module manifest file...
	@xsltproc XDK/lufa_module_transform.xslt $< | xsltproc XDK/lufa_indent_transform.xslt - > $(MODULE_OUTPUT_XML)

$(EXTENSION_OUTPUT_XML): $(TEMP_MANIFEST_XML)
	@echo Generating library XDK extension manifest file...
	@xsltproc XDK/lufa_extension_transform.xslt $< | xsltproc XDK/lufa_indent_transform.xslt - > $(EXTENSION_OUTPUT_XML)

$(MSHELP_OUTPUT_XML): $(DOXYGEN_COMBINED_XML)
	@echo Converting Doxygen XML to DocBook...
	@-mkdir mshelp 2> /dev/null
	@xsltproc HV1/lufa_docbook_transform.xslt $(DOXYGEN_COMBINED_XML) > mshelp/lufa_docbook.xml

	@echo Converting DocBook XML to Microsoft Help 1.0...
	@cd mshelp && xsltproc $(MSHELP_GEN_PARAMS) ../HV1/lufa_hv1_transform.xslt lufa_docbook.xml

	@echo Copying help assets...
	@cp HV1/lufa_studio_help_styling.css mshelp
	@-mkdir mshelp/images 2> /dev/null
	@cp `find $(LUFA_ROOT)/DoxygenPages/Images -type f` mshelp/images

	@echo Archiving help content...
	@cd mshelp && zip ../$(MSHELP_OUTPUT_XML) -q -0  -r *.html *.css images

	@echo Generating HV1 manifest...
	@xsltproc $(VSIX_GEN_PARAMS) HV1/lufa_helpcontentsetup_transform.xslt HV1/helpcontentsetup.msha > $(LUFA_ROOT)/../helpcontentsetup.msha

generate_help: $(MSHELP_OUTPUT_XML)

generate_xml: $(EXTENSION_OUTPUT_XML) $(MODULE_OUTPUT_XML)

generate_vsix: $(EXTENSION_OUTPUT_XML) $(MODULE_OUTPUT_XML) $(MSHELP_OUTPUT_XML)
	@echo Generating XDK cache files...
	@rm -f $(LUFA_ROOT)/../content.xml.cache
	@rm -f $(LUFA_ROOT)/../ExampleProjects.xml
	@python VSIX/generate_caches.py $(LUFA_ROOT)/../

	@echo Archiving XDK content...
	@rm -f contents.zip
	@cd $(LUFA_ROOT)/../ && zip contents.zip -q -0 -r --exclude=*Documentation* --exclude=*StudioIntegration* LUFA Bootloaders Demos Projects README.txt

	@echo Creating VSIX dependencies...
	@cp $(VSIX_ASSETS) $(LUFA_ROOT)/..
	@xsltproc $(VSIX_GEN_PARAMS) VSIX/lufa_vsmanifest_transform.xslt VSIX/extension.vsixmanifest > $(LUFA_ROOT)/../extension.vsixmanifest
	@xsltproc $(VSIX_GEN_PARAMS) VSIX/lufa_asfmanifest_transform.xslt VSIX/asf-manifest.xml > $(LUFA_ROOT)/../asf-manifest.xml

	@echo Generating Atmel Studio VSIX file...
	cd $(LUFA_ROOT)/../ && zip $(EXT_VSIX_NAME) -q -9 contents.zip exampleProjects.xml content.xml.cache extension.vsixmanifest asf-manifest.xml extension.xml helpcontentsetup.msha $(notdir $(MSHELP_OUTPUT_XML)) $(notdir $(VSIX_ASSETS))

	@echo "Atmel Studio VSIX extension file generated."

check_filenames: $(MODULE_OUTPUT_XML)
	@echo Verifying referenced filenames of XDK modules...
	@for f in `find $(LUFA_ROOT)/../ -name "asf.xml"`; do \
		echo "Checking $$f..."; \
		asf_file_dir=`dirname $$f`; \
		xsltproc XDK/lufa_filelist_transform.xslt $$f | sed -e "/^$$/d" | while read -r i; do \
			if ( ( ! test -f "$$asf_file_dir/$$i" ) && ( ! test -d "$$asf_file_dir/$$i" ) ); then \
				echo "Source file \"$$i\" referenced in $$f does not exist!"; \
				exit 1; \
			fi; \
		done || exit 1; \
	done;

check_database:
	python ProjectGenerator/project_generator.py -b $(LUFA_ROOT)/../ --main-ext-uuid=0e160d5c-e331-48d9-850b-e0387912171b CHECK

.PHONY: all clean generate_help generate_xml generate_vsix check_filenames check_database
