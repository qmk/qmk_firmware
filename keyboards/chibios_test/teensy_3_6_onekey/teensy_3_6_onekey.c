#include "teensy_3_6_onekey.h"

/*===========================================================================*/
/* Card insertion monitor.                                                   */
/*===========================================================================*/

#if HAL_USE_SDC
/*
 * Working area for SDHC driver.
 */
static uint8_t sd_scratchpad[512];

/*
 * SDIO configuration.
 */
static const SDCConfig sdccfg = {
  sd_scratchpad,
  SDC_MODE_4BIT
};

static bool init_done = FALSE;
static bool fs_ready = FALSE;
mutex_t fs_mutex;

static inline bool is_fs_ready(void) {
  bool res;
  chMtxLock(&fs_mutex);
  res = fs_ready;
  chMtxUnlock(&fs_mutex);
  return res;
}

static inline void fs_is_ready(bool res) {
  chMtxLock(&fs_mutex);
  fs_ready = res;
  chMtxUnlock(&fs_mutex);
}

static FATFS SDC_FS;

static FRESULT scan_files(char *path) {
  static FILINFO fno;
  FRESULT res;
  DIR dir;
  size_t i;
  char *fn;
  char buf[80];

  debug_enable = true;
  debug_matrix = true;

  if(!init_done) local_fatfs_init();

  if(!is_fs_ready()) {
    print("Can't scan files, fs not ready!\n");
    return FR_NOT_READY;
  }

  res = f_opendir(&dir, path);
  if (res == FR_OK) {
    print("Scanning files...\n");
    i = strlen(path);
    while (((res = f_readdir(&dir, &fno)) == FR_OK) && fno.fname[0]) {
      if (FF_FS_RPATH && fno.fname[0] == '.')
        continue;
      fn = fno.fname;
      if (fno.fattrib & AM_DIR) {
        *(path + i) = '/';
        strcpy(path + i + 1, fn);
        res = scan_files(path);
        *(path + i) = '\0';
        if (res != FR_OK)
          break;
      }
      else {
        sprintf(buf, "%s/%s\r\n", path, fn);
        print(buf);
      }
    }
  }
  else {
    print("opendir FAILED\n");
  }
  return res;
}

int local_fatfs_init(void) {
  FRESULT err;
  char buf[64];
  chMtxObjectInit(&fs_mutex);
  sdcStart(&SDCD1, &sdccfg);
  init_done = true;

  if ((err=sdcConnect(&SDCD1))){
    sprintf(buf, "Connect failed with code %d\n", err);
    print(buf);
    return -1;
  }

  err = f_mount(&SDC_FS, "/", 1);
  if (err != FR_OK) {
    print("Mount failed\n");
    sdcDisconnect(&SDCD1);
    return -1;
  }
  else {
  }
  fs_is_ready(TRUE);
  return 0;
}
#endif //#if defined(HAL_USE_SDC)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_CAPS:
      if (record->event.pressed) {
        print("Keypress\n");
#if HAL_USE_SDC
        scan_files("/");
#endif
      }
      break;
  }
  return true;
}
