ifneq ($(strip $(QWIIC_ENABLE)),)
  COMMON_VPATH += $(DRIVER_PATH)/qwiic
  OPT_DEFS += -DQWIIC_ENABLE
  SRC += qwiic.c
  ifeq ($(filter "i2c_master.c", $(SRC)),)
    SRC += i2c_master.c
  endif
endif

ifneq ($(filter JOYSTIIC, $(QWIIC_ENABLE)),)
  OPT_DEFS += -DQWIIC_JOYSTIIC_ENABLE
  SRC += joystiic.c
endif

ifneq ($(filter MICRO_OLED, $(QWIIC_ENABLE)),)
  OPT_DEFS += -DQWIIC_MICRO_OLED_ENABLE
  SRC += micro_oled.c
endif
