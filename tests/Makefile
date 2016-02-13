CC = gcc
CFLAGS	= 
INCLUDES = -I.
LDFLAGS = -L$(BUILDDIR)/cgreen/build-c/src -shared
LDLIBS = -lcgreen
UNITOBJ = $(BUILDDIR)/serialtest/unitobj
DEPDIR = $(BUILDDIR)/serialtest/unit.d
UNITTESTS = $(BUILDDIR)/serialtest/unittests
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
EXT = .so
UNAME := $(shell uname)
ifneq (, $(findstring MINGW, $(UNAME)))
	EXT = .dll
endif
ifneq (, $(findstring CYGWIN, $(UNAME)))
	EXT = .dll
endif
	
SRC = $(wildcard *.c)
TESTFILES = $(patsubst %.c, $(UNITTESTS)/%$(EXT), $(SRC))
$(shell mkdir -p $(DEPDIR) >/dev/null)

test: $(TESTFILES)
	@$(BUILDDIR)/cgreen/build-c/tools/cgreen-runner --color $(TESTFILES)

$(UNITTESTS)/%$(EXT): $(UNITOBJ)/%.o
	mkdir -p $(UNITTESTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(UNITOBJ)/%.o : %.c
$(UNITOBJ)/%.o: %.c $(DEPDIR)/%.d
	mkdir -p $(UNITOBJ)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d
	
$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRC).c))