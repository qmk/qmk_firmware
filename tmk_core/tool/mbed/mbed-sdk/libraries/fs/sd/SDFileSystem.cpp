/* mbed Microcontroller Library
 * Copyright (c) 2006-2012 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* Introduction
 * ------------
 * SD and MMC cards support a number of interfaces, but common to them all
 * is one based on SPI. This is the one I'm implmenting because it means
 * it is much more portable even though not so performant, and we already
 * have the mbed SPI Interface!
 *
 * The main reference I'm using is Chapter 7, "SPI Mode" of:
 *  http://www.sdcard.org/developers/tech/sdcard/pls/Simplified_Physical_Layer_Spec.pdf
 *
 * SPI Startup
 * -----------
 * The SD card powers up in SD mode. The SPI interface mode is selected by
 * asserting CS low and sending the reset command (CMD0). The card will
 * respond with a (R1) response.
 *
 * CMD8 is optionally sent to determine the voltage range supported, and
 * indirectly determine whether it is a version 1.x SD/non-SD card or
 * version 2.x. I'll just ignore this for now.
 *
 * ACMD41 is repeatedly issued to initialise the card, until "in idle"
 * (bit 0) of the R1 response goes to '0', indicating it is initialised.
 *
 * You should also indicate whether the host supports High Capicity cards,
 * and check whether the card is high capacity - i'll also ignore this
 *
 * SPI Protocol
 * ------------
 * The SD SPI protocol is based on transactions made up of 8-bit words, with
 * the host starting every bus transaction by asserting the CS signal low. The
 * card always responds to commands, data blocks and errors.
 *
 * The protocol supports a CRC, but by default it is off (except for the
 * first reset CMD0, where the CRC can just be pre-calculated, and CMD8)
 * I'll leave the CRC off I think!
 *
 * Standard capacity cards have variable data block sizes, whereas High
 * Capacity cards fix the size of data block to 512 bytes. I'll therefore
 * just always use the Standard Capacity cards with a block size of 512 bytes.
 * This is set with CMD16.
 *
 * You can read and write single blocks (CMD17, CMD25) or multiple blocks
 * (CMD18, CMD25). For simplicity, I'll just use single block accesses. When
 * the card gets a read command, it responds with a response token, and then
 * a data token or an error.
 *
 * SPI Command Format
 * ------------------
 * Commands are 6-bytes long, containing the command, 32-bit argument, and CRC.
 *
 * +---------------+------------+------------+-----------+----------+--------------+
 * | 01 | cmd[5:0] | arg[31:24] | arg[23:16] | arg[15:8] | arg[7:0] | crc[6:0] | 1 |
 * +---------------+------------+------------+-----------+----------+--------------+
 *
 * As I'm not using CRC, I can fix that byte to what is needed for CMD0 (0x95)
 *
 * All Application Specific commands shall be preceded with APP_CMD (CMD55).
 *
 * SPI Response Format
 * -------------------
 * The main response format (R1) is a status byte (normally zero). Key flags:
 *  idle - 1 if the card is in an idle state/initialising
 *  cmd  - 1 if an illegal command code was detected
 *
 *    +-------------------------------------------------+
 * R1 | 0 | arg | addr | seq | crc | cmd | erase | idle |
 *    +-------------------------------------------------+
 *
 * R1b is the same, except it is followed by a busy signal (zeros) until
 * the first non-zero byte when it is ready again.
 *
 * Data Response Token
 * -------------------
 * Every data block written to the card is acknowledged by a byte
 * response token
 *
 * +----------------------+
 * | xxx | 0 | status | 1 |
 * +----------------------+
 *              010 - OK!
 *              101 - CRC Error
 *              110 - Write Error
 *
 * Single Block Read and Write
 * ---------------------------
 *
 * Block transfers have a byte header, followed by the data, followed
 * by a 16-bit CRC. In our case, the data will always be 512 bytes.
 *
 * +------+---------+---------+- -  - -+---------+-----------+----------+
 * | 0xFE | data[0] | data[1] |        | data[n] | crc[15:8] | crc[7:0] |
 * +------+---------+---------+- -  - -+---------+-----------+----------+
 */
