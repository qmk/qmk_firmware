ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	# Additional files for RGB lighting
	SRC += k_type-rgbdriver.c is31fl3733-dual.c
	QUANTUM_LIB_SRC += i2c_master.c
endif
