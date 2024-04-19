# Quantum Painter Configurables
QUANTUM_PAINTER_DRIVERS ?=
QUANTUM_PAINTER_ANIMATIONS_ENABLE ?= yes

QUANTUM_PAINTER_LVGL_INTEGRATION ?= no

# The list of permissible drivers that can be listed in QUANTUM_PAINTER_DRIVERS
VALID_QUANTUM_PAINTER_DRIVERS := \
    surface \
    ili9163_spi \
    ili9341_spi \
    ili9486_spi \
    ili9488_spi \
    st7735_spi \
    st7789_spi \
    gc9a01_spi \
    ssd1351_spi \
    sh1106_i2c \
    sh1106_spi

#-------------------------------------------------------------------------------

OPT_DEFS += -DQUANTUM_PAINTER_ENABLE
COMMON_VPATH += $(QUANTUM_DIR)/painter \
                $(QUANTUM_DIR)/unicode
SRC += \
    $(QUANTUM_DIR)/unicode/utf8.c \
    $(QUANTUM_DIR)/color.c \
    $(QUANTUM_DIR)/painter/qp.c \
    $(QUANTUM_DIR)/painter/qp_internal.c \
    $(QUANTUM_DIR)/painter/qp_stream.c \
    $(QUANTUM_DIR)/painter/qgf.c \
    $(QUANTUM_DIR)/painter/qff.c \
    $(QUANTUM_DIR)/painter/qp_draw_core.c \
    $(QUANTUM_DIR)/painter/qp_draw_codec.c \
    $(QUANTUM_DIR)/painter/qp_draw_circle.c \
    $(QUANTUM_DIR)/painter/qp_draw_ellipse.c \
    $(QUANTUM_DIR)/painter/qp_draw_image.c \
    $(QUANTUM_DIR)/painter/qp_draw_text.c

# Check if people want animations... enable the defered exec if so.
ifeq ($(strip $(QUANTUM_PAINTER_ANIMATIONS_ENABLE)), yes)
    DEFERRED_EXEC_ENABLE := yes
    OPT_DEFS += -DQUANTUM_PAINTER_ANIMATIONS_ENABLE
endif

# Comms flags
QUANTUM_PAINTER_NEEDS_COMMS_DUMMY ?= no
QUANTUM_PAINTER_NEEDS_COMMS_SPI ?= no
QUANTUM_PAINTER_NEEDS_COMMS_I2C ?= no

# Handler for each driver
define handle_quantum_painter_driver
    CURRENT_PAINTER_DRIVER := $1

    ifeq ($$(filter $$(strip $$(CURRENT_PAINTER_DRIVER)),$$(VALID_QUANTUM_PAINTER_DRIVERS)),)
        $$(error "$$(CURRENT_PAINTER_DRIVER)" is not a valid Quantum Painter driver)

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),surface)
        QUANTUM_PAINTER_NEEDS_SURFACE := yes

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),ili9163_spi)
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_ILI9163_ENABLE -DQUANTUM_PAINTER_ILI9163_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/tft_panel \
            $(DRIVER_PATH)/painter/ili9xxx
        SRC += \
            $(DRIVER_PATH)/painter/tft_panel/qp_tft_panel.c \
            $(DRIVER_PATH)/painter/ili9xxx/qp_ili9163.c \

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),ili9341_spi)
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_ILI9341_ENABLE -DQUANTUM_PAINTER_ILI9341_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/tft_panel \
            $(DRIVER_PATH)/painter/ili9xxx
        SRC += \
            $(DRIVER_PATH)/painter/tft_panel/qp_tft_panel.c \
            $(DRIVER_PATH)/painter/ili9xxx/qp_ili9341.c \

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),ili9486_spi)
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_ILI9486_ENABLE -DQUANTUM_PAINTER_ILI9486_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/tft_panel \
            $(DRIVER_PATH)/painter/ili9xxx
        SRC += \
            $(DRIVER_PATH)/painter/tft_panel/qp_tft_panel.c \
            $(DRIVER_PATH)/painter/ili9xxx/qp_ili9486.c \

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),ili9488_spi)
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_ILI9488_ENABLE -DQUANTUM_PAINTER_ILI9488_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/tft_panel \
            $(DRIVER_PATH)/painter/ili9xxx
        SRC += \
            $(DRIVER_PATH)/painter/tft_panel/qp_tft_panel.c \
            $(DRIVER_PATH)/painter/ili9xxx/qp_ili9488.c \

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),st7735_spi)
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_ST7735_ENABLE -DQUANTUM_PAINTER_ST7735_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/tft_panel \
            $(DRIVER_PATH)/painter/st77xx
        SRC += \
            $(DRIVER_PATH)/painter/tft_panel/qp_tft_panel.c \
            $(DRIVER_PATH)/painter/st77xx/qp_st7735.c

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),st7789_spi)
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_ST7789_ENABLE -DQUANTUM_PAINTER_ST7789_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/tft_panel \
            $(DRIVER_PATH)/painter/st77xx
        SRC += \
            $(DRIVER_PATH)/painter/tft_panel/qp_tft_panel.c \
            $(DRIVER_PATH)/painter/st77xx/qp_st7789.c

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),gc9a01_spi)
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_GC9A01_ENABLE -DQUANTUM_PAINTER_GC9A01_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/tft_panel \
            $(DRIVER_PATH)/painter/gc9a01
        SRC += \
            $(DRIVER_PATH)/painter/tft_panel/qp_tft_panel.c \
            $(DRIVER_PATH)/painter/gc9a01/qp_gc9a01.c

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),ssd1351_spi)
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_SSD1351_ENABLE -DQUANTUM_PAINTER_SSD1351_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/tft_panel \
            $(DRIVER_PATH)/painter/ssd1351
        SRC += \
            $(DRIVER_PATH)/painter/tft_panel/qp_tft_panel.c \
            $(DRIVER_PATH)/painter/ssd1351/qp_ssd1351.c

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),sh1106_spi)
        QUANTUM_PAINTER_NEEDS_SURFACE := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI := yes
        QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET := yes
        OPT_DEFS += -DQUANTUM_PAINTER_SH1106_ENABLE -DQUANTUM_PAINTER_SH1106_SPI_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/oled_panel \
            $(DRIVER_PATH)/painter/sh1106
        SRC += \
            $(DRIVER_PATH)/painter/oled_panel/qp_oled_panel.c \
            $(DRIVER_PATH)/painter/sh1106/qp_sh1106.c

    else ifeq ($$(strip $$(CURRENT_PAINTER_DRIVER)),sh1106_i2c)
        QUANTUM_PAINTER_NEEDS_SURFACE := yes
        QUANTUM_PAINTER_NEEDS_COMMS_I2C := yes
        OPT_DEFS += -DQUANTUM_PAINTER_SH1106_ENABLE -DQUANTUM_PAINTER_SH1106_I2C_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/painter/oled_panel \
            $(DRIVER_PATH)/painter/sh1106
        SRC += \
            $(DRIVER_PATH)/painter/oled_panel/qp_oled_panel.c \
            $(DRIVER_PATH)/painter/sh1106/qp_sh1106.c

    endif