#include "SDFileSystem.h"
#include "mbed_debug.h"

#define SD_COMMAND_TIMEOUT 5000

#define SD_DBG             0

SDFileSystem::SDFileSystem(PinName mosi, PinName miso, PinName sclk, PinName cs, const char* name) :
    FATFileSystem(name), _spi(mosi, miso, sclk), _cs(cs), _is_initialized(0) {
    _cs = 1;

    // Set default to 100kHz for initialisation and 1MHz for data transfer
    _init_sck = 100000;
    _transfer_sck = 1000000;
}

#define R1_IDLE_STATE           (1 << 0)
#define R1_ERASE_RESET          (1 << 1)
#define R1_ILLEGAL_COMMAND      (1 << 2)
#define R1_COM_CRC_ERROR        (1 << 3)
#define R1_ERASE_SEQUENCE_ERROR (1 << 4)
#define R1_ADDRESS_ERROR        (1 << 5)
#define R1_PARAMETER_ERROR      (1 << 6)

// Types
//  - v1.x Standard Capacity
//  - v2.x Standard Capacity
//  - v2.x High Capacity
//  - Not recognised as an SD Card
#define SDCARD_FAIL 0
#define SDCARD_V1   1
#define SDCARD_V2   2
#define SDCARD_V2HC 3

int SDFileSystem::initialise_card() {
    // Set to SCK for initialisation, and clock card with cs = 1
    _spi.frequency(_init_sck);
    _cs = 1;
    for (int i = 0; i < 16; i++) {
        _spi.write(0xFF);
    }

    // send CMD0, should return with all zeros except IDLE STATE set (bit 0)
    if (_cmd(0, 0) != R1_IDLE_STATE) {
        debug("No disk, or could not put SD card in to SPI idle state\n");
        return SDCARD_FAIL;
    }

    // send CMD8 to determine whther it is ver 2.x
    int r = _cmd8();
    if (r == R1_IDLE_STATE) {
        return initialise_card_v2();
    } else if (r == (R1_IDLE_STATE | R1_ILLEGAL_COMMAND)) {
        return initialise_card_v1();
    } else {
        debug("Not in idle state after sending CMD8 (not an SD card?)\n");
        return SDCARD_FAIL;
    }
}

int SDFileSystem::initialise_card_v1() {
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        _cmd(55, 0);
        if (_cmd(41, 0) == 0) {
            cdv = 512;
            debug_if(SD_DBG, "\n\rInit: SEDCARD_V1\n\r");
            return SDCARD_V1;
        }
    }

    debug("Timeout waiting for v1.x card\n");
    return SDCARD_FAIL;
}

int SDFileSystem::initialise_card_v2() {
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        wait_ms(50);
        _cmd58();
        _cmd(55, 0);
        if (_cmd(41, 0x40000000) == 0) {
            _cmd58();
            debug_if(SD_DBG, "\n\rInit: SDCARD_V2\n\r");
            cdv = 1;
            return SDCARD_V2;
        }
    }

    debug("Timeout waiting for v2.x card\n");
    return SDCARD_FAIL;
}

int SDFileSystem::disk_initialize() {
    _is_initialized = initialise_card();
    if (_is_initialized == 0) {
        debug("Fail to initialize card\n");
        return 1;
    }
    debug_if(SD_DBG, "init card = %d\n", _is_initialized);
    _sectors = _sd_sectors();

    // Set block length to 512 (CMD16)
    if (_cmd(16, 512) != 0) {
        debug("Set 512-byte block timed out\n");
        return 1;
    }

    // Set SCK for data transfer
    _spi.frequency(_transfer_sck);
    return 0;
}

