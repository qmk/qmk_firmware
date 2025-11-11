/* Copyright 2025 David Girault
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <string.h>

#include "hal.h"
#include "quantum.h"
#include "transport.h"
#include "sync_timer.h"
#include "synchronization_util.h"
#include "split_util.h"

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif
#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif

#define ROWS_PER_HAND (MATRIX_ROWS / 2)
#define SYNC_TIMER_OFFSET 0

unsigned sync_errors[8];
static void i2cCountError(msg_t rc) {
  int i;
  if (rc == MSG_OK) {
    return;
  } else if (rc == MSG_TIMEOUT) {
    sync_errors[7]++;
  } else {
    i2cflags_t err = i2cGetErrors(&I2CD1);
    for (i = 0; i < 7; i++) {
      if (err & (1 << i))
        sync_errors[i]++;
    }
  }
}

// Buffer for master/slave matrix scan transmit.
// Master: receive buffer.
// Slave: transmit buffer.
matrix_row_t sync_matrix[ROWS_PER_HAND];

// Buffer for master/slave state transmit.
// Master:  transmit buffer.
// Slave: receive buffer.
struct sync_master {
  char valid;
#ifdef SPLIT_LED_STATE_ENABLE
  uint8_t led_state;
#endif
#ifdef SPLIT_WATCHDOG_ENABLE
  char watchdog;
#endif
#if defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)
  char oled_state;
#endif
#ifndef DISABLE_SYNC_TIMER
  uint32_t timer;
#endif
#ifdef SPLIT_LAYER_STATE_ENABLE
  uint16_t layer_state;
  uint16_t default_layer_state;
#endif
#ifdef SPLIT_MODS_ENABLE
  split_mods_sync_t mods; /* 4 * uint8_t */
#endif
#ifdef SPLIT_ACTIVITY_ENABLE
  split_slave_activity_sync_t activity;
#endif
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
  rgb_matrix_sync_t rgb_matrix;
#endif
} sync_master;

enum sync_master_valid {
    VALID_TIMER       = 1,
    VALID_LAYER_STATE = 2,
    VALID_LED_STATE   = 4,
    VALID_MODS_STATE  = 8,
    VALID_RGB_MATRIX  = 16,
    VALID_OLED_STATE  = 32,
    VALID_ACTIVITY    = 64,
    VALID_WATCHDOG    = 128,
};

////////////////////////////////////////////////////
// TIMER

#ifndef DISABLE_SYNC_TIMER
static void transport_master_prepare_timer(void) {
  if (timer_elapsed32(sync_master.timer) >= FORCED_SYNC_THROTTLE_MS) {
    sync_master.timer = sync_timer_read32() + SYNC_TIMER_OFFSET;
    sync_master.valid |= VALID_TIMER;
  }
}
static void transport_slave_update_timer(void) {
  static uint32_t last_sync_timer = 0;
  if ((sync_master.valid & VALID_TIMER) && last_sync_timer != sync_master.timer) {
    sync_master.valid &= ~VALID_TIMER;
    last_sync_timer = sync_master.timer;
    sync_timer_update(last_sync_timer);
  }
}
#else
#define transport_master_prepare_timer() do { } while (0)
#define transport_slave_update_timer() do { } while (0)
#endif

////////////////////////////////////////////////////
// LAYER

#ifdef SPLIT_LAYER_STATE_ENABLE
static void transport_master_prepare_layer(void) {
  if (layer_state != sync_master.layer_state || default_layer_state != sync_master.default_layer_state) {
    sync_master.layer_state = layer_state;
    sync_master.default_layer_state = default_layer_state;
    sync_master.valid |= VALID_LAYER_STATE;
  }
}
static void transport_slave_update_layer(void) {
  if (sync_master.valid & VALID_LAYER_STATE) {
    sync_master.valid &= ~VALID_LAYER_STATE;
    layer_state         = sync_master.layer_state;
    default_layer_state = sync_master.default_layer_state;
  }
}
#else
#define transport_master_prepare_layer() do { } while (0)
#define transport_slave_update_layer() do { } while (0)
#endif

