/* MKS3 9 键小键盘（RP2040-Zero）QMK 配置
 *
 * 关键点：
 *   1. RGB_MATRIX_SLEEP 由 keyboard.json 里 "rgb_matrix": {"sleep": true} 打开，
 *      主机休眠（USB suspend）时 9 颗主灯自动熄灭，唤醒自动恢复。
 *   2. 板载 GP16 单灯由 mks3_numpad.c 里的独立 PIO 实例驱动，同一时刻一起熄灭。
 */

#pragma once

/* 双击 RST 进 UF2 引导（RP2040-Zero 板载 BOOT 键之外的备用方式） */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

/* 板载单颗 WS2812 */
#ifndef GP16_LED_PIN
#    define GP16_LED_PIN GP16
#endif
#define GP16_ANIM_INTERVAL_MS 40
#define GP16_ANIM_BRIGHTNESS 90

/* 灯光层（第 1 层，keymap.c 里的 _RGB）的层号。
 * 该层激活时板载 GP16 灯会从慢速彩环切成纯白常亮，用来一眼分辨“现在在第 0 层还是第 1 层”。 */
#define MKS3_LIGHT_LAYER 1


/* 9 颗主灯的亮度上限：全白满亮约 540mA，这里限到 95/255≈37% */
#ifndef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 95
#endif
