ifndef VERBOSE
.SILENT:
endif

NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
ERROR_COLOR=\033[31;01m
WARN_COLOR=\033[33;01m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

AWK_CMD = awk '{ printf "%-60s %-10s\n",$$1, $$2; }'
PRINT_ERROR = printf "$@ $(ERROR_STRING)\n" | $(AWK_CMD) && false
PRINT_WARNING = printf "$@ $(WARN_STRING)\n" | $(AWK_CMD) 
PRINT_OK = printf "$@ $(OK_STRING)\n" | $(AWK_CMD)
BUILD_CMD = 


SUBDIRS := $(sort $(dir $(wildcard keyboard/planck/keymaps/*/.)))
# $(error $(SUBDIRS))

all: $(SUBDIRS)
$(SUBDIRS): 
	LOG=$$(make -C $@ 2>&1) ; if [ $$? -eq 1 ]; then $(PRINT_ERROR); elif [ "$$LOG" != "" ] ; then $(PRINT_OK); else $(PRINT_OK); fi;

.PHONY: all $(SUBDIRS)