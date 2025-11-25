// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef QUANTUM_PAINTER_DUMMY_COMMS_ENABLE

#    include "qp_comms_dummy.h"

static bool dummy_comms_init(painter_device_t device) {
    // No-op.
    return true;
}

static bool dummy_comms_start(painter_device_t device) {
    // No-op.
    return true;
}

static bool dummy_comms_stop(painter_device_t device) {
    // No-op.
    return true;
}

uint32_t dummy_comms_send(painter_device_t device, const void *data, uint32_t byte_count) {
    // No-op.
    return byte_count;
}

painter_comms_vtable_t dummy_comms_vtable = {
    // These are all effective no-op's because they're not actually needed.
    .comms_init  = dummy_comms_init,
    .comms_start = dummy_comms_start,
    .comms_stop  = dummy_comms_stop,
    .comms_send  = dummy_comms_send};

#endif // QUANTUM_PAINTER_DUMMY_COMMS_ENABLE
