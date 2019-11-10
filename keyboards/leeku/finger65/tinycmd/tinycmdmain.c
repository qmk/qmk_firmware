#include <stdio.h>
#include <string.h>
#include "tinycmd.h"
#include "tinycmdpkt.h"
#include "i2c.h"
#include "config.h"
#include <util/delay.h>     /* for _delay_ms() */

uint8_t localBuffer[0x4B]; // I2C_WRSIZE

#define WAIT_RETRY      10

#define LEDMODE_INDEX_MAX       3
#define LED_BLOCK_MAX           5
#define LEDMODE_ARRAY_SIZE      (LEDMODE_INDEX_MAX*LED_BLOCK_MAX)

static uint8_t waitResponse(uint8_t cmd)
{
    tinycmd_rsp_type *p_rsp = 0;
    uint8_t i, ret = 0;
    for(i = 0; i < WAIT_RETRY; i++)
    {
        // then read n byte(s) from the selected MegaIO register
        i2c_recv(I2C_TARGET_ADDR, (uint8_t*) localBuffer, sizeof(tinycmd_rsp_type));
        p_rsp = (tinycmd_rsp_type *)localBuffer;
        if(p_rsp->cmd_code == cmd)
        {
            ret = 1;
            break;
        }
        _delay_us(100);     // wait 100us
    }
    return ret;
}

static uint8_t sendCommand(tinycmd_pkt_req_type *p_req, uint8_t len, uint8_t rsp)
{
    uint8_t ret = 0;
    uint8_t cmd = p_req->cmd_code;
    // If need to wait response from the slave
    if(rsp)
    {
      p_req->cmd_code |= TINY_CMD_RSP_MASK;
      if(i2c_send(I2C_TARGET_ADDR, (uint8_t *)p_req, len))
      {
        ret = waitResponse(cmd & TINY_CMD_CMD_MASK);
      }
    }
    else
    {
      i2c_send(I2C_TARGET_ADDR, (uint8_t *)p_req, len);
      ret = 1;
    }
    return ret;
}

