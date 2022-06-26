wear_leveling_common_DEFS := \
	-DWEAR_LEVELING_TESTS
wear_leveling_common_SRC := \
	$(LIB_PATH)/fnv/qmk_fnv_type_validation.c \
	$(LIB_PATH)/fnv/hash_32a.c \
	$(LIB_PATH)/fnv/hash_64a.c \
	$(QUANTUM_PATH)/wear_leveling/wear_leveling.c \
	$(QUANTUM_PATH)/wear_leveling/tests/backing_mocks.cpp
wear_leveling_common_INC := \
	$(LIB_PATH)/fnv \
	$(QUANTUM_PATH)/wear_leveling

wear_leveling_general_DEFS := \
	$(wear_leveling_common_DEFS) \
	-DBACKING_STORE_WRITE_SIZE=2 \
	-DWEAR_LEVELING_BACKING_SIZE=48 \
	-DWEAR_LEVELING_LOGICAL_SIZE=16
wear_leveling_general_SRC := \
	$(wear_leveling_common_SRC) \
	$(QUANTUM_PATH)/wear_leveling/tests/wear_leveling_general.cpp
wear_leveling_general_INC := \
	$(wear_leveling_common_INC)

wear_leveling_2byte_optimized_writes_DEFS := \
	$(wear_leveling_common_DEFS) \
	-DBACKING_STORE_WRITE_SIZE=2 \
	-DWEAR_LEVELING_BACKING_SIZE=65536 \
	-DWEAR_LEVELING_LOGICAL_SIZE=32768
wear_leveling_2byte_optimized_writes_SRC := \
	$(wear_leveling_common_SRC) \
	$(QUANTUM_PATH)/wear_leveling/tests/wear_leveling_2byte_optimized_writes.cpp
wear_leveling_2byte_optimized_writes_INC := \
	$(wear_leveling_common_INC)

wear_leveling_2byte_DEFS := \
	$(wear_leveling_common_DEFS) \
	-DBACKING_STORE_WRITE_SIZE=2 \
	-DWEAR_LEVELING_BACKING_SIZE=48 \
	-DWEAR_LEVELING_LOGICAL_SIZE=16
wear_leveling_2byte_SRC := \
	$(wear_leveling_common_SRC) \
	$(QUANTUM_PATH)/wear_leveling/tests/wear_leveling_2byte.cpp
wear_leveling_2byte_INC := \
	$(wear_leveling_common_INC)

wear_leveling_4byte_DEFS := \
	$(wear_leveling_common_DEFS) \
	-DBACKING_STORE_WRITE_SIZE=4 \
	-DWEAR_LEVELING_BACKING_SIZE=48 \
	-DWEAR_LEVELING_LOGICAL_SIZE=16
wear_leveling_4byte_SRC := \
	$(wear_leveling_common_SRC) \
	$(QUANTUM_PATH)/wear_leveling/tests/wear_leveling_4byte.cpp
wear_leveling_4byte_INC := \
	$(wear_leveling_common_INC)

wear_leveling_8byte_DEFS := \
	$(wear_leveling_common_DEFS) \
	-DBACKING_STORE_WRITE_SIZE=8 \
	-DWEAR_LEVELING_BACKING_SIZE=48 \
	-DWEAR_LEVELING_LOGICAL_SIZE=16
wear_leveling_8byte_SRC := \
	$(wear_leveling_common_SRC) \
	$(QUANTUM_PATH)/wear_leveling/tests/wear_leveling_8byte.cpp
wear_leveling_8byte_INC := \
	$(wear_leveling_common_INC)