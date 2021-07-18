## https://github.com/manna-harbour/qmk_firmware/blob/crkbd/keyboards/crkbd/keymaps/manna-harbour/readme.org

#MH_MODULE=trackpoint
#MH_MODULE=oled
#MH_MODULE=oled_old
MH_MODULE=no

#MH_AUTO_BUTTONS=yes
MH_AUTO_BUTTONS=no

#MH_LOW_MOUSE=yes
MH_LOW_MOUSE=no

#MH_OLED_MODE=static
#MH_OLED_MODE=caps
MH_OLED_MODE=no

#MH_OLED_IMAGE=qmk.c
#MH_OLED_IMAGE=image.c
#MH_OLED_IMAGE=logo
MH_OLED_IMAGE=no

#MH_RGB=matrix
#MH_RGB=backlight
#MH_RGB=underglow
MH_RGB=no

#MH_DEBUG=yes
MH_DEBUG=no

#LTO_ENABLE=yes
LTO_ENABLE=no

## rules.mk, config.h, manna-harbour_miryoku.h, manna-harbour_miryoku.c
USER_NAME := manna-harbour_miryoku


this_dir=keyboards/crkbd/keymaps/manna-harbour

OPT_DEFS += -DMH_USER_NAME_H=\"$(USER_NAME).h\"

ifeq ($(strip $(MH_MODULE)), trackpoint)
  PS2_MOUSE_ENABLE = yes
  PS2_USE_INT = yes
  OPT_DEFS += -DMH_MODULE_TRACKPOINT
else ifeq ($(strip $(MH_MODULE)), oled)
  OLED_DRIVER_ENABLE = yes
else ifeq ($(strip $(MH_MODULE)), oled_old)
  SRC += ./lib/glcdfont.c
  SRC += ./lib/logo_reader.c
  OPT_DEFS += -DSSD1306OLED
endif

ifeq ($(strip $(MH_AUTO_BUTTONS)), yes)
  MOUSEKEY_ENABLE = yes
  OPT_DEFS += -DMH_AUTO_BUTTONS
endif

ifeq ($(strip $(MH_LOW_MOUSE)), yes)
  OPT_DEFS += -DMH_LOW_MOUSE
endif

ifeq ($(strip $(MH_OLED_MODE)), static)
  OPT_DEFS += -DMH_OLED_MODE_STATIC
else ifeq ($(strip $(MH_OLED_MODE)), caps)
  OPT_DEFS += -DMH_OLED_MODE_CAPS
endif

images=$(this_dir)/mh_images
originals=$(images)/originals
converted=$(images)/converted

$(converted)/%.c: $(originals)/%.*
	$(this_dir)/mh_image_to_oled $< > $@

ifeq ($(strip $(MH_OLED_IMAGE)), logo)
  OPT_DEFS += -DMH_OLED_IMAGE_LOGO
else ifneq ($(strip $(MH_OLED_IMAGE)), )
  ifneq ($(strip $(MH_OLED_IMAGE)), no)
    OPT_DEFS += -DMH_OLED_IMAGE_FILE
    ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
      SRC += $(converted)/$(MH_OLED_IMAGE)
    endif
  endif
endif

ifeq ($(strip $(MH_RGB)), matrix)
  RGB_MATRIX_ENABLE = WS2812
else ifeq ($(strip $(MH_RGB)), light)
  RGBLIGHT_ENABLE = yes
else ifeq ($(strip $(MH_RGB)), underglow)
  RGBLIGHT_ENABLE = yes
  OPT_DEFS += -DMH_RGB_UNDERGLOW
endif

ifeq ($(strip $(MH_DEBUG)), yes)
  CONSOLE_ENABLE=yes
  OPT_DEFS += -DMH_DEBUG
endif

