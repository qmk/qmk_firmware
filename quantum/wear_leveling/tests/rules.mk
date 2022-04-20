wear_leveling_common_DEFS := \
	-DWEAR_LEVELING_TESTS \
	-DWEAR_LEVELING_ASSERTS
wear_leveling_common_SRC := \
	$(QUANTUM_PATH)/wear_leveling/wear_leveling.c \
	$(QUANTUM_PATH)/wear_leveling/tests/backing_mocks.cpp
wear_leveling_common_INC := \
	$(QUANTUM_PATH)/wear_leveling

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

wear_leveling_2byte_consolidation_DEFS := \
	$(wear_leveling_common_DEFS) \
	-DBACKING_STORE_WRITE_SIZE=2 \
	-DWEAR_LEVELING_BACKING_SIZE=64 \
	-DWEAR_LEVELING_LOGICAL_SIZE=32
wear_leveling_2byte_consolidation_SRC := \
	$(wear_leveling_common_SRC) \
	$(QUANTUM_PATH)/wear_leveling/tests/wear_leveling_2byte_consolidation.cpp
wear_leveling_2byte_consolidation_INC := \
	$(wear_leveling_common_INC)

wear_leveling_4byte_consolidation_DEFS := \
	$(wear_leveling_common_DEFS) \
	-DBACKING_STORE_WRITE_SIZE=4 \
	-DWEAR_LEVELING_BACKING_SIZE=64 \
	-DWEAR_LEVELING_LOGICAL_SIZE=32
wear_leveling_4byte_consolidation_SRC := \
	$(wear_leveling_common_SRC) \
	$(QUANTUM_PATH)/wear_leveling/tests/wear_leveling_4byte_consolidation.cpp
wear_leveling_4byte_consolidation_INC := \
	$(wear_leveling_common_INC)

wear_leveling_8byte_consolidation_DEFS := \
	$(wear_leveling_common_DEFS) \
	-DBACKING_STORE_WRITE_SIZE=8 \
	-DWEAR_LEVELING_BACKING_SIZE=64 \
	-DWEAR_LEVELING_LOGICAL_SIZE=32
wear_leveling_8byte_consolidation_SRC := \
	$(wear_leveling_common_SRC) \
	$(QUANTUM_PATH)/wear_leveling/tests/wear_leveling_8byte_consolidation.cpp
wear_leveling_8byte_consolidation_INC := \
	$(wear_leveling_common_INC)