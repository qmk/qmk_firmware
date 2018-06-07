ifeq ($(USE_HAL_I2C_FALLBACK),yes)
  # Fallback SW driver.
  ifeq ($(USE_SMART_BUILD),yes)
    ifneq ($(findstring HAL_USE_I2C TRUE,$(HALCONF)),)
      PLATFORMSRC += $(CHIBIOS)/os/hal/lib/fallback/I2C/hal_i2c_lld.c
    endif
  else
    PLATFORMSRC += $(CHIBIOS)/os/hal/lib/fallback/I2C/hal_i2c_lld.c
  endif
  PLATFORMINC += $(CHIBIOS)/os/hal/lib/fallback/I2C
else
  # Default HW driver.
  ifeq ($(USE_SMART_BUILD),yes)
    ifneq ($(findstring HAL_USE_I2C TRUE,$(HALCONF)),)
      PLATFORMSRC += $(CHIBIOS)/os/hal/ports/STM32/LLD/I2Cv2/hal_i2c_lld.c
    endif
  else
    PLATFORMSRC += $(CHIBIOS)/os/hal/ports/STM32/LLD/I2Cv2/hal_i2c_lld.c
  endif
  PLATFORMINC += $(CHIBIOS)/os/hal/ports/STM32/LLD/I2Cv2
endif
