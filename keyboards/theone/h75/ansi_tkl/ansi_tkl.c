#include "ansi_tkl.h"

#include "print.h"

/* MAC or WIN 系统 */
#define LAYER_MAC_MODE (1)
#define LAYER_WIN_MODE (2)

// 用于保存于EEPROM数据
typedef struct {
    uint8_t ee_init_flag;
    uint8_t ee_layer_mode;
    uint8_t ee_side_mode;
    uint8_t ee_side_light;
    uint8_t ee_side_speed;
    uint8_t ee_side_rgb;
    uint8_t ee_side_colour;
    uint8_t retain1;
} user_config_t;

user_config_t user_config;  // 保存在EEPROM中的用户配置信息

/* 侧灯模式 */
#define SIDE_WAVE    0
#define SIDE_MIX     1
#define SIDE_STATIC  2
#define SIDE_BREATH  3
#define SIDE_OFF     4

#define SIDE_LED_NUM 4
const uint8_t side_led_index_tab[SIDE_LED_NUM][2] = {
    {84, 85},
    {83, 86},
    {82, 87},
    {81, 88},
};

// 侧灯相关变量
uint8_t side_mode       = 0;
uint8_t side_light      = 40;  // 默认亮度最大
uint8_t side_speed      = 3;   // 默认速度最快
uint8_t side_rgb        = 1;
uint8_t side_colour     = 0;
uint8_t side_play_point = 0;

uint32_t side_play_cnt   = 0;
uint32_t side_play_timer = 0;

uint8_t r_temp, g_temp, b_temp;

// 特殊按键标志（长按）
bool f_layer_win_press = 0;
bool f_layer_mac_press = 0;
bool f_reset_press     = 0;

/* 外部代码 */
#include "side_rgb_table.h"

#define SIDE_COLOUR_MAX 8
#define LIGHT_SPEED_MAX 4  // 5级速度

uint8_t side_speed_table[5][5] = {
    [SIDE_WAVE]   = {10, 14, 20, 28, 38},
    [SIDE_MIX]    = {10, 14, 20, 28, 38},
    [SIDE_STATIC] = {50, 50, 50, 50, 50},
    [SIDE_BREATH] = {10, 14, 20, 28, 38},
    [SIDE_OFF]    = {50, 50, 50, 50, 50},
};

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}

/*======================================================================
Name:		灯效播放指针控制
Descr:		控制灯效播放方向/显示间隔
======================================================================*/
static void light_point_playing(uint8_t trend, uint8_t step, uint8_t len, uint8_t *point)
{
    if (trend) {
        *point += step;
        if (*point >= len) *point -= len;
    } else {
        *point -= step;
        if (*point >= len) *point = len - (255 - *point) - 1;
    }
}

/*======================================================================
Name:		亮度计算
Descr:		根据输入的亮度值, 计算R/G/B颜色分量
======================================================================*/
static void count_rgb_light(uint8_t light_temp)
{
    uint16_t temp;

    temp   = (light_temp)*r_temp + r_temp;
    r_temp = temp >> 8;

    temp   = (light_temp)*g_temp + g_temp;
    g_temp = temp >> 8;

    temp   = (light_temp)*b_temp + b_temp;
    b_temp = temp >> 8;
}

/*======================================================================
Name:		背光亮度控制
Descr:		0% / 20% / 40% / 60%/ 80% / 100%
======================================================================*/
void light_level_control(uint8_t brighten)
{
    if (brighten)  // 亮度++
    {
        if (side_light == 100) {
            return;
        } else if (side_light >= 80)
            side_light = 100;
        else if (side_light >= 60)
            side_light = 80;
        else if (side_light >= 40)
            side_light = 60;
        else if (side_light >= 20)
            side_light = 40;
        else
            side_light = 20;
    } else  // 亮度--
    {
        if (side_light == 0) {
            return;
        } else if (side_light > 80)
            side_light = 80;
        else if (side_light > 60)
            side_light = 60;
        else if (side_light > 40)
            side_light = 40;
        else if (side_light > 20)
            side_light = 20;
        else
            side_light = 0;
    }
    user_config.ee_side_light = side_light;
    eeconfig_update_user_datablock(&user_config);  // 保存
}

