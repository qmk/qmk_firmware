/* MKS3 10 键小键盘：键盘级行为
 *
 * 1. 上电初始化板载 GP16 单灯；
 * 2. 空闲时让 GP16 慢速彩环流动（对应旧固件的板载灯行为）；
 * 3. 灯光层（第 1 层）被按住 / 打开时，GP16 从彩环切成纯白常亮 —— 用来分辨当前在第几层；
 * 4. 主机休眠 / 唤醒时同步点亮或熄灭（10 颗主灯由 rgb_matrix 的 sleep 选项负责）。
 */

#include "quantum.h"

#include "gp16_led.h"

static bool     gp16_suspended   = false;
static bool     gp16_light_layer = false; /* 上一轮是否处于灯光层 */
static uint16_t gp16_hue         = 0;

void keyboard_post_init_kb(void) {
    gp16_led_init();
    gp16_led_set(0, 0, 0);

    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    static uint32_t last_update = 0;

    if (gp16_suspended || timer_elapsed32(last_update) < GP16_ANIM_INTERVAL_MS) {
        return;
    }
    last_update = timer_read32();

    bool in_light_layer = layer_state_is(MKS3_LIGHT_LAYER);

    if (in_light_layer) {
        /* 灯光层：纯白常亮。只在刚进入时写一次，避免每 40ms 重复刷同一条灯带 */
        if (!gp16_light_layer) {
            gp16_light_layer = true;
            gp16_led_set(GP16_ANIM_BRIGHTNESS, GP16_ANIM_BRIGHTNESS, GP16_ANIM_BRIGHTNESS);
        }
        return;
    }

    /* 非灯光层：慢速彩环 */
    gp16_light_layer = false;
    gp16_hue         = (gp16_hue + 3) & 0xFF;

    hsv_t hsv = {.h = gp16_hue, .s = 255, .v = GP16_ANIM_BRIGHTNESS};
    rgb_t rgb = hsv_to_rgb(hsv);
    gp16_led_set(rgb.r, rgb.g, rgb.b);
}

/* 主机挂起（电脑休眠 / 睡眠）—— 板载灯一起熄灭 */
void suspend_power_down_kb(void) {
    gp16_suspended = true;
    gp16_led_set(0, 0, 0);

    suspend_power_down_user();
}

/* 主机唤醒 —— 交回空闲动画继续跑 */
void suspend_wakeup_init_kb(void) {
    gp16_suspended   = false;
    gp16_light_layer = false; /* 强制下一轮重画一次，防止残留白灯 */
    gp16_hue         = 0;

    suspend_wakeup_init_user();
}
