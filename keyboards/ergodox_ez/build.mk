ifeq ($(strip $(RGB_MATRIX_ENABLE)), no)
  SRC += i2c_master.c
endif
