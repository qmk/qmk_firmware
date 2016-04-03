DMBS - Dean's Makefile Build System
===================================


Modules Overview
---------------

The following modules are currently included:

 - [ATPROGRAM](atprogram.md) - Device Programming
 - [AVRDUDE](avrdude.md) - Device Programming
 - [CORE](core.md) - DMBS Core Functionality
 - [CPPCHECK](cppcheck.md) - Static Code Analysis
 - [DFU](dfu.md) - Device Programming
 - [DOXYGEN](doxygen.md) - Automated Source Code Documentation
 - [GCC](gcc.md) - Compiling/Assembling/Linking with GCC
 - [HID](hid.md) - Device Programming

To use a module, you will need to add the following boilerplate to your
makefile:

    # Include DMBS build script makefiles
    DMBS_PATH   ?= ../DMBS

Which is then used to indicate the location of your DMBS installation, relative
to the current directory.
