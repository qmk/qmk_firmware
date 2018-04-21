DMBS - Dean's Makefile Build System
===================================


Modules Overview
----------------

The following modules are currently included:

 - [ATPROGRAM](atprogram.md) - Device Programming
 - [AVRDUDE](avrdude.md) - Device Programming
 - [CORE](core.md) - DMBS Core Functionality
 - [CPPCHECK](cppcheck.md) - Static Code Analysis
 - [DFU](dfu.md) - Device Programming
 - [DOXYGEN](doxygen.md) - Automated Source Code Documentation
 - [GCC](gcc.md) - Compiling/Assembling/Linking with GCC
 - [HID](hid.md) - Device Programming

## Importing modules into your project makefile

To use a module, it is recommended to add the following boilerplate to your
makefile:

    # Include DMBS build script makefiles
    DMBS_PATH   ?= ../DMBS

Which can then used to indicate the location of your DMBS installation, relative
to the current directory, when importing modules. For example:

    DMBS_PATH   ?= ../DMBS
    include $(DMBS_PATH)/core.mk
    include $(DMBS_PATH)/gcc.mk

Imports the `CORE` and `GCC` modules from DMBS using a single path relative to
your project's makefile.

If you wish to write your own DMBS module(s),
[see the documentation here for more details.](WritingYourOwnModules.md)
