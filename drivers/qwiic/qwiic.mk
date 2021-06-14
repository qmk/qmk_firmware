ifeq ($(strip $(QWIIC_ENABLE)),yes)
  COMMON_VPATH += $(DRIVER_PATH)/qwiic
  OPT_DEFS += -DQWIIC_ENABLE
  SRC += qwiic.c
  QUANTUM_LIB_SRC += i2c_master.c

ifneq ($(filter JOYSTIIC, $(QWIIC_DRIVERS)),)
  OPT_DEFS += -DQWIIC_JOYSTIIC_ENABLE
  SRC += joystiic.c
endif

ifneq ($(filter MICRO_OLED, $(QWIIC_DRIVERS)),)
  OPT_DEFS += -DQWIIC_MICRO_OLED_ENABLE
  SRC += micro_oled.c
endif

endif
