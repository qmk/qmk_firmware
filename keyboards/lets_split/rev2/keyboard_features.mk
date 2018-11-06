#
# SPLIT_COMMUNICATION and OLED_ENABLE settings convert to C lang Macros
#
USE_I2C = no

ifeq ($(strip $(SPLIT_COMMUNICATION)), serial)
  # set SPLIT_COMMUNICATION_SERIAL for matrix.c and split_util.c
  KOPT_SRC += serial.c
  EXTRAFLAGS += -DSPLIT_COMMUNICATION_SERIAL
else
  ifeq ($(strip $(SPLIT_COMMUNICATION)), i2c)
    # set SPLIT_COMMUNICATION_I2C for matrix.c and split_util.c
    EXTRAFLAGS += -DSPLIT_COMMUNICATION_I2C
    USE_I2C = yes
  else
    $(error invalid SPLIT_COMMUNICATION value)
  endif
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
  KOPT_SRC += ssd1306.c
  # set SSD1306OLED for rev2/rev2.c and split_util.c
  EXTRAFLAGS += -DSSD1306OLED
  USE_I2C = yes
endif

ifeq ($(strip $(USE_I2C)), yes)
  KOPT_SRC += i2c.c
  # set USE_I2C for seria.c(for conflict check) and rev2.h
  EXTRAFLAGS += -DUSE_I2C #  for test  -DSOFT_SERIAL_PIN=D2
endif

ifdef RULES_VERBOSE
  $(info *** keyboards/lets_split/rev2/keyboard_features.mk ***)
  $(info  SRC += $(KOPT_SRC))
  $(info  USE_I2C = $(USE_I2C))
  $(info  SPLIT_COMMUNICATION = $(SPLIT_COMMUNICATION))
  $(info  EXTRAFLAGS = $(EXTRAFLAGS))
endif

SRC += $(KOPT_SRC)
