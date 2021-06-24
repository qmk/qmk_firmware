/* Copyright 2020 Purdea Andrei
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

#include "device.h"
#include <stdexcept>
#include <string.h>
#include <stdio.h>
#include "../../util_comm.h"

const std::string XWHATSIT_ENDING_STRING = " (Running original xwhatsit firmware)";

static const uint8_t magic[] = UTIL_COMM_MAGIC;

bool is_xwhatsit_original_firmware_path(std::string path)
{
    try {
        if (0==path.compare(path.length()-XWHATSIT_ENDING_STRING.length(), XWHATSIT_ENDING_STRING.length(), XWHATSIT_ENDING_STRING))
            return true;
    } catch (std::out_of_range &e)
    {
        // Ignore error
    }
    return false;
}

Device::Device(std::string path, QMutex &mutex) :
    mutex(mutex)
{
    this->keystate_matrix_size = 0;
    QMutexLocker locker(&mutex);
    std::string real_path = path;
    xwhatsit_original_firmware = is_xwhatsit_original_firmware_path(path);
    if (xwhatsit_original_firmware)
    {
        real_path = path.substr(0, path.length() - XWHATSIT_ENDING_STRING.length());
    }

    device = hid_open_path(real_path.c_str());
    if (!device)
    {
        throw std::runtime_error("Error opening device");
    }
    if (!xwhatsit_original_firmware)
    {
        uint8_t data[33];
        // Extract any pending data, for more reliable operation.
        while ((sizeof(data)-1)==hid_read_timeout(device, data, sizeof(data)-1, 100))
            ;
        data[0] = 0;
        memcpy(data + 1, magic, sizeof(magic));
        data[2+1] = UTIL_COMM_GET_VERSION;
        if (-1==hid_write(device, data, sizeof(data)))
        {
            hid_close(device);
            throw std::runtime_error("hid_write failed to get version");
        }
        if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
        {
            hid_close(device);
            throw std::runtime_error("hid_read failed to get version");
        }
        if ((data[0] != magic[0]) || (data[1] != magic[1]))
        {
            hid_close(device);
            throw std::runtime_error("hid_read did not receive back magic");
        }
        if (data[2] != UTIL_COMM_RESPONSE_OK)
        {
            hid_close(device);
            throw std::runtime_error("hid_read did not return OK response");
        }
        version = static_cast<uint32_t>(data[3]);
        if (version < 1)
        {
            hid_close(device);
            throw std::runtime_error("Protocol version is wrong");
        }
        if (version >= 2)
        {
            version = (static_cast<uint32_t>(data[3]) << 24) |
                      (static_cast<uint32_t>(data[4]) << 16) |
                      (static_cast<uint32_t>(data[5]) << 8 ) |
                      (static_cast<uint32_t>(data[6]) << 0 );
                                                        ;
        } else {
            version = static_cast<uint32_t>(data[3]) << 24;
        }
    } else {
        version = 0;
    }
}

Device::~Device()
{
    close();
}

void Device::close()
{
    QMutexLocker locker(&mutex);
    if (device)
    {
        hid_close(device);
        device = NULL;
    }
}

void Device::enterBootloader()
{
    {
        QMutexLocker locker(&mutex);
        if (!device) std::runtime_error("device already closed");
        if (xwhatsit_original_firmware)
        {
            uint8_t data[9] = {0, 2, 1, 0, 0, 0, 0, 0, 0};
            hid_write(device, data, sizeof(data));
        } else
        {
            uint8_t data[33];
            data[0] = 0;
            memcpy(data + 1, magic, sizeof(magic));
            data[2+1] = UTIL_COMM_ENTER_BOOTLOADER;
            if (-1==hid_write(device, data, sizeof(data)))
            {
                printf("hid error: %ls\n", hid_error(device));
                hid_close(device);
                device = NULL;
                throw std::runtime_error("hid_write failed to enter bootloader");
            }
        }
    }
    close();
}

void Device::enableKeyboard()
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_ENABLE_KEYBOARD;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to enable keyboard");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while enabling keyboard");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while enabling keyboard -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while enabling keyboard -- response not okay");
    }
}

void Device::eraseEeprom()
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_ERASE_EEPROM;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to erase eeprom");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while erasing eeprom");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while erasing eeprom -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while erasing eeprom -- response not okay");
    }
}

void Device::shiftData(uint32_t shdata)
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_SHIFT_DATA;
    data[3+1] = shdata & 0xff;
    data[4+1] = (shdata >> 8) & 0xff;
    data[5+1] = (shdata >> 16) & 0xff;
    data[6+1] = (shdata >> 24) & 0xff;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to shift data");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while shifting data");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while shifting data -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while shifting data -- response not okay");
    }
}

std::vector<uint8_t> Device::shiftDataExt(uint32_t shdata, bool data_idle, bool shcp_idle, bool stcp_idle)
{
    uint8_t data[33];
    {
        QMutexLocker locker(&mutex);
        if (xwhatsit_original_firmware)
        {
            throw std::runtime_error("This doesn't work with xwhatsit original firmware");
        }

        data[0] = 0;
        memcpy(data + 1, magic, sizeof(magic));
        data[2+1] = UTIL_COMM_SHIFT_DATA_EXT;
        data[3+1] = shdata & 0xff;
        data[4+1] = (shdata >> 8) & 0xff;
        data[5+1] = (shdata >> 16) & 0xff;
        data[6+1] = (shdata >> 24) & 0xff;
        data[7+1] = (uint8_t)data_idle;
        data[8+1] = (uint8_t)shcp_idle;
        data[9+1] = (uint8_t)stcp_idle;
        if (-1==hid_write(device, data, sizeof(data)))
        {
            printf("hid error: %ls\n", hid_error(device));
            throw std::runtime_error("hid_write failed to shift data");
        }
        if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
        {
            printf("hid error: %ls\n", hid_error(device));
            throw std::runtime_error("hid_read failed while shifting data");
        }
        if ((data[0] != magic[0]) || (data[1] != magic[1]))
        {
            throw std::runtime_error("hid_read failed while shifting data -- no magic returned");
        }
    }
    std::vector<uint8_t> ret;
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        shiftData(shdata);
        return ret;
    }
    ret.push_back(data[3]);
    ret.push_back(data[4]);
    ret.push_back(data[5]);
    return ret;
}

void Device::disableKeyboard()
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_DISABLE_KEYBOARD;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to disable keyboard");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while disabling keyboard");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while disabling keyboard -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while disabling keyboard -- response not okay");
    }
}

std::vector<std::vector<uint8_t>> Device::getThresholds()
{
    int matrixsize = getKeystateMatrixSize();
    QMutexLocker locker(&mutex);
    std::vector<std::vector<uint8_t>> ret;
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t bins;
    uint8_t current_bin = 0;
    do {
        uint8_t data[33];
        data[0] = 0;
        memcpy(data + 1, magic, sizeof(magic));
        data[2+1] = UTIL_COMM_GET_THRESHOLDS;
        data[3+1] = current_bin;
        data[4+1] = 0;
        if (-1==hid_write(device, data, sizeof(data)))
        {
            printf("hid error: %ls\n", hid_error(device));
            throw std::runtime_error("hid_write failed to disable keyboard");
        }
        if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
        {
            printf("hid error: %ls\n", hid_error(device));
            throw std::runtime_error("hid_read failed while getting thresholds");
        }
        if ((data[0] != magic[0]) || (data[1] != magic[1]))
        {
            throw std::runtime_error("hid_read failed while getting thresholds -- no magic returned");
        }
        if (data[2] != UTIL_COMM_RESPONSE_OK)
        {
            throw std::runtime_error("hid_read failed while getting thresholds -- response not okay");
        }
        std::vector<uint8_t> trdata(&data[3], &data[qMin(32, matrixsize + 3 + 3)]);
        if (matrixsize > 32 - 6)
        {
            data[0] = 0;
            memcpy(data + 1, magic, sizeof(magic));
            data[2+1] = UTIL_COMM_GET_THRESHOLDS;
            data[3+1] = current_bin;
            data[4+1] = 32-6;
            if (-1==hid_write(device, data, sizeof(data)))
            {
                printf("hid error: %ls\n", hid_error(device));
                throw std::runtime_error("hid_write failed to disable keyboard");
            }
            if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
            {
                printf("hid error: %ls\n", hid_error(device));
                throw std::runtime_error("hid_read failed while getting thresholds");
            }
            if ((data[0] != magic[0]) || (data[1] != magic[1]))
            {
                throw std::runtime_error("hid_read failed while getting thresholds -- no magic returned");
            }
            if (data[2] != UTIL_COMM_RESPONSE_OK)
            {
                throw std::runtime_error("hid_read failed while getting thresholds -- response not okay");
            }
            trdata.insert(trdata.end(), &data[6], &data[qMin(32, matrixsize - (32 - 6) + 6)]);
        }
        ret.push_back(trdata);
        bins = data[3];
        current_bin ++;
    } while (current_bin < bins);
    return ret;
}

std::vector<uint8_t> Device::getKeyState()
{
    int matrixsize = getKeystateMatrixSize();
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_GET_KEYSTATE;
    data[3+1] = 0;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to get keystate");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while getting keystate");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while getting keystate -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while getting keystate -- response not okay");
    }
    std::vector<uint8_t> ret(&data[3], &data[qMin(32, matrixsize + 3)]);
    if (matrixsize > 32 - 3)
    {
        data[0] = 0;
        memcpy(data + 1, magic, sizeof(magic));
        data[2+1] = UTIL_COMM_GET_KEYSTATE;
        data[3+1] = 32-3;
        if (-1==hid_write(device, data, sizeof(data)))
        {
            printf("hid error: %ls\n", hid_error(device));
            throw std::runtime_error("hid_write failed to get keystate");
        }
        if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
        {
            printf("hid error: %ls\n", hid_error(device));
            throw std::runtime_error("hid_read failed while getting keystate");
        }
        if ((data[0] != magic[0]) || (data[1] != magic[1]))
        {
            throw std::runtime_error("hid_read failed while getting keystate -- no magic returned");
        }
        if (data[2] != UTIL_COMM_RESPONSE_OK)
        {
            throw std::runtime_error("hid_read failed while getting keystate -- response not okay");
        }
        ret.insert(ret.end(), &data[3], &data[qMin(32, matrixsize - (32 - 3) + 3)]);
    }
    return ret;
}


std::vector<uint8_t> Device::getKeyboardDetails()
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_GET_KEYBOARD_DETAILS;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to get keyboard details");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while getting keyboard details");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while getting keyboard details -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while getting keyboard details -- response not okay");
    }
    std::vector<uint8_t> ret(&data[3], &data[32]);
    return ret;
}

int Device::getKeystateMatrixSize()
{
    if (!isVersionAtLeast(2, 0, 2)) return 16;
    if (this->keystate_matrix_size) return this->keystate_matrix_size;
    std::vector<uint8_t> details = getKeyboardDetails();
    uint8_t cols = details[0];
    uint8_t rows = details[1];
    uint8_t bytes_per_row = (cols > 16) ? 4 : ((cols > 8) ? 2 : 1);
    this->keystate_matrix_size = bytes_per_row * rows;
    return this->keystate_matrix_size;
}

std::vector<uint16_t> Device::getSignalValue(uint8_t col, uint8_t row)
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_GET_SIGNAL_VALUE;
    data[3+1] = col;
    data[4+1] = row;
    uint8_t count = 14;
    data[5+1] = count;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to get signal value");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while getting signal value");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while getting signal value -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while getting signal value -- response not okay");
    }
    uint8_t i;
    std::vector<uint16_t> ret;
    for (i=0;i<count;i++)
    {
        uint16_t value = data[3+i*2] | static_cast<uint16_t>(data[3+i*2+1] << 8);
        ret.push_back(value);
    }
    return ret;
}

void Device::setDacValue(uint16_t value)
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_SET_DAC_VALUE;
    data[3+1] = value & 0xFF;
    data[4+1] = (value >> 8) & 0xFF;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to set DAC value");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while setting DAC value");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while setting DAC value -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while setting DAC value -- response not okay");
    }
}

uint8_t Device::getRowState()
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    uint8_t data[33];
    data[0] = 0;
    memcpy(data + 1, magic, sizeof(magic));
    data[2+1] = UTIL_COMM_GET_ROW_STATE;
    if (-1==hid_write(device, data, sizeof(data)))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_write failed to get row state");
    }
    if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
    {
        printf("hid error: %ls\n", hid_error(device));
        throw std::runtime_error("hid_read failed while getting row state");
    }
    if ((data[0] != magic[0]) || (data[1] != magic[1]))
    {
        throw std::runtime_error("hid_read failed while getting row state -- no magic returned");
    }
    if (data[2] != UTIL_COMM_RESPONSE_OK)
    {
        throw std::runtime_error("hid_read failed while getting row state -- response not okay");
    }
    return data[3];
}

uint32_t Device::getVersion()
{
    return version;
}

bool Device::isVersionAtLeast(uint8_t major, uint8_t mid, uint16_t minor)
{
    if ((version >> 24) > major) return true;
    if ((version >> 24) < major) return false;
    if (((version >> 16) & 0xff) > mid) return true;
    if (((version >> 16) & 0xff) < mid) return false;
    if ((version & 0xffff) >= minor) return true;
    return false;
}

void Device::assertVersionIsAtLeast(uint8_t major, uint8_t mid, uint16_t minor)
{
    if (!isVersionAtLeast(major, mid, minor))
        throw std::runtime_error("Version of communication protocl is too old. Please update your firmware.");
}

std::string Device::getKeyboardFilename()
{
    QMutexLocker locker(&mutex);
    if (xwhatsit_original_firmware)
    {
        throw std::runtime_error("This doesn't work with xwhatsit original firmware");
    }
    int start = 0;
    std::string s;
    std::string piece;
    do
    {
        uint8_t data[33];
        data[0] = 0;
        memcpy(data + 1, magic, sizeof(magic));
        data[2+1] = UTIL_COMM_GET_KEYBOARD_FILENAME;
        data[4] = static_cast<uint8_t>(start);
        if (-1==hid_write(device, data, sizeof(data)))
        {
            printf("hid error: %ls\n", hid_error(device));
            throw std::runtime_error("hid_write failed to get keyboard firmware");
        }
        if ((sizeof(data)-1)!=hid_read_timeout(device, data, sizeof(data)-1, 1000))
        {
            printf("hid error: %ls\n", hid_error(device));
            throw std::runtime_error("hid_read failed to get keyboard firmware");
        }
        if ((data[0] != magic[0]) || (data[1] != magic[1]))
        {
            throw std::runtime_error("hid_read failed to get keyboard firmware -- no magic returned");
        }
        if (data[2] != UTIL_COMM_RESPONSE_OK)
        {
            throw std::runtime_error("hid_read failed to get keyboard firmware -- response not okay");
        }
        data[32] = 0;
        piece = std::string(reinterpret_cast<const char *>(data + 3));
        s += piece;
        start += piece.size();
    } while ((piece.length() >= 32 - 3) && (start < 256));
    return s;
}
