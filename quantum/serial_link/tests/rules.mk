serial_link_byte_stuffer_SRC :=\
	$(SERIAL_PATH)/tests/byte_stuffer_tests.cpp \
	$(SERIAL_PATH)/protocol/byte_stuffer.c

serial_link_frame_router_SRC := \
	$(SERIAL_PATH)/tests/frame_router_tests.cpp \
	$(SERIAL_PATH)/protocol/byte_stuffer.c \
    $(SERIAL_PATH)/protocol/frame_validator.c \
	$(SERIAL_PATH)/protocol/frame_router.c