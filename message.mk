COLOR ?= true

ifeq ($(COLOR),true)
	NO_COLOR=\033[0m
	OK_COLOR=\033[32;01m
	ERROR_COLOR=\033[31;01m
	WARN_COLOR=\033[33;01m
	BLUE=\033[0;34m
	BOLD=\033[1m
endif

ifneq ($(shell awk --version 2>/dev/null),)
	AWK=awk
else
	AWK=cat && test
endif

ON_ERROR ?= exit 1

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)\n
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)\n
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)\n

TAB_LOG = printf "\n$$LOG\n\n" | $(AWK) '{ sub(/^/," | "); print }'
TAB_LOG_PLAIN = printf "$$LOG\n"
AWK_STATUS = $(AWK) '{ printf " %-10s\n", $$1; }'
AWK_CMD = $(AWK) '{ printf "%-99s", $$0; }'
PRINT_ERROR = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG) && $(ON_ERROR)
PRINT_WARNING = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG)
PRINT_ERROR_PLAIN = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN) && $(ON_ERROR)
PRINT_WARNING_PLAIN = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN)
PRINT_OK = $(SILENT) || printf " $(OK_STRING)" | $(AWK_STATUS)
BUILD_CMD = LOG=$$($(CMD) 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING); else $(PRINT_OK); fi;
MAKE_MSG_FORMAT = $(AWK) '{ printf "%-118s", $$0;}'

# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_ERRORS = $(ERROR_COLOR)Make finished with errors\n$(NO_COLOR)
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_BIN = Creating binary load file for Flash:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_COMPILING_CPP = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:
MSG_SUBMODULE_DIRTY = $(WARN_COLOR)WARNING:$(NO_COLOR)\n \
	Some git sub-modules are out of date or modified, please consider runnning:$(BOLD)\n\
	git submodule sync --recursive\n\
	git submodule update --init --recursive$(NO_COLOR)\n\n\
	You can ignore this warning if you are not compiling any ChibiOS keyboards,\n\
	or if you have modified the ChibiOS libraries yourself. \n\n
MSG_NO_CMP = $(ERROR_COLOR)Error:$(NO_COLOR)$(BOLD) cmp command not found, please install diffutils\n$(NO_COLOR)

define GENERATE_MSG_MAKE_KB
    MSG_MAKE_KB_ACTUAL := Making $$(KB_SP) with keymap $(BOLD)$$(CURRENT_KM)$(NO_COLOR)
    ifneq ($$(MAKE_TARGET),)
        MSG_MAKE_KB_ACTUAL += and target $(BOLD)$$(MAKE_TARGET)$(NO_COLOR)
    endif
endef
MSG_MAKE_KB = $(eval $(call GENERATE_MSG_MAKE_KB))$(MSG_MAKE_KB_ACTUAL)
define GENERATE_MSG_MAKE_TEST
    MSG_MAKE_TEST_ACTUAL := Making test $(BOLD)$(TEST_NAME)$(NO_COLOR)
    ifneq ($$(MAKE_TARGET),)
        MSG_MAKE_TEST_ACTUAL += with target $(BOLD)$$(MAKE_TARGET)$(NO_COLOR)
    endif
endef
MSG_MAKE_TEST = $(eval $(call GENERATE_MSG_MAKE_TEST))$(MSG_MAKE_TEST_ACTUAL)
MSG_TEST = Testing $(BOLD)$(TEST_NAME)$(NO_COLOR)
