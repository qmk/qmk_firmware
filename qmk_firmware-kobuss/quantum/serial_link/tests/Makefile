# The MIT License (MIT)
#
# Copyright (c) 2016 Fred Sundvik
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC = gcc
CFLAGS	=
INCLUDES = -I. -I../../
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
	@mkdir -p $(UNITTESTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(UNITOBJ)/%.o : %.c
$(UNITOBJ)/%.o: %.c $(DEPDIR)/%.d
	@mkdir -p $(UNITOBJ)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@
	@mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRC)))
