encoder_DEFS := -DENCODER_TESTS -DENCODER_ENABLE -DENCODER_MOCK_SINGLE
encoder_CONFIG := $(QUANTUM_PATH)/encoder/tests/config_mock.h

encoder_SRC := \
	platforms/test/timer.c \
	drivers/encoder/encoder_quadrature.c \
	$(QUANTUM_PATH)/encoder/tests/mock.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests.cpp \
	$(QUANTUM_PATH)/encoder.c

encoder_split_left_eq_right_DEFS := -DENCODER_TESTS -DENCODER_ENABLE -DENCODER_MOCK_SPLIT
encoder_split_left_eq_right_INC := $(QUANTUM_PATH)/split_common
encoder_split_left_eq_right_CONFIG := $(QUANTUM_PATH)/encoder/tests/config_mock_split_left_eq_right.h

encoder_split_left_eq_right_SRC := \
	platforms/test/timer.c \
	drivers/encoder/encoder_quadrature.c \
	$(QUANTUM_PATH)/encoder/tests/mock_split.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests_split_left_eq_right.cpp \
	$(QUANTUM_PATH)/encoder.c

encoder_split_left_gt_right_DEFS := -DENCODER_TESTS -DENCODER_ENABLE -DENCODER_MOCK_SPLIT
encoder_split_left_gt_right_INC := $(QUANTUM_PATH)/split_common
encoder_split_left_gt_right_CONFIG := $(QUANTUM_PATH)/encoder/tests/config_mock_split_left_gt_right.h

encoder_split_left_gt_right_SRC := \
	platforms/test/timer.c \
	drivers/encoder/encoder_quadrature.c \
	$(QUANTUM_PATH)/encoder/tests/mock_split.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests_split_left_gt_right.cpp \
	$(QUANTUM_PATH)/encoder.c

encoder_split_left_lt_right_DEFS := -DENCODER_TESTS -DENCODER_ENABLE -DENCODER_MOCK_SPLIT
encoder_split_left_lt_right_INC := $(QUANTUM_PATH)/split_common
encoder_split_left_lt_right_CONFIG := $(QUANTUM_PATH)/encoder/tests/config_mock_split_left_lt_right.h

encoder_split_left_lt_right_SRC := \
	platforms/test/timer.c \
	drivers/encoder/encoder_quadrature.c \
	$(QUANTUM_PATH)/encoder/tests/mock_split.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests_split_left_lt_right.cpp \
	$(QUANTUM_PATH)/encoder.c

encoder_split_no_left_DEFS := -DENCODER_TESTS -DENCODER_ENABLE -DENCODER_MOCK_SPLIT
encoder_split_no_left_INC := $(QUANTUM_PATH)/split_common
encoder_split_no_left_CONFIG := $(QUANTUM_PATH)/encoder/tests/config_mock_split_no_left.h

encoder_split_no_left_SRC := \
	platforms/test/timer.c \
	drivers/encoder/encoder_quadrature.c \
	$(QUANTUM_PATH)/encoder/tests/mock_split.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests_split_no_left.cpp \
	$(QUANTUM_PATH)/encoder.c

encoder_split_no_right_DEFS := -DENCODER_TESTS -DENCODER_ENABLE -DENCODER_MOCK_SPLIT
encoder_split_no_right_INC := $(QUANTUM_PATH)/split_common
encoder_split_no_right_CONFIG := $(QUANTUM_PATH)/encoder/tests/config_mock_split_no_right.h

encoder_split_no_right_SRC := \
	platforms/test/timer.c \
	drivers/encoder/encoder_quadrature.c \
	$(QUANTUM_PATH)/encoder/tests/mock_split.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests_split_no_right.cpp \
	$(QUANTUM_PATH)/encoder.c

encoder_split_role_DEFS := -DENCODER_TESTS -DENCODER_ENABLE -DENCODER_MOCK_SPLIT
encoder_split_role_INC := $(QUANTUM_PATH)/split_common
encoder_split_role_CONFIG := $(QUANTUM_PATH)/encoder/tests/config_mock_split_role.h

encoder_split_role_SRC := \
	platforms/test/timer.c \
	drivers/encoder/encoder_quadrature.c \
	$(QUANTUM_PATH)/encoder/tests/mock_split.c \
	$(QUANTUM_PATH)/encoder/tests/encoder_tests_split_role.cpp \
	$(QUANTUM_PATH)/encoder.c
