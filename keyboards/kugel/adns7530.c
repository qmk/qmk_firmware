/* Copyright 2020 sekigon-gonnoc
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

#include "adns7530.h"
#include "spi.h"
#include "quantum.h"

#define WRITE_TO(addr) (0x80 | addr)
#define READ_FROM(addr) (addr)

#define ToWord(p_byte) (*((uint16_t *)(p_byte)))
#define ToDWord(p_byte) (*((uint32_t *)(p_byte)))
static uint8_t  pixel_img[1024];
static uint32_t pix_to_read;
#define IMG_WIDTH 26

const uint8_t *get_pixel_bitmap_adns7530(uint32_t *size) {
    // set bitmap header
    // 8bit 26*26 pixels
    pixel_img[0]            = 0x42;
    pixel_img[1]            = 0x4D;
    ToDWord(&pixel_img[2])  = IMG_WIDTH * 28 + 54;
    ToWord(&pixel_img[6])   = 0;
    ToWord(&pixel_img[8])   = 0;
    ToDWord(&pixel_img[10]) = 0x36;
    ToDWord(&pixel_img[14]) = 40;
    ToDWord(&pixel_img[18]) = IMG_WIDTH;
    ToDWord(&pixel_img[22]) = IMG_WIDTH;
    ToWord(&pixel_img[26])  = 1;
    ToWord(&pixel_img[28])  = 8;
    ToDWord(&pixel_img[30]) = 0;
    ToDWord(&pixel_img[34]) = IMG_WIDTH * 28;
    ToDWord(&pixel_img[38]) = 96;
    ToDWord(&pixel_img[42]) = 96;
    ToDWord(&pixel_img[46]) = 0;
    ToDWord(&pixel_img[50]) = 0;

    *size = IMG_WIDTH * 28 + 54;  // with * height(4byte aligned) + header

    return pixel_img;
}

void reset_adns7530(uint8_t cs_pin) {
    uint8_t rcv[256];

    {
        uint8_t snd[] = {
            WRITE_TO(0x3A), 0x5a, 0, 0, WRITE_TO(0x2E), 0, 0, 0,
        };
        spim_start(snd, sizeof(snd), rcv, sizeof(snd), cs_pin);
    }

    {
        uint8_t snd[] = {
            READ_FROM(0x2), 0, READ_FROM(0x3), 0,
            READ_FROM(0x4), 0, READ_FROM(0x5), 0,
        };
        spim_start(snd, sizeof(snd), rcv, sizeof(snd), cs_pin);
    }

    {
        uint8_t snd[] = {
            WRITE_TO(0x3C), 0x27, WRITE_TO(0x22), 0x0A, WRITE_TO(0x21), 0x01,
            WRITE_TO(0x3C), 0x32, WRITE_TO(0x23), 0x20, WRITE_TO(0x3C), 0x05,
        };
        spim_start(snd, sizeof(snd), rcv, sizeof(snd), cs_pin);
    }

    {
        // clang-format off
        // set laser power packet
        uint8_t snd[] = {
            WRITE_TO(0x1A), 0x40,
            WRITE_TO(0x1F), (uint8_t)((~0x40) & 0xFF),
            WRITE_TO(0x1C), 0xFF,
            WRITE_TO(0x1D), 0,
        };
        // clang-format on

        // get laser power config from CONFIG.JSN
        uint8_t laser_power = BMPAPI->app.get_config()->reserved[0];
        // set default value
        if (laser_power == 0) {
            laser_power = 0xFF;
        }

        snd[5] = laser_power;
        snd[7] = ~laser_power;

        spim_start(snd, sizeof(snd), rcv, sizeof(snd), cs_pin);
    }
}

uint8_t read_pid_adns7530(uint8_t cs_pin) {
    uint8_t snd[2] = {0};
    uint8_t rcv[2] = {0};

    spim_start(snd, 2, rcv, 2, cs_pin);

    // 0x31
    return rcv[1];
}

void read_adns7530(bool read_flag, uint8_t cs_pin, adns7530_info_t *info) {
    if (read_flag || pix_to_read) {
        // trackball communication packet
        uint8_t snd[] = {0x42, 0, 0, 0, 0, 0};
        uint8_t rcv[] = {0, 0, 0, 0, 0, 0};

        spim_start(snd, sizeof(snd), rcv, sizeof(rcv), cs_pin);

        info->x = ((int16_t)rcv[2] << 4) | (((int16_t)rcv[4] >> 4) << 12);
        info->y = ((int16_t)rcv[3] << 4) | (((int16_t)rcv[4] & 0x0F) << 12);
        info->surface     = rcv[5];
        info->motion_flag = rcv[1];
    } else {
        info->x           = 0;
        info->y           = 0;
        info->surface     = 0;
        info->motion_flag = 0;
    }

    if (pix_to_read && (info->motion_flag & 0x40)) {
        // read pixel data if available
        uint8_t  snd[2] = {READ_FROM(0x35), 0};
        uint8_t  rcv[2];
        uint32_t col = (IMG_WIDTH * IMG_WIDTH - pix_to_read) / IMG_WIDTH;
        uint32_t row = (IMG_WIDTH * IMG_WIDTH - pix_to_read) % IMG_WIDTH;
        spim_start(snd, 2, rcv, 2, cs_pin);

        // write to bitmap file
        pixel_img[54 + 28 * row + col] = rcv[1];
        pix_to_read--;

        if (pix_to_read == 0) {
            xprintf("capture finished\n");
        } else if (pix_to_read % 100 == 0) {
            xprintf(".");
        }
    }
}

int capture_pixel_adns7530(uint8_t cs_pin) {
    xprintf("capture pixel image\n");

    uint8_t rcv[2];
    // reset pointer of pixel_grab to (0,0)
    {
        uint8_t snd[] = {WRITE_TO(0x35), 0x00};
        spim_start(snd, 2, rcv, 2, cs_pin);
    }

    // wait until PIXRDY set
    do {
        uint8_t snd[] = {READ_FROM(0x02), 0x00};
        spim_start(snd, 2, rcv, 2, cs_pin);
    } while (!(rcv[1] & 0x60));

    pix_to_read = IMG_WIDTH * IMG_WIDTH;
    return 0;
}
