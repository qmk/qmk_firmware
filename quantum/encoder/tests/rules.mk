encoder_DEFS := -DENCODER_MOCK_SINGLE

encoder_SRC := \
	$(QUANTUM_PATH)/encoder/tests/mock.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests.cpp \
	$(QUANTUM_PATH)/encoder.c

encoder_split_DEFS := -DENCODER_MOCK_SPLIT

encoder_split_SRC := \
	$(QUANTUM_PATH)/encoder/tests/mock_split.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests_split.cpp \
	$(QUANTUM_PATH)/encoder.c
