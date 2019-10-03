#include <stdlib.h>
#include <string.h>

#include "microshell/core/microshell.h"
#include "microshell/core/msconf.h"
#include "microshell/util/msopt.h"
#include "microshell/util/mscmd.h"
#include "microshell/util/ntlibc.h"

#include "debug.h"
#include "print.h"
#include "quantum.h"
#include "rgblight.h"
#include "eeprom.h"

#include "bmp.h"
#include "i2c.h"
#include "cli.h"
#include "bootloader.h"
#include "app_ble_func.h"

#include "apidef.h"
#include "configurator.h"

void cli_puts(char *str);
static MSCMD_USER_RESULT usrcmd_reset(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_advertise(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_bootloader(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_bonding_information(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_delete_bonding(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_help(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_keymap(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_config(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_keystr_conv(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_update_file(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_remove_file(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_debug_enable(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_dump_memory(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_dump_string(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_led_control(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_eeprom_control(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_webconfig_enter(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
static MSCMD_USER_RESULT usrcmd_i2c_test(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);

static MICROSHELL microshell;
static MSCMD mscmd;

static const MSCMD_COMMAND_TABLE table[] = {
    {   "reset",   usrcmd_reset, "Reset system"   },
    {   "adv",   usrcmd_advertise, "Start advertising"   },
    {   "dfu",   usrcmd_bootloader, "Jump to bootloader"   },
    {   "show",   usrcmd_bonding_information, "Show bonded devices"  },
    {   "del",   usrcmd_delete_bonding, "Delete bond information"   },
    {   "help",     usrcmd_help, "Show this message"     },
    {   "map",     usrcmd_keymap, "Show keymap"     },
    {   "conf",     usrcmd_config, "Show config"     },
    {   "conv",     usrcmd_keystr_conv, "Show keymap"     },
    {   "update",     usrcmd_update_file, "Update file"     },
    {   "remove",     usrcmd_remove_file, "Remove file"     },
    {   "debug",     usrcmd_debug_enable, "Debug print setting"     },
    {   "dump",     usrcmd_dump_memory, "Dump memory"     },
    {   "dumps",     usrcmd_dump_string, "Dump memory"     },
    {   "led",     usrcmd_led_control, "LED control"     },
    {   "ee",     usrcmd_eeprom_control, "eeprom control"     },
    {   "web",     usrcmd_webconfig_enter, "Start web config mode"     },
    {   "i2c",     usrcmd_i2c_test, "Test i2c"     },
    // USER_DEFINED_MSCMD,
};

void cli_puts(char *str) {
  BMPAPI->usb.serial_puts((uint8_t*)str, strlen(str));
}
static MSCMD_USER_RESULT usrcmd_reset(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
  BMPAPI->app.reset();
  return 0;
}
static MSCMD_USER_RESULT usrcmd_advertise(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
#ifndef NRF_SEPARATE_KEYBOARD_SLAVE
  char arg[4];
  if (msopt->argc >= 2) {
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    if(arg[0] >='0' && arg[0] <= '9') {
      BMPAPI->ble.advertise(arg[0]-'0');
    }
  } else {
    BMPAPI->ble.advertise(255);
  }
#endif
  return 0;
}

static MSCMD_USER_RESULT usrcmd_bootloader(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
//  bootloader_jump();
  BMPAPI->bootloader_jump();
  return 0;
}

static MSCMD_USER_RESULT usrcmd_bonding_information(MSOPT *msopt,
    MSCMD_USER_OBJECT usrobj) {
  bmp_api_bonding_info_t peers[8];
  uint32_t peer_cnt = sizeof(peers)/sizeof(peers[0]);

  BMPAPI->ble.get_bonding_info(peers, &peer_cnt);

  bmp_api_config_t const * const config = BMPAPI->app.get_config();

 for (int i = 0; i < peer_cnt; i++) {
   // print mac address
   xprintf("%2d:%s:  %02x:%02x:%02x:%02x:%02x:%02x",
                peers[i].id,
                (peers[i].role == 2) ? "Slave " :
                    (config->mode == SPLIT_SLAVE) ? "Master" : "Device",
                peers[i].addr[5], peers[i].addr[4], peers[i].addr[3],
                peers[i].addr[2], peers[i].addr[1], peers[i].addr[0]);
   cli_puts("\r\n");
 }
  return 0;
}

static MSCMD_USER_RESULT usrcmd_delete_bonding(MSOPT *msopt,
    MSCMD_USER_OBJECT usrobj) {
  char arg[4];
  if (msopt->argc >= 2) {
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    if(arg[0] >= '0' && arg[0] <='9') {
      BMPAPI->ble.delete_bond(arg[0]-'0');
    }
  } else {
    BMPAPI->ble.delete_bond(255);
  }
  return 0;
}

static MSCMD_USER_RESULT usrcmd_help(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
  for (int i = 0; i < sizeof(table) / sizeof(table[0]); i++) {
    cli_puts(table[i].argv0);
    microshell.uart_putc('\t');
    cli_puts(table[i].desc);
    cli_puts("\r\n");
  }
  return 0;
}

extern char keymap_string[];
static MSCMD_USER_RESULT usrcmd_keymap(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
  tfp_printf("%s\r\n", keymap_string);
  return 0;
}

static MSCMD_USER_RESULT usrcmd_update_file(MSOPT *msopt,
    MSCMD_USER_OBJECT usrobj) {
  char arg[4];
  if (msopt->argc >= 2) {
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    if(arg[0] >= '0' && arg[0] <='9') {
      BMPAPI->app.save_file(arg[0]-'0');
    }
  }
  return 0;
}

static MSCMD_USER_RESULT usrcmd_remove_file(MSOPT *msopt,
    MSCMD_USER_OBJECT usrobj) {
  char arg[4];
  if (msopt->argc >= 2) {
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    if(arg[0] >= '0' && arg[0] <='9') {
      BMPAPI->app.delete_file(arg[0]-'0');
    }
  }
  return 0;
}

extern char config_string[];
static MSCMD_USER_RESULT usrcmd_config(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
  tfp_printf("%s\r\n", config_string);
  return 0;
}

static MSCMD_USER_RESULT usrcmd_debug_enable(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
    char arg[16];
    if (msopt->argc >= 2)
    {
        msopt_get_argv(msopt, 1, arg, sizeof(arg));
        if (strcmp(arg, "on") == 0)
        {
            debug_enable = true;
            debug_keyboard = true;
            debug_mouse = true;
        }
        else if (strcmp(arg, "off") == 0)
        {
            debug_enable = false;
            debug_keyboard = false;
            debug_mouse = false;
        }
    }
    else
    {
        xprintf("Set debug option [on|off]\r\n");
    }
    return 0;
}

static MSCMD_USER_RESULT usrcmd_dump_memory(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
  char arg[16];
  if (msopt->argc >= 2) {
     msopt_get_argv(msopt, 1, arg, sizeof(arg));
     uint32_t addr = (uint32_t)strtol(arg, NULL, 16);
     uint8_t* p = (uint8_t*)addr;
     char* pstr = (char*)addr;
     if (addr < 0x20000000 || addr > 0x20040000)
     {
       tfp_printf("invalid addr\r\n");
       return 0;
     }
     for(int i=0; i<16; i++){
       for(int j=0; j<8; j++){
       tfp_printf("%02x ", *p++);
       }
       tfp_printf("  ");
       for(int j=0; j<8; j++){
         tfp_printf("%c", *pstr++);
       }
       tfp_printf("\r\n");
     }
  }
  return 0;
}

static MSCMD_USER_RESULT usrcmd_dump_string(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
  char arg[16];
  char string[1025];
  if (msopt->argc >= 2) {
     msopt_get_argv(msopt, 1, arg, sizeof(arg));
     uint32_t addr = (uint32_t)strtol(arg, NULL, 16);
     uint8_t* p = (uint8_t*)addr;
     if (addr < 0x20000000 || addr > 0x20040000)
     {
       tfp_printf("invalid addr\r\n");
       return 0;
     }
     memcpy(string, p, 1024);
     string[1024] = '\0';
     tfp_printf("%s\r\n", string);
  }
  return 0;
}

uint16_t str2quantum_keycode(const char* str, uint32_t len);
static MSCMD_USER_RESULT usrcmd_keystr_conv(MSOPT *msopt, MSCMD_USER_OBJECT usrobj) {
  char str[16];
  uint16_t kc;
  if (msopt->argc >= 2) {
    msopt_get_argv(msopt, 1, str, sizeof(str));
    kc = str2quantum_keycode(str, strlen(str));
    xprintf("%d\r\n", kc);
    // snprintf(str, sizeof(str), "%d", kc);
    // cli_puts(str);
  }
  return 0;
}

static MSCMD_USER_RESULT usrcmd_led_control(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
  char arg[16];
  if (msopt->argc >= 2) {
     msopt_get_argv(msopt, 1, arg, sizeof(arg));
     uint32_t mode = (uint32_t)atoi(arg);
     dprintf("set led mode:%d\r\n", mode);
     if (mode == 0) {
        rgblight_disable();
     } else {
        rgblight_enable();
     }
     rgblight_mode(mode);
  }
  return 0;
}

static inline void show_eeprom()
{
  uint8_t *eeprom;
  uint32_t len;
  eeprom_get_buffer_addr(&eeprom, &len);
  for(int i=0; i<(len+1)/8; i++) {
    for(int j=0; j<8; j++) {
      tfp_printf("%02x ", *eeprom++);
    }
    tfp_printf("\r\n");
  }
}

static MSCMD_USER_RESULT usrcmd_eeprom_control(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
  char arg[16];
  if (msopt->argc >= 2)
  {
    msopt_get_argv(msopt, 1, arg, sizeof(arg));
    if (strcmp(arg, "load") == 0)
    {
      println("load eeprom");
      load_eeprom_emulation_file();
      show_eeprom();
    }
    else if (strcmp(arg, "save") == 0)
    {
      println("save eeprom");
      save_eeprom_emulation_file();
    }
    else if (strcmp(arg, "delete") == 0)
    {
      println("delete eeprom");
    }
    else if (strcmp(arg, "show") == 0)
    {
      println("show eeprom");
      show_eeprom();
    }
  }
  return 0;
}

static MSCMD_USER_RESULT usrcmd_webconfig_enter(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
    BMPAPI->web_config.enter();
    return 0;
}

static MSCMD_USER_RESULT usrcmd_i2c_test(MSOPT *msopt, MSCMD_USER_OBJECT usrobj)
{
    char arg[16];
    uint8_t addr;
    uint8_t reg;
    uint8_t dat;
    uint8_t res;
    if (msopt->argc >= 3) {
        msopt_get_argv(msopt, 1, arg, sizeof(arg));
        addr = (uint8_t)atoi(arg);
        msopt_get_argv(msopt, 2, arg, sizeof(arg));
        reg = (uint8_t)atoi(arg);

        i2c_init();
        res = i2c_readReg(addr, reg, &dat, 1, 0);
        i2c_uninit();

        xprintf("0x%02x:0x%02x res:%d dat:%d\r\n", addr, reg, res, dat);
    }
    else
    {
        xprintf("Invalid option\r\n");
    }
    return 0;
}

void cli_init() {
  microshell_init(&microshell, BMPAPI->usb.serial_putc,
      BMPAPI->usb.serial_byte_to_read,
      BMPAPI->usb.serial_getc,
      NULL);
  mscmd_init(&mscmd, table, sizeof(table) / sizeof(table[0]), NULL);
}

void cli_exec() {
  static char buf[MSCONF_MAX_INPUT_LENGTH];
  static char* cur=buf;
  static bool show_info=false;

  if(!show_info) {
    microshell.uart_putc('>');
    show_info=true;
  }
  cur = microshell_getline(&microshell, buf, cur, MSCONF_MAX_INPUT_LENGTH - (cur-buf));
  if (cur == buf+MSCONF_MAX_INPUT_LENGTH) {
    MSCMD_USER_RESULT r;
    mscmd_execute(&mscmd, buf, &r);
    memset(buf, 0, MSCONF_MAX_INPUT_LENGTH);
    cur = buf;
    show_info=false;
  }
}
