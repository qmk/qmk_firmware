COLOR ?= true

ifeq ($(COLOR),true)
	NO_COLOR=\033[0m
	OK_COLOR=\033[32;01m
	ERROR_COLOR=\033[31;01m
	WARN_COLOR=\033[33;01m
	SKIPPED_COLOR=\033[36;01m
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
SKIPPED_STRING=$(SKIPPED_COLOR)[SKIPPED]$(NO_COLOR)\n

TAB_LOG = printf "\n%s\n\n" "$$LOG" | $(AWK) '{ sub(/^/," | "); print }'
TAB_LOG_PLAIN = printf "%s\n" "$$LOG"
AWK_STATUS = $(AWK) '{ printf " %-10s\n", $$1; }'
AWK_CMD = $(AWK) '{ printf "%-99s", $$0; }'
PRINT_ERROR = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG) && $(ON_ERROR)
PRINT_WARNING = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG)
PRINT_ERROR_PLAIN = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN) && $(ON_ERROR)
PRINT_WARNING_PLAIN = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN)
PRINT_SKIPPED_PLAIN = ($(SILENT) || printf " $(SKIPPED_STRING)" | $(AWK_STATUS))
PRINT_OK = $(SILENT) || printf " $(OK_STRING)" | $(AWK_STATUS)
BUILD_CMD = LOG=$$($(CMD) 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING); else $(PRINT_OK); fi;
MAKE_MSG_FORMAT = $(AWK) '{ printf "%-118s", $$0;}'

# The UNSYNC_OUTPUT_CMD command disables the `--output-sync` for the current command, if the `--output-sync` granularity is `target` or lower.
# This is achieved by telling make to treat the current command as if it invokes a recursive make subcommand (as if by calling `$(MAKE)`).
UNSYNC_OUTPUT_CMD = +true

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
MSG_UF2 = Creating UF2 file for deployment:
MSG_EEPROM = Creating load file for EEPROM:
MSG_BIN = Creating binary load file for flashing:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_EXECUTING = Executing:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_COMPILING_CXX = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:
MSG_GENERATING = Generating:
MSG_NOT_REPO = $(WARN_COLOR)WARNING:$(NO_COLOR) Target folder is not a git repo, you probably downloaded a zip file instead of cloning.\n\
Please consider following $(BOLD)https://docs.qmk.fm/\#/newbs_getting_started$(NO_COLOR).\n\n
MSG_SUBMODULE_DIRTY = $(WARN_COLOR)WARNING:$(NO_COLOR) Some git submodules are out of date or modified.\n\
Please consider running $(BOLD)qmk git-submodule$(NO_COLOR).\n\n

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

MSG_BOOTLOADER_NOT_FOUND_BASE = Bootloader not found. Make sure the board is in bootloader mode. See https://docs.qmk.fm/\#/newbs_flashing\n
MSG_CHECK_FILESIZE = Checking file size of $(TARGET).$(FIRMWARE_FORMAT)
MSG_FILE_TOO_BIG = $(ERROR_COLOR)The firmware is too large!$(NO_COLOR) $(CURRENT_SIZE)/$(MAX_SIZE) ($(OVER_SIZE) bytes over)\n
MSG_FILE_TOO_SMALL = The firmware is too small! $(CURRENT_SIZE)/$(MAX_SIZE)\n
MSG_FILE_JUST_RIGHT = The firmware size is fine - $(CURRENT_SIZE)/$(MAX_SIZE) ($(PERCENT_SIZE)%%, $(FREE_SIZE) bytes free)\n
MSG_FILE_NEAR_LIMIT = The firmware size is approaching the maximum - $(CURRENT_SIZE)/$(MAX_SIZE) ($(PERCENT_SIZE)%%, $(FREE_SIZE) bytes free)\n
MSG_PYTHON_MISSING = $(ERROR_COLOR)ERROR:$(NO_COLOR) Cannot run \"qmk hello\"!\n\n\
	Please run $(BOLD)qmk setup$(NO_COLOR) to install all the dependencies QMK requires.\n\n
MSG_FLASH_BOOTLOADER = $(WARN_COLOR)WARNING:$(NO_COLOR) This board's bootloader is not specified or is not supported by the \":flash\" target at this time.\n\n
MSG_FLASH_ARCH = $(WARN_COLOR)WARNING:$(NO_COLOR) This board's architecture is not supported by the \":flash\" target at this time.\n\n
MSG_BOOTLOADER_NOT_FOUND = $(ERROR_COLOR)ERROR:$(NO_COLOR) $(MSG_BOOTLOADER_NOT_FOUND_BASE) Trying again in 5s (Ctrl+C to cancel)\n
BOOTLOADER_RETRY_TIME ?= 0.5
MSG_BOOTLOADER_NOT_FOUND_QUICK_RETRY = $(MSG_BOOTLOADER_NOT_FOUND_BASE) Trying again every $(BOOTLOADER_RETRY_TIME)s (Ctrl+C to cancel)

define WARNING_MESSAGE
    $(shell printf "\n %-99s $(WARN_STRING)\n" "$1" >&2)
endef

define CATASTROPHIC_ERROR
    $(shell printf "\n * %-99s $(ERROR_STRING)\n" "$2" >&2)
    $(error $1)
endef
