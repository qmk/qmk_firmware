/*
  Copyright (C) 2020 Ein Terakawa

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#include <string.h>

#include "hal.h"
#include "ssd1306.h"

/* timeout value must be increased for i2cclk less than its default, 100kHz. */
#define CMD_TRANSMIT_TIMEOUT TIME_MS2I(10)
#define DATA_TRANSMIT_TIMEOUT TIME_MS2I(100)

#define CTRL_CMD_STREAM 0x00
#define CTRL_DATA_STREAM 0x40
#define CTRL_CMD_SINGLE 0x80

#define I2CD ((ssd1306)->config->i2cd)
#define ADDR ((ssd1306)->config->i2caddr)

#define send_cmd(ssd1306, ...)                                      \
    do {                                                            \
        uint8_t buf[] = { CTRL_CMD_STREAM, __VA_ARGS__ };           \
        bool _success = _send_cmd(I2CD, ADDR, buf, sizeof(buf));    \
        if (!_success) goto done;                                   \
    } while(0)

#define send_cmd_static(ssd1306, ...)                                   \
    do {                                                                \
        static const uint8_t buf[] = { CTRL_CMD_STREAM, __VA_ARGS__ };  \
        bool _success = _send_cmd(I2CD, ADDR, buf, sizeof(buf));        \
        if (!_success) goto done;                                       \
    } while(0)

#define CMD1(c) c
#define CMD2(c, d) c, d
#define CMD3(c, d, e) c, d, e

static bool _send_cmd(I2CDriver *i2cd, uint8_t addr, const uint8_t *buf, int len)
{
    msg_t status = i2cMasterTransmitTimeout(
        i2cd, addr, buf, len, NULL, 0, CMD_TRANSMIT_TIMEOUT);

    if (MSG_OK != status) {
        /* i2cflags_t error_code = i2cGetErrors(i2cd); */
        return false;
    }

    return true;
}

#define send_data(ssd1306, buf, len)                        \
    do {                                                    \
        bool _success = _send_data(I2CD, ADDR, buf, len);   \
        if (!_success) goto done;                           \
    } while(0)

static bool _send_data(I2CDriver *i2cd, uint8_t addr, const uint8_t *buf, int len)
{
    msg_t status = i2cMasterTransmitTimeout(
        i2cd, addr, buf, len, NULL, 0, DATA_TRANSMIT_TIMEOUT);

    if (MSG_OK != status) {
        /* i2cflags_t error_code = i2cGetErrors(I2CD); */
        return false;
    }

    return true;
}