/*======================================================================
Name:   背光速度控制 0,1,2,3,4 (0最快, 4最慢)
======================================================================*/
void light_speed_contol(uint8_t fast)
{
    if ((side_speed) > LIGHT_SPEED_MAX)
        (side_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if ((side_speed)) side_speed--;  // 速度加快
    } else {
        if ((side_speed) < LIGHT_SPEED_MAX) side_speed++;  // 速度减慢
    }
    user_config.ee_side_speed = side_speed;
    eeconfig_update_user_datablock(&user_config);  // 保存
}

#define LIGHT_COLOUR_MAX 8
/*======================================================================
Name:		测光标准色切换
Descr:		依次为红橙黄绿青蓝紫白/彩色循环
======================================================================*/
void side_colour_control(uint8_t dir)
{
    //-------- 背光颜色设置
    if (dir) {  // 顺序切换
        if (side_rgb) {
            side_rgb    = 0;
            side_colour = 0;
        } else {
            side_colour++;
            if (side_colour >= LIGHT_COLOUR_MAX) {
                side_rgb    = 1;
                side_colour = 0;
            }
        }
    } else {  // 逆序切换
        if (side_rgb) {
            side_rgb    = 0;
            side_colour = LIGHT_COLOUR_MAX - 1;
        } else {
            side_colour--;
            if (side_colour >= LIGHT_COLOUR_MAX) {
                side_rgb = 1;
            }
        }
    }
    user_config.ee_side_rgb    = side_rgb;
    user_config.ee_side_colour = side_colour;
    eeconfig_update_user_datablock(&user_config);  // 保存
}

/*======================================================================
Name:		侧光模式切换
======================================================================*/
void side_mode_control(uint8_t dir)
{
    if (dir) {  // 顺序切换
        side_mode++;
        if (side_mode > SIDE_OFF) {
            side_mode = 0;
        }
    } else {  // 逆序切换
        if (side_mode > 0) {
            side_mode--;
        } else {
            side_mode = SIDE_OFF;
        }
    }
    side_play_point          = 0;
    user_config.ee_side_mode = side_mode;
    eeconfig_update_user_datablock(&user_config);  // 保存
}

/*======================================================================
Name:		设置左右侧灯颜色
======================================================================*/
// 设置左侧RGB
void set_left_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < 4; i++) {
        rgb_matrix_set_color(81 + i, r >> 2, g >> 2, b >> 2);
    }
}

// 设置右侧RGB
void set_right_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < 4; i++) {
        rgb_matrix_set_color(85 + i, r >> 2, g >> 2, b >> 2);
    }
}

/**================================================================================================================================
 * 		辅助灯光设计
 ================================================================================================================================*/
