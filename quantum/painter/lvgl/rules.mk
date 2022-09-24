# LVGL Integration

OPT_DEFS += -DQUANTUM_PAINTER_LVGL_INTEGRATION_ENABLE
DEFERRED_EXEC_ENABLE := yes

LVGL_DIR_NAME = lvgl
LVGL_DIR = $(LIB_DIR)
LVGL_PATH = $(LVGL_DIR)/$(LVGL_DIR_NAME)

ifeq ($(strip $(QUANTUM_PAINTER_LVGL_USE_CUSTOM_CONF)), yes)
	OPT_DEFS += -DLV_CONF_INCLUDE_SIMPLE
	OPT_DEFS += -DQUANTUM_PAINTER_LVGL_USE_CUSTOM_CONF
endif

COMMON_VPATH += \
                $(QUANTUM_DIR)/painter/$(LVGL_DIR_NAME) \
                $(LVGL_PATH)

SRC += $(QUANTUM_DIR)/painter/$(LVGL_DIR_NAME)/qp_lvgl.c
SRC += $(shell find $(LVGL_PATH)/src -type f -name '*.c')
CFLAGS += "-I$(LVGL_PATH)"

# Fix this: Should include their makefile

# include $(LVGL_PATH)/src/extra/extra.mk
# include $(LVGL_PATH)/src/core/lv_core.mk
# include $(LVGL_PATH)/src/draw/lv_draw.mk
# include $(LVGL_PATH)/src/draw/sw/lv_draw_sw.mk
# include $(LVGL_PATH)/src/font/lv_font.mk
# include $(LVGL_PATH)/src/hal/lv_hal.mk
# include $(LVGL_PATH)/src/misc/lv_misc.mk
# include $(LVGL_PATH)/src/widgets/lv_widgets.mk
