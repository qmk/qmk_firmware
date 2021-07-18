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

define ADD_DRIVER
    $(1)_DRIVER:=$(strip $($(1)_DRIVER))
    $(1)_WIDTH:=$(strip $($(1)_WIDTH))
    $(1)_HEIGHT:=$(strip $($(1)_HEIGHT))
    ifeq ($($(1)_DRIVER),)
        $$(error $(1)_DRIVER is not defined)
    endif
    ifeq ($($(1)_WIDTH),)
        $$(error $(1)_WIDTH is not defined)
    endif
    ifeq ($($(1)_HEIGHT),)
        $$(error $(1)_HEIGHT is not defined)
    endif
    OPT_DEFS+=-D$(1)_WIDTH=$($(1)_WIDTH)
    OPT_DEFS+=-D$(1)_HEIGHT=$($(1)_HEIGHT)
    GFXDEFS+=-D$(1)_WIDTH=$($(1)_WIDTH)
    GFXDEFS+=-D$(1)_HEIGHT=$($(1)_HEIGHT)
    $(1)_DISPLAY_NUMBER:=$$(words $$(GDISP_DRIVER_LIST))
    OPT_DEFS+=-D$(1)_DISPLAY_NUMBER=$$($(1)_DISPLAY_NUMBER)
    include $(TOP_DIR)/drivers/ugfx/gdisp/$($(1)_DRIVER)/driver.mk
endef

GDISP_DRIVER_LIST:=

SRC += $(VISUALIZER_DIR)/visualizer.c \
	$(VISUALIZER_DIR)/visualizer_keyframes.c
EXTRAINCDIRS += $(GFXINC) $(VISUALIZER_DIR)
GFXLIB = $(LIB_PATH)/ugfx
VPATH += $(VISUALIZER_PATH)

OPT_DEFS += -DVISUALIZER_ENABLE

ifdef LCD_ENABLE
OPT_DEFS += -DLCD_ENABLE
ULIBS += -lm
endif

ifeq ($(strip $(LCD_ENABLE)), yes)
    SRC += $(VISUALIZER_DIR)/lcd_keyframes.c
    ifeq ($(strip $(LCD_BACKLIGHT_ENABLE)), yes)
        OPT_DEFS += -DLCD_BACKLIGHT_ENABLE
        SRC += $(VISUALIZER_DIR)/lcd_backlight.c
        SRC += $(VISUALIZER_DIR)/lcd_backlight_keyframes.c
    endif
# Note, that the linker will strip out any resources that are not actually in use
SRC += $(VISUALIZER_DIR)/resources/lcd_logo.c
$(eval $(call ADD_DRIVER,LCD))
endif

ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
SRC += $(VISUALIZER_DIR)/led_backlight_keyframes.c
$(eval $(call ADD_DRIVER,LED))
endif

SRC += $(VISUALIZER_DIR)/default_animations.c

include $(GFXLIB)/gfx.mk
# For the common_gfxconf.h
GFXINC += quantum/visualizer

GFXSRC := $(patsubst $(TOP_DIR)/%,%,$(GFXSRC))
GFXDEFS := $(patsubst %,-D%,$(patsubst -D%,%,$(GFXDEFS)))

GDISP_LIST_COMMA=,
GDISP_LIST_EMPTY=
GDISP_LIST_SPACE=$(GDISP_LIST_EMPTY) $(GDISP_LIST_EMPTY)

GDISP_DRIVER_LIST := $(strip $(GDISP_DRIVER_LIST))
GDISP_DRIVER_LIST := $(subst $(GDISP_LIST_SPACE),$(GDISP_LIST_COMMA),$(GDISP_DRIVER_LIST))

GFXDEFS +=-DGDISP_DRIVER_LIST="$(GDISP_DRIVER_LIST)"

ifneq ("$(wildcard $(KEYMAP_PATH)/visualizer.c)","")
    SRC += $(KEYMAP_PATH)/visualizer.c
else 
    VISUALIZER_1 := $(KEYBOARD_PATH_1)/visualizer.c
    VISUALIZER_2 := $(KEYBOARD_PATH_2)/visualizer.c
    VISUALIZER_3 := $(KEYBOARD_PATH_3)/visualizer.c
    VISUALIZER_4 := $(KEYBOARD_PATH_4)/visualizer.c
    VISUALIZER_5 := $(KEYBOARD_PATH_5)/visualizer.c

    ifneq ("$(wildcard $(VISUALIZER_5))","")
        SRC += $(VISUALIZER_5)
    endif
    ifneq ("$(wildcard $(VISUALIZER_4))","")
        SRC += $(VISUALIZER_4)
    endif
    ifneq ("$(wildcard $(VISUALIZER_3))","")
        SRC += $(VISUALIZER_3)
    endif
    ifneq ("$(wildcard $(VISUALIZER_2))","")
        SRC += $(VISUALIZER_2)
    endif
    ifneq ("$(wildcard $(VISUALIZER_1))","")
        SRC += $(VISUALIZER_1)
    endif
endif

ifdef EMULATOR
UINCDIR += $(TMK_DIR)/common
endif
