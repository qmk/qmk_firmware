CGREEN_LIB = $(BUILDDIR)/cgreen/build-c/src/libcgreen.a

CGREEN_DIR = "$(CURDIR)/$(SERIAL_DIR)/cgreen/cgreen"
CGREEN_BUILD_DIR = "$(CURDIR)/$(BUILDDIR)/cgreen"
export CGREEN_DIR
export CGREEN_BUILD_DIR
$(CGREEN_LIB):
	make -C $(SERIAL_DIR)/cgreen 

.PHONY serialtest:
serialtest : $(CGREEN_LIB)
	@echo $(CGREEN_LIB)
	make -C $(SERIAL_DIR)/tests BUILDDIR=../../$(BUILDDIR)