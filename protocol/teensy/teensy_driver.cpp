#include "WProgram.h"
#include "host.h"
#include "host_driver.h"
#include "teensy_driver.h"
#include "led.h"
#include "debug.h"

/* Host driver */
static uint8_t teensy_keyboard_leds(void);
static void teensy_send_keyboard(report_keyboard_t *report);
static void teensy_send_mouse(report_mouse_t *report);
static void teensy_send_system(uint16_t data);
static void teensy_send_consumer(uint16_t data);

host_driver_t teensy_driver = {
    teensy_keyboard_leds,
    teensy_send_keyboard,
    teensy_send_mouse,
    teensy_send_system,
    teensy_send_consumer
};

static uint8_t teensy_keyboard_leds(void)
{
    return keyboard_leds;
}

static void teensy_send_keyboard(report_keyboard_t *report)
{
    keyboard_modifier_keys = report->mods;
    keyboard_keys[0] = report->keys[0];
    keyboard_keys[1] = report->keys[1];
    keyboard_keys[2] = report->keys[2];
    keyboard_keys[3] = report->keys[3];
    keyboard_keys[4] = report->keys[4];
    keyboard_keys[5] = report->keys[5];
    usb_keyboard_send();
}

static void teensy_send_mouse(report_mouse_t *report)
{
    usb_mouse_buttons_state = report->buttons;
    usb_mouse_move(report->x, report->y, report->v);
}

static void teensy_send_system(uint16_t data)
{
}

#define CONSUMER2TEENSY(usage) \
    (usage == AUDIO_MUTE           ? KEY_MEDIA_MUTE       : \
    (usage == AUDIO_VOL_UP         ? KEY_MEDIA_VOLUME_INC : \
    (usage == AUDIO_VOL_DOWN       ? KEY_MEDIA_VOLUME_DEC : \
    (usage == TRANSPORT_NEXT_TRACK ? KEY_MEDIA_NEXT_TRACK : \
    (usage == TRANSPORT_PREV_TRACK ? KEY_MEDIA_PREV_TRACK : \
    (usage == TRANSPORT_STOP       ? KEY_MEDIA_STOP       : \
    (usage == TRANSPORT_STOP_EJECT ? KEY_MEDIA_EJECT      : \
    (usage == TRANSPORT_PLAY_PAUSE ? KEY_MEDIA_PLAY_PAUSE : \
    (usage == AL_CC_CONFIG         ? 0x00  : \
    (usage == AL_EMAIL             ? 0x00  : \
    (usage == AL_CALCULATOR        ? 0x00  : \
    (usage == AL_LOCAL_BROWSER     ? 0x00  : \
    (usage == AC_SEARCH            ? 0x00  : \
    (usage == AC_HOME              ? 0x00  : \
    (usage == AC_BACK              ? 0x00  : \
    (usage == AC_FORWARD           ? 0x00  : \
    (usage == AC_STOP              ? 0x00  : \
    (usage == AC_REFRESH           ? 0x00  : \
    (usage == AC_BOOKMARKS         ? 0x00  : 0)))))))))))))))))))
static void teensy_send_consumer(uint16_t data)
{
    static uint16_t last_data = 0;
    if (data == last_data) return;
    last_data = data;
    
    uint8_t bitmap = CONSUMER2TEENSY(data);
    Keyboard.set_media(bitmap);
    Keyboard.send_now();
}
