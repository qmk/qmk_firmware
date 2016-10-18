serial_link_byte_stuffer_SRC :=\
	$(SERIAL_PATH)/tests/byte_stuffer_tests.cpp \
	$(SERIAL_PATH)/protocol/byte_stuffer.c

serial_link_frame_validator_SRC := \
	$(SERIAL_PATH)/tests/frame_validator_tests.cpp \
	$(SERIAL_PATH)/protocol/frame_validator.c 

serial_link_frame_router_SRC := \
	$(SERIAL_PATH)/tests/frame_router_tests.cpp \
	$(SERIAL_PATH)/protocol/byte_stuffer.c \
	$(SERIAL_PATH)/protocol/frame_validator.c \
	$(SERIAL_PATH)/protocol/frame_router.c

serial_link_triple_buffered_object_SRC := \
	$(SERIAL_PATH)/tests/triple_buffered_object_tests.cpp \
	$(SERIAL_PATH)/protocol/triple_buffered_object.c 

serial_link_transport_SRC := \
	$(SERIAL_PATH)/tests/transport_tests.cpp \
	$(SERIAL_PATH)/protocol/transport.c \
	$(SERIAL_PATH)/protocol/triple_buffered_object.c 
