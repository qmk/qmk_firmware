AUDIO_ENABLE ?= yes           # Audio output on port C6

MCU = at90usb1286

ifndef QUANTUM_DIR
	include ../../../Makefile
endif