uint8_t tinycmd_config(uint8_t rgb_num, uint16_t rgb_limit, uint8_t rsp)
{
    tinycmd_config_req_type *p_cfg_req = (tinycmd_config_req_type *)localBuffer;
    uint8_t ret = 0;

    p_cfg_req->cmd_code = TINY_CMD_CONFIG_F;
    p_cfg_req->pkt_len = sizeof(tinycmd_config_req_type);
    p_cfg_req->rgb_num = rgb_num;
    p_cfg_req->rgb_limit = rgb_limit;

    ret = sendCommand((tinycmd_pkt_req_type *)p_cfg_req, p_cfg_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_ver(uint8_t rsp)
{
    tinycmd_ver_req_type *p_ver_req = (tinycmd_ver_req_type *)localBuffer;
    uint8_t ret = 0;

    p_ver_req->cmd_code = TINY_CMD_VER_F;
    p_ver_req->pkt_len = sizeof(tinycmd_ver_req_type);

    ret = sendCommand((tinycmd_pkt_req_type *)p_ver_req, p_ver_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_reset(uint8_t type, uint8_t rsp)
{
    tinycmd_reset_req_type *p_reset_req = (tinycmd_reset_req_type *)localBuffer;
    //uint8_t ret = 0;

    p_reset_req->cmd_code = TINY_CMD_RESET_F;
    p_reset_req->pkt_len = sizeof(tinycmd_reset_req_type);
    p_reset_req->type = 0;

    sendCommand((tinycmd_pkt_req_type *)p_reset_req, p_reset_req->pkt_len, rsp);

    return rsp;
}

uint8_t tinycmd_three_lock(uint8_t num, uint8_t caps, uint8_t scroll, uint8_t rsp)
{
    uint8_t lock = 0;
    tinycmd_three_lock_req_type *p_three_lock_req = (tinycmd_three_lock_req_type *)localBuffer;
    uint8_t ret = 0;

    p_three_lock_req->cmd_code = TINY_CMD_THREE_LOCK_F;
    p_three_lock_req->pkt_len = sizeof(tinycmd_three_lock_req_type);
    if(num)
    {
        lock |= (1<<2);
    }
    if(caps)
    {
        lock |= (1<<1);
    }
    if(scroll)
    {
        lock |= (1<<0);
    }
    p_three_lock_req->lock = lock;

    ret = sendCommand((tinycmd_pkt_req_type *)p_three_lock_req, p_three_lock_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_dirty(uint8_t down)
{
    tinycmd_dirty_req_type *p_dirty_req = (tinycmd_dirty_req_type *)localBuffer;

    if(down)
    {
        p_dirty_req->cmd_code = TINY_CMD_DIRTY_F | TINY_CMD_KEY_MASK;
    }
    else
    {
        p_dirty_req->cmd_code = TINY_CMD_DIRTY_F;
    }
    sendCommand((tinycmd_pkt_req_type *)p_dirty_req, sizeof(tinycmd_dirty_req_type), 0);
    return 1;
}

uint8_t tinycmd_sleep(uint8_t sleep, uint8_t rsp)
{
    tinycmd_sleep_req_type *p_sleep_req = (tinycmd_sleep_req_type *)localBuffer;
    //uint8_t ret = 0;

    p_sleep_req->cmd_code = TINY_CMD_SLEEP_F;
    p_sleep_req->pkt_len = sizeof(tinycmd_sleep_req_type);

    sendCommand((tinycmd_pkt_req_type *)p_sleep_req, p_sleep_req->pkt_len, rsp);

    return 1;
}

uint8_t tinycmd_rgb_all(uint8_t on, uint8_t r, uint8_t g, uint8_t b, uint8_t rsp)
{
    tinycmd_rgb_all_req_type *p_rgb_all_req = (tinycmd_rgb_all_req_type *)localBuffer;
    uint8_t ret = 0;

    p_rgb_all_req->cmd_code = TINY_CMD_RGB_ALL_F;
    p_rgb_all_req->pkt_len = sizeof(tinycmd_rgb_all_req_type);

    p_rgb_all_req->on = on;

    p_rgb_all_req->led.g = g;
    p_rgb_all_req->led.r = r;
    p_rgb_all_req->led.b = b;

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_all_req, p_rgb_all_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_rgb_pos(uint8_t pos, uint8_t r, uint8_t g, uint8_t b, uint8_t rsp)
{
    tinycmd_rgb_pos_req_type *p_rgb_pos_req = (tinycmd_rgb_pos_req_type *)localBuffer;
    uint8_t ret = 0;

    p_rgb_pos_req->cmd_code = TINY_CMD_RGB_POS_F;
    p_rgb_pos_req->pkt_len = sizeof(tinycmd_rgb_pos_req_type);

    p_rgb_pos_req->pos = pos;

    p_rgb_pos_req->led.g = g;
    p_rgb_pos_req->led.r = r;
    p_rgb_pos_req->led.b = b;

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_pos_req, p_rgb_pos_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_rgb_range(uint8_t num, uint8_t offset, uint8_t r, uint8_t g, uint8_t b, uint8_t rsp)
{
    tinycmd_led_type led;
    tinycmd_rgb_range_req_type *p_rgb_range_req = (tinycmd_rgb_range_req_type *)localBuffer;
    uint8_t i, ret = 0;

    //overflow
    if((offset + num) > TINYCMD_LED_MAX)
        return ret;

    p_rgb_range_req->cmd_code = TINY_CMD_RGB_RANGE_F;
    p_rgb_range_req->pkt_len = sizeof(tinycmd_rgb_range_req_type);

    p_rgb_range_req->num = num;
    p_rgb_range_req->offset = offset;

    led.g = g;
    led.r = r;
    led.b = b;

    for(i = 0; i < p_rgb_range_req->num; i++)
    {
       p_rgb_range_req->led[i] = led;
    }

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_range_req, p_rgb_range_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_rgb_buffer(uint8_t num, uint8_t offset, uint8_t *data, uint8_t rsp)
{
    tinycmd_rgb_buffer_req_type *p_rgb_buffer_req = (tinycmd_rgb_buffer_req_type *)localBuffer;
    uint8_t ret = 0;

    //overflow
    if((offset + num) > TINYCMD_LED_MAX)
        return ret;

    p_rgb_buffer_req->cmd_code = TINY_CMD_RGB_BUFFER_F;
    p_rgb_buffer_req->pkt_len = sizeof(tinycmd_rgb_buffer_req_type);

    p_rgb_buffer_req->num = num;
    p_rgb_buffer_req->offset = offset;

    memcpy(p_rgb_buffer_req->data, data, num*3);

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_buffer_req, p_rgb_buffer_req->pkt_len, rsp);

    return ret;
}


uint8_t tinycmd_rgb_set_effect(uint8_t index, uint8_t rsp)
{
    tinycmd_rgb_set_effect_req_type *p_rgb_set_effect_req = (tinycmd_rgb_set_effect_req_type *)localBuffer;
    uint8_t ret = 0;

    p_rgb_set_effect_req->cmd_code = TINY_CMD_RGB_SET_EFFECT_F;
    p_rgb_set_effect_req->pkt_len = sizeof(tinycmd_rgb_set_effect_req_type);
    p_rgb_set_effect_req->index = index;

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_set_effect_req, p_rgb_set_effect_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_rgb_set_preset(uint8_t index, rgb_effect_param_type *p_param, uint8_t rsp)
{
    tinycmd_rgb_set_preset_req_type *p_rgb_set_preset_req = (tinycmd_rgb_set_preset_req_type *)localBuffer;
    uint8_t ret = 0;
    if(index >= RGB_EFFECT_MAX)
        index = RGB_EFFECT_BASIC;

    p_rgb_set_preset_req->cmd_code = TINY_CMD_RGB_SET_PRESET_F;
    p_rgb_set_preset_req->pkt_len = sizeof(tinycmd_rgb_set_preset_req_type);
    p_rgb_set_preset_req->index = index;
    memcpy(&p_rgb_set_preset_req->effect_param, p_param, sizeof(rgb_effect_param_type));

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_set_preset_req, p_rgb_set_preset_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_rgb_effect_speed(uint16_t speed, uint8_t rsp)
{
    tinycmd_rgb_effect_speed_req_type *p_rgb_effect_speed_req = (tinycmd_rgb_effect_speed_req_type *)localBuffer;
    uint8_t ret = 0;

    p_rgb_effect_speed_req->cmd_code = TINY_CMD_RGB_EFFECT_SPEED_F;
    p_rgb_effect_speed_req->pkt_len = sizeof(tinycmd_rgb_effect_speed_req_type);
    p_rgb_effect_speed_req->speed = speed;

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_effect_speed_req, p_rgb_effect_speed_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_rgb_effect_on(uint8_t on, uint8_t rsp)
{
    tinycmd_rgb_effect_on_req_type *p_rgb_effect_on_req = (tinycmd_rgb_effect_on_req_type *)localBuffer;
    uint8_t ret = 0;

    p_rgb_effect_on_req->cmd_code = TINY_CMD_RGB_EFFECT_ON_F;
    p_rgb_effect_on_req->pkt_len = sizeof(tinycmd_rgb_effect_on_req_type);
    p_rgb_effect_on_req->on = on;

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_effect_on_req, p_rgb_effect_on_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_led_level(uint8_t channel, uint8_t level, uint8_t rsp)
{
    tinycmd_led_level_req_type *p_led_level_req = (tinycmd_led_level_req_type *)localBuffer;
    uint8_t ret = 0;

    p_led_level_req->cmd_code = TINY_CMD_LED_LEVEL_F;
    p_led_level_req->pkt_len = sizeof(tinycmd_led_level_req_type);
    p_led_level_req->channel = channel;
    p_led_level_req->level = level;

    ret = sendCommand((tinycmd_pkt_req_type *)p_led_level_req, p_led_level_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_led_set_effect(uint8_t index, uint8_t rsp)
{
    tinycmd_led_set_effect_req_type *p_rgb_set_effect_req = (tinycmd_led_set_effect_req_type *)localBuffer;
    uint8_t ret = 0;

    p_rgb_set_effect_req->cmd_code = TINY_CMD_LED_SET_EFFECT_F;
    p_rgb_set_effect_req->pkt_len = sizeof(tinycmd_led_set_effect_req_type);
    p_rgb_set_effect_req->preset = index;

    ret = sendCommand((tinycmd_pkt_req_type *)p_rgb_set_effect_req, p_rgb_set_effect_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_led_set_preset(uint8_t preset, uint8_t block, uint8_t effect, uint8_t rsp)
{
    tinycmd_led_set_preset_req_type *p_led_set_preset_mode_req = (tinycmd_led_set_preset_req_type *)localBuffer;
    uint8_t ret = 0;

    p_led_set_preset_mode_req->cmd_code = TINY_CMD_LED_SET_PRESET_F;
    p_led_set_preset_mode_req->pkt_len = sizeof(tinycmd_led_set_preset_req_type);
    p_led_set_preset_mode_req->preset = preset;
    p_led_set_preset_mode_req->block = block;
    p_led_set_preset_mode_req->effect = effect;

    ret = sendCommand((tinycmd_pkt_req_type *)p_led_set_preset_mode_req, p_led_set_preset_mode_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_led_config_preset(uint8_t *p_led_mode_array, uint8_t rsp)
{
    tinycmd_led_config_preset_req_type *p_led_cfg_preset_req = (tinycmd_led_config_preset_req_type *)localBuffer;
    uint8_t i, ret = 0;

    p_led_cfg_preset_req->cmd_code = TINY_CMD_LED_CONFIG_PRESET_F;
    p_led_cfg_preset_req->pkt_len = sizeof(tinycmd_led_config_preset_req_type);

    for(i = 0; i < LEDMODE_ARRAY_SIZE; i++)
    {
        p_led_cfg_preset_req->data[i] = p_led_mode_array[i];
    }

    ret = sendCommand((tinycmd_pkt_req_type *)p_led_cfg_preset_req, p_led_cfg_preset_req->pkt_len, rsp);

    return ret;
}

uint8_t tinycmd_led_effect_on(uint8_t on, uint8_t rsp)
{
    tinycmd_led_effect_on_req_type *p_led_effect_on_req = (tinycmd_led_effect_on_req_type *)localBuffer;
    uint8_t ret = 0;

    p_led_effect_on_req->cmd_code = TINY_CMD_LED_EFFECT_ON_F;
    p_led_effect_on_req->pkt_len = sizeof(tinycmd_led_effect_on_req_type);
    p_led_effect_on_req->on = on;

    ret = sendCommand((tinycmd_pkt_req_type *)p_led_effect_on_req, p_led_effect_on_req->pkt_len, rsp);

    return ret;
}
