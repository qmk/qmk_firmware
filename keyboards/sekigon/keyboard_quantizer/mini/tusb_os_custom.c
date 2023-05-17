// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ch.h"
#include "tusb_os_custom.h"

void osal_task_delay(uint32_t msec) {
    chThdSleepMilliseconds(msec);
}

osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef) {
    chMtxObjectInit((mutex_t*)mdef);
    return mdef;
}

bool osal_mutex_lock(osal_mutex_t mutex_hdl, uint32_t msec) {
    chMtxLock((mutex_t*)mutex_hdl);
    return true;
}

bool osal_mutex_unlock(osal_mutex_t mutex_hdl) {
    chMtxUnlock((mutex_t*)mutex_hdl);
    return true;
}
