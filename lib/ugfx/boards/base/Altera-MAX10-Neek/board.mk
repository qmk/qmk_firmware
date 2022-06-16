GFXINC  += $(GFXLIB)/boards/base/Altera-MAX10-NEEK
GFXSRC  +=
GFXDEFS +=
GFXLIBS +=

include $(GFXLIB)/drivers/gdisp/alteraframereader/driver.mk
include $(GFXLIB)/drivers/ginput/touch/FT5316/driver.mk
