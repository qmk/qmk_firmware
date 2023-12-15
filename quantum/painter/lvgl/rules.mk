# LVGL Integration

OPT_DEFS += -DQUANTUM_PAINTER_LVGL_INTEGRATION_ENABLE -DLV_CONF_INCLUDE_SIMPLE
DEFERRED_EXEC_ENABLE := yes

LVGL_DIR_NAME = lvgl
LVGL_DIR = $(LIB_DIR)
LVGL_PATH = $(LVGL_DIR)/$(LVGL_DIR_NAME)

COMMON_VPATH += $(PLATFORM_PATH) \
                $(QUANTUM_DIR)/painter/$(LVGL_DIR_NAME) \
                $(LVGL_PATH)

include $(LVGL_PATH)/src/extra/extra.mk
include $(LVGL_PATH)/src/core/lv_core.mk
include $(LVGL_PATH)/src/draw/lv_draw.mk
include $(LVGL_PATH)/src/draw/sw/lv_draw_sw.mk
include $(LVGL_PATH)/src/font/lv_font.mk
include $(LVGL_PATH)/src/hal/lv_hal.mk
include $(LVGL_PATH)/src/misc/lv_misc.mk
include $(LVGL_PATH)/src/widgets/lv_widgets.mk

SRC += qp_lvgl.c \
       $(CSRCS)
