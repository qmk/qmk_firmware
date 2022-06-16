GFXINC  += $(GFXLIB)/boards/base/Linux
GFXSRC  +=
GFXDEFS += -DGFX_USE_OS_LINUX=GFXON
GFXLIBS += rt

include $(GFXLIB)/drivers/multiple/X/driver.mk