endef

# Iterate through the listed drivers for the build, including what's necessary
$(foreach qp_driver,$(QUANTUM_PAINTER_DRIVERS),$(eval $(call handle_quantum_painter_driver,$(qp_driver))))

# If a surface is needed, set up the required files
ifeq ($(strip $(QUANTUM_PAINTER_NEEDS_SURFACE)), yes)
    QUANTUM_PAINTER_NEEDS_COMMS_DUMMY := yes
    OPT_DEFS += -DQUANTUM_PAINTER_SURFACE_ENABLE
    COMMON_VPATH += \
        $(DRIVER_PATH)/painter/generic
    SRC += \
        $(DRIVER_PATH)/painter/generic/qp_surface_common.c \
        $(DRIVER_PATH)/painter/generic/qp_surface_mono1bpp.c \
        $(DRIVER_PATH)/painter/generic/qp_surface_rgb565.c
endif

# If dummy comms is needed, set up the required files
ifeq ($(strip $(QUANTUM_PAINTER_NEEDS_COMMS_DUMMY)), yes)
    OPT_DEFS += -DQUANTUM_PAINTER_DUMMY_COMMS_ENABLE
    VPATH += $(DRIVER_PATH)/painter/comms
    SRC += \
        $(QUANTUM_DIR)/painter/qp_comms.c \
        $(DRIVER_PATH)/painter/comms/qp_comms_dummy.c
endif

# If SPI comms is needed, set up the required files
ifeq ($(strip $(QUANTUM_PAINTER_NEEDS_COMMS_SPI)), yes)
    OPT_DEFS += -DQUANTUM_PAINTER_SPI_ENABLE
    SPI_DRIVER_REQUIRED = yes
    VPATH += $(DRIVER_PATH)/painter/comms
    SRC += \
        $(QUANTUM_DIR)/painter/qp_comms.c \
        $(DRIVER_PATH)/painter/comms/qp_comms_spi.c

    ifeq ($(strip $(QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET)), yes)
        OPT_DEFS += -DQUANTUM_PAINTER_SPI_DC_RESET_ENABLE
    endif
endif

# If I2C comms is needed, set up the required files
ifeq ($(strip $(QUANTUM_PAINTER_NEEDS_COMMS_I2C)), yes)
    OPT_DEFS += -DQUANTUM_PAINTER_I2C_ENABLE
    I2C_DRIVER_REQUIRED = yes
    VPATH += $(DRIVER_PATH)/painter/comms
    SRC += \
        $(QUANTUM_DIR)/painter/qp_comms.c \
        $(DRIVER_PATH)/painter/comms/qp_comms_i2c.c
endif

# Check if LVGL needs to be enabled
ifeq ($(strip $(QUANTUM_PAINTER_LVGL_INTEGRATION)), yes)
    include $(QUANTUM_DIR)/painter/lvgl/rules.mk
endif
