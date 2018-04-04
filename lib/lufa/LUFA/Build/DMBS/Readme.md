DMBS - Dean's Makefile Build System
===================================


Project Overview
----------------

GNU Make is scary, and it's tough to get the rules right sometimes. Many
projects get by via simple copy-pasting of old makefiles, resulting in many
redundant copies of the same old rules. DMBS aims to solve this by providing a
simple modular set of makefiles which can be included by your project to quickly
add various build functionality.

This aims to replace the old WinAVR "mfile" makefile template, giving better
functionality and much simpler user makefiles.


Benefits:
----------------

Apart from much simpler, cleaner makefiles DMBS carries the aim of making the
process of troubleshooting build issues a little easier. Lots can go wrong, so
DMBS tries to sanity check its inputs wherever possible, and produce
human-readable error messages. Forgotten to set a variable? Get a
`Makefile {X} value not set.` message, rather than a possibly unrelated message.
Have the wrong filename? See `Source file does not exist: {X}` rather than the
infamous `No rule to make target {X}` message.


Use:
----------------

A template user makefile is provided in the `Template` directory. DMBS modules
are included via a GNU Make `include` directive. While the DMBS `core` module is
always required, you can pick and choose what other modules you wish to add to
your user project.

[See here for the documentation on the individual modules provided by DMBS.](DMBS/ModulesOverview.md)
If you're interested in writing your own DMBS module(s), [see here.](DMBS/WritingYourOwnModules.md)

Here's an example user makefile:

	MCU          = atmega128
	ARCH         = AVR8
	F_CPU        = 8000000
	OPTIMIZATION = s
	TARGET       = Template
	SRC          = $(TARGET).c
	CC_FLAGS     =
	LD_FLAGS     =

	# Default target
	all:

	# Include DMBS build script makefiles
	DMBS_PATH   ?= ../DMBS
	include $(DMBS_PATH)/core.mk
	include $(DMBS_PATH)/gcc.mk
	include $(DMBS_PATH)/cppcheck.mk
	include $(DMBS_PATH)/doxygen.mk
	include $(DMBS_PATH)/dfu.mk
	include $(DMBS_PATH)/hid.mk
	include $(DMBS_PATH)/avrdude.mk
	include $(DMBS_PATH)/atprogram.mk

Each DMBS module can optionally supply one or more Make variables and macros,
which you can reference in your user makefile. Additionally, modules can require
one or more variables to be set by the user makefile, with (in some cases) sane
defaults used if left out.

As modules are added, you can get a list of available targets by simply typing
`make help` from the command line. This will produce a formatted list of targets
as well as mandatory and optional variables and exposed variables and macros.


Distribution
----------------

You can embed DMBS in your project any way you like - some options are:
1. A git submodule
2. A source tarball
3. A manually copied extracted archive

The intention of DMBS is that users can just import it from whatever source
they like. If your project needs to extend the existing modules in an unusual
manner, or if you want to provide your own modules, you can include them in
your project repository (or submit a patch to DMBS if your module is generic
enough to warrant wide use).


License
----------------

DMBS is released into the public domain, making is suitable for use everywhere,
by everyone. Contributions are greatly appreciated however, in order to make
DMBS better for everyone.

The actual license text is as follows:

	This is free and unencumbered software released into the public domain.

	Anyone is free to copy, modify, publish, use, compile, sell, or
	distribute this software, either in source code form or as a compiled
	binary, for any purpose, commercial or non-commercial, and by any
	means.

	In jurisdictions that recognize copyright laws, the author or authors
	of this software dedicate any and all copyright interest in the
	software to the public domain. We make this dedication for the benefit
	of the public at large and to the detriment of our heirs and
	successors. We intend this dedication to be an overt act of
	relinquishment in perpetuity of all present and future rights to this
	software under copyright law.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.

	For more information, please refer to <http://unlicense.org/>
