SYSTEM_TYPE := $(shell gcc -dumpmachine)
GCC_VERSION := $(shell gcc --version 2>/dev/null)

CC = $(CC_PREFIX) gcc
OBJCOPY =
OBJDUMP =
SIZE =
AR =
NM =
HEX =
EEP =
BIN =


COMPILEFLAGS += -funsigned-char
ifeq ($(findstring clang, ${GCC_VERSION}),)
COMPILEFLAGS += -funsigned-bitfields
endif
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fshort-enums
ifneq ($(findstring mingw, ${SYSTEM_TYPE}),)
COMPILEFLAGS += -mno-ms-bitfields
endif

CFLAGS += $(COMPILEFLAGS)
ifeq ($(findstring clang, ${GCC_VERSION}),)
CFLAGS += -fno-inline-small-functions
endif
CFLAGS += -fno-strict-aliasing

CXXFLAGS += $(COMPILEFLAGS)
CXXFLAGS += -fno-exceptions
CXXFLAGS += $(CXXSTANDARD)
