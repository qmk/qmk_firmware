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
SRC += $(VISUALIZER_DIR)/lcd_backlight.c
SRC += $(VISUALIZER_DIR)/lcd_keyframes.c
SRC += $(VISUALIZER_DIR)/lcd_backlight_keyframes.c
# Note, that the linker will strip out any resources that are not actually in use
SRC += $(VISUALIZER_DIR)/resources/lcd_logo.c
OPT_DEFS += -DLCD_BACKLIGHT_ENABLE
endif

ifeq ($(strip $(LED_ENABLE)), yes)
SRC += $(VISUALIZER_DIR)/led_keyframes.c
OPT_DEFS += -DLED_ENABLE
endif

include $(GFXLIB)/gfx.mk
GFXSRC := $(patsubst $(TOP_DIR)/%,%,$(GFXSRC))
GFXDEFS := $(patsubst %,-D%,$(patsubst -D%,%,$(GFXDEFS)))

ifneq ("$(wildcard $(KEYMAP_PATH)/visualizer.c)","")
	SRC += keyboards/$(KEYBOARD)/keymaps/$(KEYMAP)/visualizer.c
else 
	ifeq ("$(wildcard $(SUBPROJECT_PATH)/keymaps/$(KEYMAP)/visualizer.c)","")
		ifeq ("$(wildcard $(SUBPROJECT_PATH)/visualizer.c)","")
$(error "$(KEYMAP_PATH)/visualizer.c" does not exist)
		else
			SRC += keyboards/$(KEYBOARD)/$(SUBPROJECT)/visualizer.c
		endif
	else
		SRC += keyboards/$(KEYBOARD)/$(SUBPROJECT)/keymaps/$(KEYMAP)/visualizer.c
	endif
endif

ifdef EMULATOR
UINCDIR += $(TMK_DIR)/common
endif