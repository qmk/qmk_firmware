GFXINC  += $(GFXLIB)/boards/base/Linux-Framebuffer-Touch
GFXSRC  +=
GFXDEFS += -DGFX_USE_OS_LINUX=GFXON
GFXLIBS += rt

include $(GFXLIB)/boards/base/Linux-Framebuffer/board.mk
include $(GFXLIB)/drivers/ginput/touch/Linux-Event/driver.mk
