GFXINC  +=	$(GFXLIB)/boards/base/STM32F439i-Eval/CubeHAL
GFXSRC  +=	$(GFXLIB)/boards/base/STM32F439i-Eval/CubeHAL/stm324x9i_eval_sdram.c
				
ifeq ($(OPT_OS),raw32)
	GFXDEFS +=	STM32F439xx
	GFXSRC	+=	$(STMHAL)/Src/stm32f4xx_hal.c \
				$(STMHAL)/Src/stm32f4xx_hal_cortex.c \
				$(STMHAL)/Src/stm32f4xx_hal_rcc.c \
				$(STMHAL)/Src/stm32f4xx_hal_rcc_ex.h \
				$(STMHAL)/Src/stm32f4xx_hal_gpio.c \
				$(STMHAL)/Src/stm32f4xx_hal_pwr.c \
				$(STMHAL)/Src/stm32f4xx_hal_pwr_ex.c \
				$(STMHAL)/Src/stm32f4xx_hal_sdram.c \
				$(STMHAL)/Src/stm32f4xx_hal_dma.c \
				$(STMHAL)/Src/stm32f4xx_hal_ltdc.c \
				$(STMHAL)/Src/stm32f4xx_hal_i2c.c \
				$(STMHAL)/Src/stm32f4xx_ll_fmc.c
	GFXSRC	+=	$(GFXLIB)/boards/base/STM32F439i-Eval/CubeHAL/stm32f439i_raw32_startup.s \
				$(GFXLIB)/boards/base/STM32F439i-Eval/CubeHAL/stm32f439i_raw32_ugfx.c \
				$(GFXLIB)/boards/base/STM32F439i-Eval/CubeHAL/stm32f439i_raw32_system.c \
				$(GFXLIB)/boards/base/STM32F439i-Eval/CubeHAL/stm32f439i_raw32_interrupts.c
	GFXDEFS	+=	GFX_OS_PRE_INIT_FUNCTION=Raw32OSInit GFX_OS_INIT_NO_WARNING=GFXON
	GFXINC	+=	$(CMSIS)/Device/ST/STM32F4xx/Include \
				$(CMSIS)/Include \
				$(STMHAL)/Inc
	LDSCRIPT = $(GFXLIB)/boards/base/STM32F439i-Eval/CubeHAL/stm32f439nihx_flash.ld
endif

include $(GFXLIB)/drivers/gdisp/STM32LTDC/driver.mk
include $(GFXLIB)/drivers/ginput/touch/EXC7200/driver.mk