#ifndef TINYCMD_H
#define TINYCMD_H

#define TINY_CMD_CMD_MASK               0x3F
#define TINY_CMD_RSP_MASK               0x80
#define TINY_CMD_KEY_MASK               0x40

// System Command
#define TINY_CMD_CONFIG_F               0
#define TINY_CMD_VER_F                  1
#define TINY_CMD_RESET_F                2
#define TINY_CMD_THREE_LOCK_F           3
#define TINY_CMD_DIRTY_F                4
#define TINY_CMD_SLEEP_F                5

// RGB Command
#define TINY_CMD_RGB_ALL_F              20
#define TINY_CMD_RGB_POS_F              21
#define TINY_CMD_RGB_RANGE_F            22
#define TINY_CMD_RGB_BUFFER_F           23
#define TINY_CMD_RGB_SET_EFFECT_F       24
#define TINY_CMD_RGB_SET_PRESET_F       25
#define TINY_CMD_RGB_EFFECT_SPEED_F     26
#define TINY_CMD_RGB_EFFECT_ON_F        27

// LED Command
#define TINY_CMD_LED_LEVEL_F            40
#define TINY_CMD_LED_SET_EFFECT_F       41
#define TINY_CMD_LED_SET_PRESET_F       42
#define TINY_CMD_LED_CONFIG_PRESET_F    43
#define TINY_CMD_LED_EFFECT_ON_F        44

#define TINY_CMD_MAX                    127



#endif // TINYCMD_H

