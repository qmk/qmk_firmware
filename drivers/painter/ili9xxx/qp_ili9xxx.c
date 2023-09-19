// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_comms.h"
#include "qp_ili9xxx_opcodes.h"

bool qp_ili9xxx_set_inversion(painter_device_t device, bool invert) {
    if (!device) {
        qp_dprintf("qp_ili9xxx_set_inversion: fail (un-initialized pointer)\n");
        return false;
    }

    qp_comms_command(device, invert ? ILI9XXX_CMD_INVERT_ON : ILI9XXX_CMD_INVERT_OFF);

    qp_dprintf("qp_ili9xxx_set_inversion: ok\n");
    return true;
}
