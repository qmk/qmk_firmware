CC = gcc
CFLAGS	= 
INCLUDES = -I.
LDFLAGS = -L$(BUILDDIR)/cgreen/build-c/src
LDLIBS = -lcgreen
UNITOBJ = $(BUILDDIR)/testserial/unitobj
DEPDIR = $(BUILDDIR)/testserial/unit.d
UNITEXE = $(BUILDDIR)/testserial/unitexe
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
EXT = 
UNAME := $(shell uname)
ifneq (, $(findstring mingw, $(UNAME)))
	EXT += exe
endif
ifneq (, $(findstring cygwin, $(UNAME)))
	EXT += exe
endif
	
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, $(UNITEXE)/%$(EXT), $(SRC))
$(shell mkdir -p $(DEPDIR) >/dev/null)

test: $(EXE)
	@for f in $^; do \
	echo "++++++++++++++++++"; \
	echo "Running unit tests"; \
	echo $$(basename $$f); \
	echo "++++++++++++++++++"; \
	echo ""; \
	$$f || exit 1; \
	echo ""; \
	echo "******************"; \
	echo ""; \
	done

$(UNITEXE)/%$(EXT): $(UNITOBJ)/%.o
	mkdir -p $(UNITEXE)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(UNITOBJ)/%.o : %.c
$(UNITOBJ)/%.o: %.c $(DEPDIR)/%.d
	mkdir -p $(UNITOBJ)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d
	
$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRC).c))