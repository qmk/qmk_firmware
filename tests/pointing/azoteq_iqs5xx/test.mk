# Copyright 2026 QMK
# SPDX-License-Identifier: GPL-2.0-or-later

SRC += drivers/sensors/azoteq_iqs5xx.c
SRC += tests/pointing/azoteq_iqs5xx/azoteq_iqs5xx_mock.c

VPATH += $(QUANTUM_DIR)/pointing_device
VPATH += drivers/sensors