int SDFileSystem::disk_write(const uint8_t* buffer, uint64_t block_number, uint8_t count) {
    if (!_is_initialized) {
        return -1;
    }
    
    for (uint64_t b = block_number; b < block_number + count; b++) {
        // set write address for single block (CMD24)
        if (_cmd(24, b * cdv) != 0) {
            return 1;
        }
        
        // send the data block
        _write(buffer, 512);
        buffer += 512;
    }
    
    return 0;
}

int SDFileSystem::disk_read(uint8_t* buffer, uint64_t block_number, uint8_t count) {
    if (!_is_initialized) {
        return -1;
    }
    
    for (uint64_t b = block_number; b < block_number + count; b++) {
        // set read address for single block (CMD17)
        if (_cmd(17, b * cdv) != 0) {
            return 1;
        }
        
        // receive the data
        _read(buffer, 512);
        buffer += 512;
    }

    return 0;
}

int SDFileSystem::disk_status() {
    // FATFileSystem::disk_status() returns 0 when initialized
    if (_is_initialized) {
        return 0;
    } else {
        return 1;
    }
}

int SDFileSystem::disk_sync() { return 0; }
uint64_t SDFileSystem::disk_sectors() { return _sectors; }


// PRIVATE FUNCTIONS
int SDFileSystem::_cmd(int cmd, int arg) {
    _cs = 0;

    // send a command
    _spi.write(0x40 | cmd);
    _spi.write(arg >> 24);
    _spi.write(arg >> 16);
    _spi.write(arg >> 8);
    _spi.write(arg >> 0);
    _spi.write(0x95);

    // wait for the repsonse (response[7] == 0)
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        int response = _spi.write(0xFF);
        if (!(response & 0x80)) {
            _cs = 1;
            _spi.write(0xFF);
            return response;
        }
    }
    _cs = 1;
    _spi.write(0xFF);
    return -1; // timeout
}
int SDFileSystem::_cmdx(int cmd, int arg) {
    _cs = 0;

    // send a command
    _spi.write(0x40 | cmd);
    _spi.write(arg >> 24);
    _spi.write(arg >> 16);
    _spi.write(arg >> 8);
    _spi.write(arg >> 0);
    _spi.write(0x95);

    // wait for the repsonse (response[7] == 0)
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        int response = _spi.write(0xFF);
        if (!(response & 0x80)) {
            return response;
        }
    }
    _cs = 1;
    _spi.write(0xFF);
    return -1; // timeout
}


int SDFileSystem::_cmd58() {
    _cs = 0;
    int arg = 0;

    // send a command
    _spi.write(0x40 | 58);
    _spi.write(arg >> 24);
    _spi.write(arg >> 16);
    _spi.write(arg >> 8);
    _spi.write(arg >> 0);
    _spi.write(0x95);

    // wait for the repsonse (response[7] == 0)
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        int response = _spi.write(0xFF);
        if (!(response & 0x80)) {
            int ocr = _spi.write(0xFF) << 24;
            ocr |= _spi.write(0xFF) << 16;
            ocr |= _spi.write(0xFF) << 8;
            ocr |= _spi.write(0xFF) << 0;
            _cs = 1;
            _spi.write(0xFF);
            return response;
        }
    }
    _cs = 1;
    _spi.write(0xFF);
    return -1; // timeout
}

int SDFileSystem::_cmd8() {
    _cs = 0;

    // send a command
    _spi.write(0x40 | 8); // CMD8
    _spi.write(0x00);     // reserved
    _spi.write(0x00);     // reserved
    _spi.write(0x01);     // 3.3v
    _spi.write(0xAA);     // check pattern
    _spi.write(0x87);     // crc

    // wait for the repsonse (response[7] == 0)
    for (int i = 0; i < SD_COMMAND_TIMEOUT * 1000; i++) {
        char response[5];
        response[0] = _spi.write(0xFF);
        if (!(response[0] & 0x80)) {
            for (int j = 1; j < 5; j++) {
                response[i] = _spi.write(0xFF);
            }
            _cs = 1;
            _spi.write(0xFF);
            return response[0];
        }
    }
    _cs = 1;
    _spi.write(0xFF);
    return -1; // timeout
}