////////////////////////////////////////////////////
// LEDS

#ifdef SPLIT_LED_STATE_ENABLE
static void transport_master_prepare_leds(void) {
  uint8_t led_state;
  led_state = host_keyboard_leds();
  if (led_state != sync_master.led_state) {
    sync_master.led_state = led_state;
    sync_master.valid |= VALID_LED_STATE;
  }
}
void set_split_host_keyboard_leds(uint8_t led_state);
static void transport_slave_update_leds(void) {
  if (sync_master.valid & VALID_LED_STATE) {
    sync_master.valid &= ~VALID_LED_STATE;
    set_split_host_keyboard_leds(sync_master.led_state);
  }
}
#else
#define transport_master_prepare_leds() do { } while (0)
#define transport_slave_update_leds() do { } while (0)
#endif

////////////////////////////////////////////////////
// MODS

#ifdef SPLIT_MODS_ENABLE
static void transport_master_prepare_mods(void) {
  split_mods_sync_t new_mods;
  bool mods_need_sync = false;
  new_mods.real_mods = get_mods();
  if (!mods_need_sync && new_mods.real_mods != sync_master.mods.real_mods) {
    mods_need_sync = true;
  }
  new_mods.weak_mods = get_weak_mods();
  if (!mods_need_sync && new_mods.weak_mods != sync_master.mods.weak_mods) {
    mods_need_sync = true;
  }
#ifndef NO_ACTION_ONESHOT
  new_mods.oneshot_mods = get_oneshot_mods();
  if (!mods_need_sync && new_mods.oneshot_mods != sync_master.mods.oneshot_mods) {
    mods_need_sync = true;
  }
  new_mods.oneshot_locked_mods = get_oneshot_locked_mods();
  if (!mods_need_sync && new_mods.oneshot_locked_mods != sync_master.mods.oneshot_locked_mods) {
    mods_need_sync = true;
  }
#endif // NO_ACTION_ONESHOT
  if (mods_need_sync)
    sync_master.valid |= VALID_MODS_STATE;
}
static void transport_slave_update_mods(void) {
  if (sync_master.valid & VALID_MODS_STATE) {
    split_mods_sync_t *mods = &sync_master.mods;
    sync_master.valid &= ~VALID_MODS_STATE;
    set_mods(mods->real_mods);
    set_weak_mods(mods->weak_mods);
#ifndef NO_ACTION_ONESHOT
    set_oneshot_mods(mods->oneshot_mods);
    set_oneshot_locked_mods(mods->oneshot_locked_mods);
#endif
  }
}
#else
#define transport_master_prepare_mods() do { } while (0)
#define transport_slave_update_mods() do { } while (0)
#endif

////////////////////////////////////////////////////
// RGB Matrix

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
static void transport_master_prepare_rgb_matrix(void) {
    rgb_matrix_sync_t rgb_matrix_tmp;
    bool changed;
    memcpy(&rgb_matrix_tmp.rgb_matrix, &rgb_matrix_config, sizeof(rgb_config_t));
    rgb_matrix_tmp.rgb_suspend_state = rgb_matrix_get_suspend_state();
    changed = memcmp(&sync_master.rgb_matrix, &rgb_matrix_tmp, sizeof(rgb_matrix_tmp)) != 0;
    if (changed) {
      sync_master.rgb_matrix = rgb_matrix_tmp;
      sync_master.valid |= VALID_RGB_MATRIX;
    }
}
static void transport_slave_update_rgb_matrix(void) {
  if (sync_master.valid & VALID_RGB_MATRIX) {
    sync_master.valid &= ~VALID_RGB_MATRIX;
    memcpy(&rgb_matrix_config, &sync_master.rgb_matrix.rgb_matrix, sizeof(rgb_config_t));
    rgb_matrix_set_suspend_state(sync_master.rgb_matrix.rgb_suspend_state);
  }
}
#else
#define transport_master_prepare_rgb_matrix() do { } while (0)
#define transport_slave_update_rgb_matrix() do { } while (0)
#endif

////////////////////////////////////////////////////
// RGB Matrix

