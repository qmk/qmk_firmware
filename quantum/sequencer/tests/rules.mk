# The letter case of these variables might seem odd. However:
# - it is consistent with the example that is used as a reference in the Unit Testing article (https://docs.qmk.fm/#/unit_testing?id=adding-tests-for-new-or-existing-features)
# - Neither `make test:sequencer` or `make test:SEQUENCER` work when using SCREAMING_SNAKE_CASE

sequencer_DEFS := -DMATRIX_ROWS=1 -DMATRIX_COLS=1 -DNO_DEBUG -DMIDI_MOCKED

sequencer_SRC := \
	$(QUANTUM_PATH)/sequencer/tests/midi_mock.c \
	$(QUANTUM_PATH)/sequencer/tests/sequencer_tests.cpp \
	$(QUANTUM_PATH)/sequencer/sequencer.c \
	$(PLATFORM_PATH)/timer.c \
	$(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c
