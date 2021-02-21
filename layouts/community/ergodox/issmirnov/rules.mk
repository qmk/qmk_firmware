# https://github.com/qmk/qmk_firmware/blob/master/docs/getting_started_make_guide.md
ifndef QUANTUM_DIR
    include ../../../../Makefile
endif

# Enable ORYX options
ORYX_ENABLE = yes
WEBUSB_ENABLE = yes

