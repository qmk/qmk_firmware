# Keycode cache unit tests configuration

keycode_cache_DEFS := -DMATRIX_ROWS=4 -DMATRIX_COLS=4 -DNO_DEBUG -DKEYCODE_CACHE_ENABLE -DKEYCODE_CACHE_LIMIT=8

keycode_cache_SRC := \
	$(QUANTUM_PATH)/keycode_cache/keycode_cache_tests.cpp \
	$(QUANTUM_PATH)/keycode_cache/keycode_cache_mock.c \
	$(QUANTUM_PATH)/action_layer.c \
