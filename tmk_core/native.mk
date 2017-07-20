SYSTEM_TYPE := $(shell gcc -dumpmachine)

CC = gcc
OBJCOPY = 
OBJDUMP = 
SIZE = 
AR = 
NM = 
HEX = 
EEP = 
BIN =


COMPILEFLAGS += -funsigned-char
COMPILEFLAGS += -funsigned-bitfields
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fshort-enums
ifneq ($(findstring mingw, ${SYSTEM_TYPE}),)
COMPILEFLAGS += -mno-ms-bitfields
endif

CFLAGS += $(COMPILEFLAGS)
CFLAGS += -fno-inline-small-functions
CFLAGS += -fno-strict-aliasing

CPPFLAGS += $(COMPILEFLAGS)
CPPFLAGS += -fno-exceptions
CPPFLAGS += -std=gnu++11