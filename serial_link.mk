CGREEN_LIB = $(BUILDDIR)/cgreen/build-c/src/libcgreen.a

.phony testserial:
testserial: $(CGREEN_LIB)

CGREEN_DIR = "$(CURDIR)/$(SERIAL_DIR)/cgreen/cgreen"
CGREEN_BUILD_DIR = "$(CURDIR)/$(BUILDDIR)/cgreen"
export CGREEN_DIR
export CGREEN_BUILD_DIR
$(CGREEN_LIB):
	make -C $(SERIAL_DIR)/cgreen