int SDFileSystem::_read(uint8_t *buffer, uint32_t length) {
    _cs = 0;

    // read until start byte (0xFF)
    while (_spi.write(0xFF) != 0xFE);

    // read data
    for (uint32_t i = 0; i < length; i++) {
        buffer[i] = _spi.write(0xFF);
    }
    _spi.write(0xFF); // checksum
    _spi.write(0xFF);

    _cs = 1;
    _spi.write(0xFF);
    return 0;
}

int SDFileSystem::_write(const uint8_t*buffer, uint32_t length) {
    _cs = 0;

    // indicate start of block
    _spi.write(0xFE);

    // write the data
    for (uint32_t i = 0; i < length; i++) {
        _spi.write(buffer[i]);
    }

    // write the checksum
    _spi.write(0xFF);
    _spi.write(0xFF);

    // check the response token
    if ((_spi.write(0xFF) & 0x1F) != 0x05) {
        _cs = 1;
        _spi.write(0xFF);
        return 1;
    }

    // wait for write to finish
    while (_spi.write(0xFF) == 0);

    _cs = 1;
    _spi.write(0xFF);
    return 0;
}

static uint32_t ext_bits(unsigned char *data, int msb, int lsb) {
    uint32_t bits = 0;
    uint32_t size = 1 + msb - lsb;
    for (uint32_t i = 0; i < size; i++) {
        uint32_t position = lsb + i;
        uint32_t byte = 15 - (position >> 3);
        uint32_t bit = position & 0x7;
        uint32_t value = (data[byte] >> bit) & 1;
        bits |= value << i;
    }
    return bits;
}

uint64_t SDFileSystem::_sd_sectors() {
    uint32_t c_size, c_size_mult, read_bl_len;
    uint32_t block_len, mult, blocknr, capacity;
    uint32_t hc_c_size;
    uint64_t blocks;

    // CMD9, Response R2 (R1 byte + 16-byte block read)
    if (_cmdx(9, 0) != 0) {
        debug("Didn't get a response from the disk\n");
        return 0;
    }

    uint8_t csd[16];
    if (_read(csd, 16) != 0) {
        debug("Couldn't read csd response from disk\n");
        return 0;
    }

    // csd_structure : csd[127:126]
    // c_size        : csd[73:62]
    // c_size_mult   : csd[49:47]
    // read_bl_len   : csd[83:80] - the *maximum* read block length

    int csd_structure = ext_bits(csd, 127, 126);

    switch (csd_structure) {
        case 0:
            cdv = 512;
            c_size = ext_bits(csd, 73, 62);
            c_size_mult = ext_bits(csd, 49, 47);
            read_bl_len = ext_bits(csd, 83, 80);

            block_len = 1 << read_bl_len;
            mult = 1 << (c_size_mult + 2);
            blocknr = (c_size + 1) * mult;
            capacity = blocknr * block_len;
            blocks = capacity / 512;
            debug_if(SD_DBG, "\n\rSDCard\n\rc_size: %d \n\rcapacity: %ld \n\rsectors: %lld\n\r", c_size, capacity, blocks);
            break;

        case 1:
            cdv = 1;
            hc_c_size = ext_bits(csd, 63, 48);
            blocks = (hc_c_size+1)*1024;
            debug_if(SD_DBG, "\n\rSDHC Card \n\rhc_c_size: %d\n\rcapacity: %lld \n\rsectors: %lld\n\r", hc_c_size, blocks*512, blocks);
            break;

        default:
            debug("CSD struct unsupported\r\n");
            return 0;
    };
    return blocks;
}