#if defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)
static void transport_master_prepare_oled(void) {
    bool current_oled_state = is_oled_on();
    if (current_oled_state != sync_master.oled_state) {
      sync_master.oled_state = current_oled_state;
      sync_master.valid |= VALID_OLED_STATE;
    }
}
static void transport_slave_update_oled(void) {
  if (sync_master.valid & VALID_OLED_STATE) {
    sync_master.valid &= ~VALID_OLED_STATE;
    if (sync_master.oled_state) {
        oled_on();
    } else {
        oled_off();
    }
  }
}
#else
#define transport_master_prepare_oled() do { } while (0)
#define transport_slave_update_oled() do { } while (0)
#endif

////////////////////////////////////////////////////
// WATCHDOG

#ifdef SPLIT_WATCHDOG_ENABLE
static void transport_master_prepare_watchdog(void) {
  if (!split_watchdog_check()) {
    sync_master.valid |= VALID_WATCHDOG;
    sync_master.watchdog = true;
  }
}
static void transport_master_finish_watchdog(msg_t rc) {
  bool okay = rc == MSG_OK;
  split_watchdog_update(okay);
}
static void transport_slave_update_watchdog(void) {
  split_watchdog_update(sync_master.watchdog);
}
#else
#define transport_master_prepare_watchdog() do { } while (0)
#define transport_master_finish_watchdog(x) do { } while (0)
#define transport_slave_update_watchdog() do { } while (0)
#endif

////////////////////////////////////////////////////
// ACTIVITY

#ifdef SPLIT_ACTIVITY_ENABLE
static void transport_master_prepare_activity(void) {
  static uint32_t last_update = 0;
  split_slave_activity_sync_t activity_sync;
  bool changed = false;

  activity_sync.matrix_timestamp          = last_matrix_activity_time();
  activity_sync.encoder_timestamp         = last_encoder_activity_time();
  activity_sync.pointing_device_timestamp = last_pointing_device_activity_time();

  changed = memcmp(&sync_master.activity, &activity_sync, sizeof(activity_sync)) != 0;
  if (changed || timer_elapsed32(last_update) >= FORCED_SYNC_THROTTLE_MS) {
    sync_master.activity = activity_sync;
    sync_master.valid |= VALID_ACTIVITY;
    last_update = sync_timer_read32();
  }
}
static void transport_slave_update_activity(void) {
  if (sync_master.valid & VALID_ACTIVITY) {
    split_slave_activity_sync_t *activity = &sync_master.activity;
    sync_master.valid &= ~VALID_ACTIVITY;
    set_activity_timestamps(activity->matrix_timestamp, activity->encoder_timestamp, activity->pointing_device_timestamp);
  }
}
#else
#define transport_master_prepare_activity() do { } while (0)
#define transport_slave_update_activity() do { } while (0)
#endif

////////////////////////////////////////////////////
// TRANSPORT

#define SLAVE_TIMEOUT TIME_MS2I(100)
#define SLAVE_I2C_ADDRESS 0x13

static uint8_t split_buf[64] __attribute__((aligned(8)));

static const I2CConfig I2CCfg = {
  .timingr = 0x00702991, /*0x10909CEC*/ /* From STM32CubeMX */
  .cr1 = 0,
  .cr2 = 0,
};

/**
 * @brief This thread runs on the slave and responds to transactions initiated
 * by the master.
 */