// 波浪
static void side_wave_mode_show(void)
{
    uint8_t play_index;

    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    if (side_rgb)
        light_point_playing(0, 3, FLOW_COLOUR_TAB_LEN, &side_play_point);
    else
        light_point_playing(0, 2, WAVE_TAB_LEN, &side_play_point);

    play_index = side_play_point;
    for (int i = 0; i < SIDE_LED_NUM; i++) {
        if (side_rgb) {
            r_temp = flow_rainbow_colour_tab[play_index][0];
            g_temp = flow_rainbow_colour_tab[play_index][1];
            b_temp = flow_rainbow_colour_tab[play_index][2];

            // 移动
            light_point_playing(1, 16, FLOW_COLOUR_TAB_LEN, &play_index);
        } else {
            r_temp = colour_lib[side_colour][0];
            g_temp = colour_lib[side_colour][1];
            b_temp = colour_lib[side_colour][2];

            // 单色移动
            light_point_playing(1, 12, WAVE_TAB_LEN, &play_index);
            count_rgb_light(wave_data_tab[play_index]);
        }
        count_rgb_light(light_value_tab[side_light]);
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

// 光谱
static void side_spectrum_mode_show(void)
{
    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    //------------------------------
    light_point_playing(1, 1, FLOW_COLOUR_TAB_LEN, &side_play_point);

    r_temp = flow_rainbow_colour_tab[side_play_point][0];
    g_temp = flow_rainbow_colour_tab[side_play_point][1];
    b_temp = flow_rainbow_colour_tab[side_play_point][2];

    count_rgb_light(light_value_tab[side_light]);

    for (int i = 0; i < SIDE_LED_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

// 呼吸
static void side_breathe_mode_show(void)
{
    static uint8_t play_point = 0;

    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    //------------------------------
    light_point_playing(0, 1, BREATHE_TAB_LEN, &play_point);

    // 处理颜色
    if (side_rgb) {
        if (play_point == 0) {
            if (++side_play_point >= LIGHT_COLOUR_MAX) side_play_point = 0;
        }

        r_temp = colour_lib[side_play_point][0];
        g_temp = colour_lib[side_play_point][1];
        b_temp = colour_lib[side_play_point][2];
    } else {
        r_temp = colour_lib[side_colour][0];
        g_temp = colour_lib[side_colour][1];
        b_temp = colour_lib[side_colour][2];
    }

    count_rgb_light(breathe_data_tab[play_point]);
    count_rgb_light(light_value_tab[side_light]);

    for (int i = 0; i < SIDE_LED_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

// 静态
static void side_static_mode_show(void)
{
    uint8_t play_index;

    //------------------------------
    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    //------------------------------
    if (side_play_point >= SIDE_COLOUR_MAX) side_play_point = 0;

    for (int i = 0; i < SIDE_LED_NUM; i++) {
        if (side_rgb)  // 彩色常亮
        {
            r_temp = flow_rainbow_colour_tab[16 * i][0];
            g_temp = flow_rainbow_colour_tab[16 * i][1];
            b_temp = flow_rainbow_colour_tab[16 * i][2];
            light_point_playing(0, 24, FLOW_COLOUR_TAB_LEN, &play_index);
        } else  // 单色常亮
        {
            r_temp = colour_lib[side_colour][0];
            g_temp = colour_lib[side_colour][1];
            b_temp = colour_lib[side_colour][2];
        }
        count_rgb_light(light_value_tab[side_light]);
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

void set_side_colour(uint8_t r_temp, uint8_t g_temp, uint8_t b_temp)
{
    for (int i = 0; i < SIDE_LED_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

// 关闭
static void side_off_mode_show(void)
{
    if (side_play_cnt <= side_speed_table[side_mode][side_speed])
        return;
    else
        side_play_cnt -= side_speed_table[side_mode][side_speed];
    if (side_play_cnt > 20) side_play_cnt = 0;

    //------------------------------
    r_temp = 0x00;
    g_temp = 0x00;
    b_temp = 0x00;

    for (int i = 0; i < SIDE_LED_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            rgb_matrix_set_color(side_led_index_tab[i][j], r_temp >> 2, g_temp >> 2, b_temp >> 2);
        }
    }
}

/** ================================================================
    测灯灯效设计
 ================================================================*/
void m_side_led_show(void)
{
    side_play_cnt += timer_elapsed32(side_play_timer);
    side_play_timer = timer_read32();  // store time of last refresh

    switch (side_mode) {
        case SIDE_WAVE:
            side_wave_mode_show();
            break;  // 波浪
        case SIDE_MIX:
            side_spectrum_mode_show();
            break;  // 光谱
        case SIDE_STATIC:
            side_static_mode_show();
            break;  // 常亮
        case SIDE_BREATH:
            side_breathe_mode_show();
            break;  // 呼吸
        case SIDE_OFF:
            side_off_mode_show();
            break;  // 关闭
    }

    // caps lock led 系统指示灯控制  左侧RGB
    if (host_keyboard_led_state().caps_lock) {
        set_left_rgb(0x00, 0xff, 0xff);
    }
}

void rgb_matrix_update_pwm_buffers(void);
void device_reset_show(void)
{
    for (int blink_cnt = 0; blink_cnt < 3; blink_cnt++) {
        rgb_matrix_set_color_all(0x40, 0x40, 0x40);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);

        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);
    }
}

void device_sys_show(void)
{
    if (user_config.ee_layer_mode == LAYER_MAC_MODE) {
        r_temp = 0xff;  // MAC显示白色
        g_temp = 0xff;
        b_temp = 0xff;
    } else {
        r_temp = 0x00;  // WIN显示蓝色
        g_temp = 0x00;
        b_temp = 0xff;
    }

    for (int blink_cnt = 0; blink_cnt < 3; blink_cnt++) {
        set_right_rgb(r_temp, g_temp, b_temp);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);

        set_right_rgb(0, 0, 0);
        rgb_matrix_update_pwm_buffers();
        wait_ms(200);
    }
}

void device_reset_init(void)
{
    side_mode       = 0;  // 侧灯恢复默认设置
    side_light      = 40;
    side_speed      = 3;
    side_rgb        = 1;
    side_colour     = 0;
    side_play_cnt   = 0;
    side_play_point = 0;
    side_play_timer = timer_read32();  // store time of last refresh

    // RGB 恢复出厂设
    rgb_matrix_enable();                                                                   // 先开灯
    rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);                                              // 默认模式
    rgb_matrix_set_speed(255 - RGB_MATRIX_SPD_STEP * 2);                                   // 速度中等
    rgb_matrix_sethsv(255, 255, RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP * 2);  // 色调 饱和 亮度

    default_layer_set(1 << 0);                   // 按键恢复出厂设置
    keymap_config.nkro        = 0;               // mac 无全键无冲
    user_config.ee_layer_mode = LAYER_MAC_MODE;  // MAC层

    // 出厂默认
    user_config.ee_init_flag   = 0xA5;
    user_config.ee_side_mode   = side_mode;
    user_config.ee_side_light  = side_light;
    user_config.ee_side_speed  = side_speed;
    user_config.ee_side_rgb    = side_rgb;
    user_config.ee_side_colour = side_colour;
    eeconfig_update_user_datablock(&user_config);  // 保存
}

/**================================================================
    应用层：按键长按处理
 ================================================================*/
void long_press_key(void)
{
    static uint32_t long_press_timer = 0;
    static uint16_t reset_press_time = 0;
    static uint16_t layer_sw_press_time;  // 系统切换长按计时

    // 100ms间隔
    if (timer_elapsed32(long_press_timer) < 100) return;
    long_press_timer = timer_read32();  // store time of last refresh

    // 长按系统切换
    if (f_layer_mac_press || f_layer_win_press) {
        layer_sw_press_time++;
        if (layer_sw_press_time >= 30) {
            layer_sw_press_time = 0;

            if (f_layer_mac_press) {
                default_layer_set(1 << 0);      // MAC
                keymap_config.nkro        = 0;  // mac 无全键无冲
                user_config.ee_layer_mode = LAYER_MAC_MODE;
            } else if (f_layer_win_press) {
                default_layer_set(1 << 2);      // WIN
                keymap_config.nkro        = 1;  // win 全键无冲
                user_config.ee_layer_mode = LAYER_WIN_MODE;
            }
            f_layer_win_press = 0;
            f_layer_mac_press = 0;

            eeconfig_update_user_datablock(&user_config);  // 保存

            device_sys_show();  // 系统切换，侧灯闪烁3次
        }
    } else {
        layer_sw_press_time = 0;
    }

    // 长按复位按键
    if (f_reset_press) {
        reset_press_time++;
        if (reset_press_time >= 30) {
            reset_press_time = 0;

            f_reset_press = 0;
            eeconfig_init();

            device_reset_show();  // 恢复出厂设置 闪烁3次

            device_reset_init();  // 恢复出厂设置 初始化

            // NVIC_SystemReset();     // 系统复位
            // while(1);			// 取消系统复位
        }
    } else {
        reset_press_time = 0;
    }
}

/** ================================================================
    自定义按键
 ================================================================*/
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    // 处理自定义按键功能
    switch (keycode) {
        //------------------------  MAC按键
        // 任务调度按键
        case MAC_TASK: {
            if (record->event.pressed) {
                host_consumer_send(0x029F);
            } else {
                host_consumer_send(0);
            }
            return false;
        }
        // 搜索按键
        case MAC_SEARCH: {
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code_delay(KC_SPACE, 50);
                unregister_code(KC_LGUI);
            }
            return false;
        }
        // 语音按键
        case MAC_VOICE: {
            if (record->event.pressed) {
                host_consumer_send(0xcf);
            } else {
                host_consumer_send(0);
            }
            return false;
        }
        // 启动台
        case MAC_DNT: {
            if (record->event.pressed) {
                host_consumer_send(0x02A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        }

        //------------------------  测灯按键
        // 测灯亮度++
        case SIDE_VAI: {
            if (record->event.pressed) {
                // light_level_control(1, &side_light);
                light_level_control(1);
            }
            return false;
        }
        // 测灯亮度--
        case SIDE_VAD: {
            if (record->event.pressed) {
                // light_level_control(0, &side_light);
                light_level_control(0);
            }
            return false;
        }
        // 测灯模式切换
        case SIDE_MOD: {
            if (record->event.pressed) {
                // side_mode++;
                // if (side_mode >= SIDE_OFF + 1) side_mode = 0;

                // side_play_point = 0;
                side_mode_control(1);
            }
            return false;
        }
        // 测灯颜色切换
        case SIDE_HUI: {
            if (record->event.pressed) {
                side_colour_control(1);
            }
            return false;
        }
        // 测灯速度加快
        case SIDE_SPI: {
            if (record->event.pressed) {
                // light_speed_contol(1, &side_speed);
                light_speed_contol(1);
            }
            return false;
        }
        // 测灯速度减慢
        case SIDE_SPD: {
            if (record->event.pressed) {
                // light_speed_contol(0, &side_speed);
                light_speed_contol(0);
            }
            return false;
        }

        //------------------------  系统按键
        // win系统
        case SYS_WIN: {
            if (record->event.pressed) {
                f_layer_win_press = 1;
            } else {
                f_layer_win_press = 0;
            }
            return false;
        }
        // MAC系统
        case SYS_MAC: {
            if (record->event.pressed) {
                f_layer_mac_press = 1;
            } else {
                f_layer_mac_press = 0;
            }
            return false;
        }
        // 复位按键
        case DEV_RESET: {
            if (record->event.pressed) {
                f_reset_press = 1;
            } else {
                f_reset_press = 0;
            }
            return false;
        }
        default:
            return true;
    }
    return true;
};

/** ================================================================
 * @brief   上电恢复SYS_LAYER
 * ================================================================*/
void sys_layer_init(void)
{
    eeconfig_read_user_datablock(&user_config);

    if (user_config.ee_init_flag != 0xA5) {
        rgb_matrix_sethsv(255, 255, RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP * 2);  // 色调 饱和 亮度
        user_config.ee_init_flag   = 0xA5;
        user_config.ee_layer_mode  = LAYER_MAC_MODE;
        user_config.ee_side_mode   = side_mode;
        user_config.ee_side_light  = side_light;
        user_config.ee_side_speed  = side_speed;
        user_config.ee_side_rgb    = side_rgb;
        user_config.ee_side_colour = side_colour;
        eeconfig_update_user_datablock(&user_config);
    } else {
        side_mode   = user_config.ee_side_mode;
        side_light  = user_config.ee_side_light;
        side_speed  = user_config.ee_side_speed;
        side_rgb    = user_config.ee_side_rgb;
        side_colour = user_config.ee_side_colour;
    }

    if (user_config.ee_layer_mode == LAYER_MAC_MODE) {
        default_layer_set(1 << 0);  // MAC
        keymap_config.nkro = 0;     // mac 无全键无冲
    } else if (user_config.ee_layer_mode == LAYER_WIN_MODE) {
        default_layer_set(1 << 2);  // WIN
        keymap_config.nkro = 1;     // win 全键无冲
    } else {
        user_config.ee_layer_mode = LAYER_MAC_MODE;
        default_layer_set(1 << 0);  // MAC
        keymap_config.nkro = 0;     // mac 无全键无冲
        eeconfig_update_user_datablock(&user_config);
    }
}

// ====================================================================
// ====================================================================
// 初始化调用一次
void keyboard_post_init_user(void)
{
    // debug_enable = true;

    sys_layer_init();  // 初始化默认按键层

    // 关灯后，重新插拔usb，第一个灯异常，在这里重新刷一遍buffer
    rgb_matrix_set_color_all(0x00, 0x00, 0x00);
    rgb_matrix_update_pwm_buffers();
}

// 指示灯处理
bool rgb_matrix_indicators_user(void)
{
    // 侧灯放在此处理，关灯后该指示灯函数不再调用
    m_side_led_show();  // 测灯灯效设计

    return true;
}

// 该函数在所有 QMK 处理结束、开始下一次迭代之前被调用。可以放用户循环处理程序。
void housekeeping_task_user(void)
{
    long_press_key();  // 按键长按处理
}