static bool ssd1306Init(SSD1306Driver *ssd1306)
{
    bool success = false;
    uint8_t height = ssd1306->config->height;

    /* Initialize buffer */
    memset(ssd1306->buf, 0, SSD1306_PREAMBLE_LENGTH + ssd1306->len);
    ssd1306->buf[0] = CTRL_DATA_STREAM; /* need this byte proceeding the actual data */

    i2cStart(I2CD, ssd1306->config->i2ccfg);

    send_cmd_static(ssd1306,
                    CMD1(SetDisplayOff),
                    CMD2(SetOscFreqAndClkDiv, 0x80));

    send_cmd(ssd1306,
             CMD2(SetMultiplexRatio, height - 1));

    send_cmd_static(ssd1306,
                    CMD2(SetDisplayOffset, 0x00),
                    CMD1(SetDisplayStartLine | 0x00),
                    CMD2(ChargePumpSetting, 0x14),
                    CMD2(SetMemoryAddressMode, 0x00)); /* Horizontal Addressing Mode */

    if (ssd1306->config->rotate180) {
        /* rotate 180 degrees == upside down */
        send_cmd_static(ssd1306,
                        CMD1(SetSegmentRemapReverse),
                        CMD1(SetComScanOrderReverse));
    } else {
        /* no rotation */
        send_cmd_static(ssd1306,
                        CMD1(SetSegmentRemapNormal),
                        CMD1(SetComScanOrderNormal));
    }

    if (height == 64) {
        /* 128x64 module uses AlternativeComMode */
        send_cmd_static(ssd1306,
                        CMD2(SetComPins, 0x12),
                        CMD2(SetContrastControl, 0xCF));
    } else {
        /* 128x32 & 96x16 module uses SequentialComMode */
        send_cmd_static(ssd1306,
                        CMD2(SetComPins, 0x02),
                        CMD2(SetContrastControl, 0x8F));
    }

    send_cmd_static(ssd1306,
                    CMD2(SetPreChargePeriod, 0xF1),
                    CMD2(SetVcomhLevel, 0x40),
                    CMD1(DisableEntireDisplayOn),
                    CMD1(SetNormalDisplay),
                    CMD1(DeactivateScroll),
                    CMD1(SetDisplayOn));

    success = true;

done:
    i2cStop(I2CD);
    return success;
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Update display with framebuffer contents.
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 *
 * @api
 */
bool ssd1306Show(SSD1306Driver *ssd1306)
{
    bool success = false;

    if (ssd1306->state != SSD1306_READY)
        return success;

    i2cStart(I2CD, ssd1306->config->i2ccfg);

    /* Transfer to Graphic Display Data RAM */
    send_cmd(ssd1306,
             CMD3(SetPageAddress, 0, ssd1306->pages - 1),
             CMD3(SetColumnAddress, 0, ssd1306->config->width - 1));

    send_data(ssd1306, ssd1306->buf, ssd1306->len + SSD1306_PREAMBLE_LENGTH);

    success = true;

done:
    i2cStop(I2CD);
    return success;
}

/**
 * @brief   Switch-on display.
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 *
 * @api
 */
bool ssd1306DisplayOn(SSD1306Driver *ssd1306)
{
    bool success = false;

    if (ssd1306->state != SSD1306_READY)
        return success;

    i2cStart(I2CD, ssd1306->config->i2ccfg);
    send_cmd_static(ssd1306, CMD1(SetDisplayOn));
    success = true;
done:
    i2cStop(I2CD);
    return success;
}

/**
 * @brief   Switch-off display.
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 *
 * @api
 */
bool ssd1306DisplayOff(SSD1306Driver *ssd1306)
{
    bool success = false;

    if (ssd1306->state != SSD1306_READY)
        return success;

    i2cStart(I2CD, ssd1306->config->i2ccfg);
    send_cmd_static(ssd1306, CMD1(SetDisplayOff));
    success = true;
done:
    i2cStop(I2CD);
    return success;
}

// SCROLLING FUNCTIONS -----------------------------------------------------

/**
 * @brief   Activate a right-handed scroll for all or part of the display.
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 * @param[in] start      first row
 * @param[in] stop       last row
 *
 * @api
 */
bool ssd1306StartScrollRight(SSD1306Driver *ssd1306, uint8_t start, uint8_t stop)
{
    bool success = false;

    if (ssd1306->state != SSD1306_READY)
        return success;

    i2cStart(I2CD, ssd1306->config->i2ccfg);
    send_cmd(ssd1306, RightHorizontalScroll, 0, start, 0, stop, 0, 255, ActivateScroll);
    success = true;
done:
    i2cStop(I2CD);
    return success;
}

/**
 * @brief   Activate a left-handed scroll for all or part of the display.
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 * @param[in] start      first row
 * @param[in] stop       last row
 *
 * @api
 */
bool ssd1306StartScrollLeft(SSD1306Driver *ssd1306, uint8_t start, uint8_t stop)
{
    bool success = false;

    if (ssd1306->state != SSD1306_READY)
        return success;

    i2cStart(I2CD, ssd1306->config->i2ccfg);
    send_cmd(ssd1306, LeftHorizontalScroll, 0, start, 0, stop, 0, 255, ActivateScroll);
    success = true;
done:
    i2cStop(I2CD);
    return success;
}

/**
 * @brief   Cease a previously-begun scrolling action.
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 *
 * @api
 */
bool ssd1306StopScroll(SSD1306Driver *ssd1306)
{
    bool success = false;

    if (ssd1306->state != SSD1306_READY)
        return success;

    i2cStart(I2CD, ssd1306->config->i2ccfg);
    send_cmd_static(ssd1306, DeactivateScroll);
    success = true;
done:
    i2cStop(I2CD);
    return success;
}

// OTHER HARDWARE SETTINGS -------------------------------------------------

/**
 * @brief  Enable or disable display invert mode (white-on-black vs
 *         black-on-white).
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 * @param[in] inverted   If true, switch to invert mode (black-on-white), else
 *  normal mode (white-on-black).
 *
 * @return True on success else false.
 */
bool ssd1306Invert(SSD1306Driver *ssd1306, bool i)
{
    bool success = false;

    if (ssd1306->state != SSD1306_READY)
        return success;

    i2cStart(I2CD, ssd1306->config->i2ccfg);
    send_cmd(ssd1306, i ? SetInvertDisplay : SetNormalDisplay);
    success = true;
done:
    i2cStop(I2CD);
    return success;
}

/**
 * @brief  Dim the display.
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 * @param[in] contrast   brightness value to set
 *
 * @return True on success else false.
 */
bool ssd1306Dim(SSD1306Driver *ssd1306, uint8_t contrast)
{
    bool success = false;

    if (ssd1306->state != SSD1306_READY)
        return success;

    i2cStart(I2CD, ssd1306->config->i2ccfg);
    send_cmd(ssd1306, CMD2(SetContrastControl, contrast));
    success = true;
done:
    i2cStop(I2CD);
    return success;
}

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p SSD1306Driver object
 *
 * @init
 */
void ssd1306ObjectInit(SSD1306Driver *devp)
{
    devp->config = NULL;
    devp->state  = SSD1306_STOP;
}

/**
 * @brief   Configures and activates SSD1306 Driver peripheral.
 *
 * @param[in] devp      pointer to the @p SSD1306Driver object
 * @param[in] config    pointer to the @p SSD1306Config object
 *
 * @api
 */
void ssd1306Start(SSD1306Driver *devp, const SSD1306Config *config)
{
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert(devp->state == SSD1306_STOP,
                  "ssd1306Start(), invalid state");
    devp->config = config;
    devp->pages = config->height / 8;
    devp->len = devp->pages * config->width;
    devp->buf = config->buf ?:
        chHeapAllocAligned(NULL, devp->len + SSD1306_PREAMBLE_LENGTH, sizeof(int));
    if (devp->buf && ssd1306Init(devp))
        devp->state = SSD1306_READY;
}

/**
 * @brief   Deactivates the SSD1306 Driver peripheral.
 *
 * @param[in] devp       pointer to the @p SSD1306Driver object
 *
 * @api
 */
void ssd1306Stop(SSD1306Driver *devp)
{
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == SSD1306_STOP) || (devp->state == SSD1306_READY),
                  "ssd1306Stop(), invalid state");
    ssd1306DisplayOff(devp);
    if (!devp->config->buf && devp->buf) {
        chHeapFree(devp->buf);
        devp->buf = NULL;
    }
    devp->state = SSD1306_STOP;
}
