COLOR ?= true

ifeq ($(COLOR),true)
	NO_COLOR=\033[0m
	OK_COLOR=\033[32;01m
	ERROR_COLOR=\033[31;01m
	WARN_COLOR=\033[33;01m
	BLUE=\033[0;34m
	BOLD=\033[1m
endif

ifneq ($(shell echo "1 2 3" | awk '{ printf "%2s", $$3; }' 2>/dev/null)," 3")
	AWK=awk
else
	AWK=cat && test
endif

ON_ERROR ?= exit 1

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)\n
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)\n
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)\n

TAB_LOG = printf "\n%s\n\n" "$$LOG" | $(AWK) '{ sub(/^/," | "); print }'
TAB_LOG_PLAIN = printf "%s\n" "$$LOG"
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
MSG_FLASH = Creating load file for flashing:
MSG_EEPROM = Creating load file for EEPROM:
MSG_BIN = Creating binary load file for flashing:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_COMPILING_CXX = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:
MSG_SUBMODULE_DIRTY = $(WARN_COLOR)WARNING:$(NO_COLOR)\n \
	Some git sub-modules are out of date or modified, please consider running:$(BOLD)\n\
        make git-submodule\n\
	You can ignore this warning if you are not compiling any ChibiOS keyboards,\n\
	or if you have modified the ChibiOS libraries yourself. \n\n$(NO_COLOR)
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
define GENERATE_MSG_AVAILABLE_KEYMAPS
    MSG_AVAILABLE_KEYMAPS_ACTUAL := Available keymaps for $(BOLD)$$(CURRENT_KB)$(NO_COLOR):
endef
MSG_AVAILABLE_KEYMAPS = $(eval $(call GENERATE_MSG_AVAILABLE_KEYMAPS))$(MSG_AVAILABLE_KEYMAPS_ACTUAL)

MSG_CHECK_FILESIZE = Checking file size of $(TARGET).hex
MSG_FILE_TOO_BIG = $(ERROR_COLOR)The firmware is too large!$(NO_COLOR) $(CURRENT_SIZE)/$(MAX_SIZE) ($(OVER_SIZE) bytes over)\n
MSG_FILE_TOO_SMALL = The firmware is too small! $(CURRENT_SIZE)/$(MAX_SIZE)\n
MSG_FILE_JUST_RIGHT = The firmware size is fine - $(CURRENT_SIZE)/$(MAX_SIZE) ($(PERCENT_SIZE)%%, $(FREE_SIZE) bytes free)\n
MSG_FILE_NEAR_LIMIT = The firmware size is approaching the maximum - $(CURRENT_SIZE)/$(MAX_SIZE) ($(PERCENT_SIZE)%%, $(FREE_SIZE) bytes free)\n
MSG_PYTHON_MISSING = $(WARN_COLOR)WARNING:$(NO_COLOR)\n \
	Python 3 is not installed. It will be required by a future version\n\
	of qmk_firmware.\n\n\
	Please run $(BOLD)util/qmk_install.sh$(NO_COLOR) to install all the dependencies QMK requires.\n\n
MSG_FLASH_BOOTLOADER = $(WARN_COLOR)WARNING:$(NO_COLOR) This board's bootloader is not specified or is not supported by the \":flash\" target at this time.\n\n
MSG_FLASH_ARCH = $(WARN_COLOR)WARNING:$(NO_COLOR) This board's architecture is not supported by the \":flash\" target at this time.\n\n
MSG_BOOTLOADER_NOT_FOUND = $(ERROR_COLOR)ERROR:$(NO_COLOR) Bootloader not found. Trying again in 5s.\n