static THD_WORKING_AREA(waSlaveThread, 256);
static THD_FUNCTION(SlaveThread, arg)
{
  unsigned rcvd;
  msg_t rc;

  (void)arg;
  chRegSetThreadName("split_protocol_tx_rx");

resetup:
  /* Setup I2C. */
  i2cStart(&I2CD1, &I2CCfg);
  i2cSlaveMatchAddress(&I2CD1, SLAVE_I2C_ADDRESS);

  while (true) {
    /* Wait for a master transmission */
    rc = i2cSlaveReceiveTimeout(&I2CD1, split_buf, sizeof(split_buf), TIME_INFINITE);
    i2cCountError(rc);
    if (rc == MSG_OK) {
      unsigned remain = dmaStreamGetTransactionSize(I2CD1.dmarx);
      rcvd = sizeof(split_buf) - remain;
    } else {
      rcvd = 0;
    }
    /* If the master needs a reply */
    if (i2cSlaveIsAnswerRequired(&I2CD1)) {
      /* Send matrix */
      rc = i2cSlaveTransmitTimeout(&I2CD1, sync_matrix, sizeof(sync_matrix), SLAVE_TIMEOUT);
      if (rc == MSG_OK)
        palClearLine(LINE_SIDE_IRQ);
      i2cCountError(rc);
    }
    /* If received something from the master, update sync_master. */
    if (rcvd) {
      split_shared_memory_lock();
      memcpy(&sync_master, split_buf, MIN(rcvd, sizeof(sync_master)));
      split_shared_memory_unlock();
    }
    if (rc == MSG_TIMEOUT) {
        i2cStop(&I2CD1);
        goto resetup;
    }
  }
}

void transport_slave_init(void) {
  /* Just create slave thread. It will finish init. */
  chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), NORMALPRIO + 3, SlaveThread, NULL);
}

void transport_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[])
{
  bool changed = false;
  for (uint8_t i = 0; i < ROWS_PER_HAND; ++i) {
    if (sync_matrix[i] != slave_matrix[i]) {
      sync_matrix[i] = slave_matrix[i];
      changed = true;
    }
  }
  if (changed) {
    /* Signal master slave matrix has changed. */
    palSetLine(LINE_SIDE_IRQ);
  }

  /* Handle changes sent by master to slave */
  split_shared_memory_lock();
  transport_slave_update_timer();
  transport_slave_update_layer();
  transport_slave_update_leds();
  transport_slave_update_mods();
  transport_slave_update_rgb_matrix();
  transport_slave_update_oled();
  transport_slave_update_watchdog();
  transport_slave_update_activity();
  split_shared_memory_unlock();
}

void transport_master_init(void) {
  /* Setup LINE_SIDE_IRQ GPIO as input. */
  palSetLineMode(LINE_SIDE_IRQ, PAL_MODE_INPUT_PULLDOWN);
}

bool transport_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[])
{
  msg_t rc = MSG_OK;
  bool matrix_sync = false;

  /* Setup sync_master. This structure is only accessed by this function, so
   * so no lock is required. */
  sync_master.valid = 0;
  transport_master_prepare_timer();
  transport_master_prepare_layer();
  transport_master_prepare_leds();
  transport_master_prepare_mods();
  transport_master_prepare_rgb_matrix();
  transport_master_prepare_oled();
  transport_master_prepare_activity();
  transport_master_prepare_watchdog();

  /* synchronous I2C write/read. */
  matrix_sync = palReadLine(LINE_SIDE_IRQ);
  if (sync_master.valid || matrix_sync) {
    uint8_t *dest = matrix_sync ? sync_matrix : NULL;
    size_t size = dest ? sizeof(sync_matrix) : 0;
    i2cStart(&I2CD1, &I2CCfg);
    if (dest && !sync_master.valid) {
      /* Just read sync_matrix. */
      rc = i2cMasterReceiveTimeout(&I2CD1, SLAVE_I2C_ADDRESS, dest, size, SLAVE_TIMEOUT);
      i2cCountError(rc);
    } else if (sync_master.valid) {
      /* Write sync_master and read sync_matrix if needed. */
      /* TODO: Transfer only the required bytes according to valid bytes. */
      rc = i2cMasterTransmitTimeout(&I2CD1, SLAVE_I2C_ADDRESS, (uint8_t *)&sync_master, sizeof(sync_master), dest, size, SLAVE_TIMEOUT);
      i2cCountError(rc);
    }
    i2cStop(&I2CD1);
    if (rc != MSG_OK) {
      return false;
    }
  }
  /* Update watchdog on successful transaction. */
  transport_master_finish_watchdog(rc);
  /* Always update slave matrix because matrix_post_scan() will compare itself to detect change. */
  memcpy(slave_matrix, sync_matrix, sizeof(sync_matrix));
  return true;
}
