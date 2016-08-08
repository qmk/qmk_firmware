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

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)\n
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)\n
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)\n

ifndef $(SILENT)
	SILENT = false
endif

TAB_LOG = printf "\n$$LOG\n\n" | $(AWK) '{ sub(/^/," | "); print }'
TAB_LOG_PLAIN = printf "$$LOG\n"
AWK_STATUS = $(AWK) '{ printf " %-10s\n", $$1; }'
AWK_CMD = $(AWK) '{ printf "%-99s", $$0; }'
PRINT_ERROR = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG) && exit 1
PRINT_WARNING = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG)
PRINT_ERROR_PLAIN = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN) && exit 1
PRINT_WARNING_PLAIN = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN)
PRINT_OK = $(SILENT) || printf " $(OK_STRING)" | $(AWK_STATUS)
BUILD_CMD = LOG=$$($(CMD) 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING); else $(PRINT_OK); fi;
MSG_NO_CMP = $(ERROR_COLOR)Error:$(NO_COLOR)$(BOLD) cmp command not found, please install diffutils\n$(NO_COLOR)