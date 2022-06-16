GFXINC  += $(GFXLIB)/boards/base/OSX
GFXSRC  +=
GFXDEFS += -DGFX_USE_OS_OSX=GFXON
GFXLIBS +=

include $(GFXLIB)/drivers/multiple/SDL/driver.mk

