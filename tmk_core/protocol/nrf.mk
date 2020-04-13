PROTOCOL_DIR = protocol
NRF_DIR = $(PROTOCOL_DIR)/nrf

  SRC += $(NRF_DIR)/matrix.c \
		 $(NRF_DIR)/matrix_basic.c \
		 $(NRF_DIR)/matrix_lpme.c \
		 $(NRF_DIR)/matrix_duplex.c \
		 $(NRF_DIR)/lpme.c \

 SRC += \
       $(NRF_DIR)/main_master.c \
       $(NRF_DIR)/$(NRF_VER_DIR)/cli.c \
       $(NRF_DIR)/microshell/core/microshell.c \
       $(NRF_DIR)/microshell/core/mscore.c \
       $(NRF_DIR)/microshell/util/mscmd.c \
       $(NRF_DIR)/microshell/util/msopt.c \
       $(NRF_DIR)/microshell/util/ntlibc.c \
       $(NRF_DIR)/$(NRF_VER_DIR)/configurator.c \
       $(NRF_DIR)/keycode_str_converter.c \
       $(NRF_DIR)/config_file_util.c \
       $(NRF_DIR)/bmp.c \
       $(NRF_DIR)/bmp_extended_keycode_converter.c \
       $(NRF_DIR)/bmp_process_extended_keycode.c \
       $(NRF_DIR)/bmp_indicator_led.c \

VPATH += $(TMK_PATH)/$(NRF_DIR)/microshell/core
VPATH += $(TMK_PATH)/$(NRF_DIR)/microshell/util


VPATH += $(TMK_PATH)/$(PROTOCOL_DIR)
VPATH += $(TMK_PATH)/$(NRF_DIR)

ifeq ($(strip $(ENCODER_ENABLE)), yes)
  $(error Use BMP_ENCODER_ENABLE instead of ENCODER_ENABLE)
endif
ifeq ($(strip $(BMP_ENCODER_ENABLE)), yes)
  CFLAGS += -DBMP_ENCODER_ENABLE
  SRC += $(NRF_DIR)/encoder.c
endif

ifeq ($(strip $(MIDI_ENABLE)), yes)
  include $(TMK_PATH)/protocol/midi.mk
endif

