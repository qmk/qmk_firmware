GFXINC  +=	$(GFXLIB)/boards/base/STM32F469i-Discovery \
		$(GFXLIB)/boards/base/STM32F469i-Discovery/CubeHAL \
		$(STMHAL)/Inc

GFXSRC  +=	$(GFXLIB)/boards/base/STM32F469i-Discovery/stm32f469i_discovery_sdram.c
				
ifeq ($(OPT_OS),raw32)
	GFXDEFS +=	STM32F469xx
	GFXSRC	+=	$(STMHAL)/Src/stm32f4xx_hal.c \
			$(STMHAL)/Src/stm32f4xx_hal_cortex.c \
			$(STMHAL)/Src/stm32f4xx_hal_rcc.c \
			$(STMHAL)/Src/stm32f4xx_hal_rcc_ex.h \
			$(STMHAL)/Src/stm32f4xx_hal_gpio.c \
			$(STMHAL)/Src/stm32f4xx_hal_pwr.c \
			$(STMHAL)/Src/stm32f4xx_hal_pwr_ex.c \
			$(STMHAL)/Src/stm32f4xx_hal_dma.c \
			$(STMHAL)/Src/stm32f4xx_hal_i2c.c \
			$(STMHAL)/Src/stm32f4xx_hal_sdram.c \
			$(STMHAL)/Src/stm32f4xx_hal_dsi.c \
			$(STMHAL)/Src/stm32f4xx_ll_fmc.c \
			$(GFXLIB)/boards/base/STM32F469i-Discovery/otm8009a.c
	GFXSRC	+=	$(GFXLIB)/boards/base/STM32F469i-Discovery/startup_stm32f469xx.s \
			$(GFXLIB)/boards/base/STM32F469i-Discovery/stm32f469i_raw32_ugfx.c \
			$(GFXLIB)/boards/base/STM32F469i-Discovery/stm32f469i_raw32_system.c \
			$(GFXLIB)/boards/base/STM32F469i-Discovery/stm32f469i_raw32_it.c
	GFXDEFS	+=	GFX_OS_PRE_INIT_FUNCTION=Raw32OSInit GFX_OS_INIT_NO_WARNING=GFXON
	GFXINC	+=	$(CMSIS)/Device/ST/STM32F4xx/Include \
			$(CMSIS)/Include
	LDSCRIPT = 	$(GFXLIB)/boards/base/STM32F469i-Discovery/STM32_FLASH.ld
endif

include $(GFXLIB)/drivers/gdisp/STM32LTDC/driver.mk
include $(GFXLIB)/drivers/ginput/touch/FT6x06/driver.mk
