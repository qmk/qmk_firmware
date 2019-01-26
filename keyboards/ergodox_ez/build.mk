ifeq ($(strip $(RGB_MATRIX_ENABLE)), no)
  SRC += i2c_master.c
endif

ifeq ($(strip $(I2CLCD_AF_ENABLE)), yes)
    SRC += i2c_lcd_af.c
    OPT_DEFS += -DI2CLCD_PORT=$(I2CLCD_PORT) -DI2CLCD_ENABLE
endif

ifeq ($(strip $(I2CLCD_SB_ENABLE)), yes)
    SRC += i2c_lcd_sb.c
    OPT_DEFS += -DI2CLCD_PORT=$(I2CLCD_PORT) -DI2CLCD_ENABLE
endif

ifeq ($(strip $(I2CLCD_ENABLE)), yes)
  SRC += i2c_lcd.c
  OPT_DEFS += -DI2CLCD_PORT=$(I2CLCD_PORT)
endif

ifeq ($(strip $(LCDSTENO_ENABLE)), yes)
  SRC += lcd_steno.c
endif
