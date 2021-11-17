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

#ifndef DEVICE_H
#define DEVICE_H

#include <hidapi.h>
#include <string>
#include <vector>
#include <QMutex>

extern const std::string XWHATSIT_ENDING_STRING;
bool is_xwhatsit_original_firmware_path(std::string path);

class Device
{
public:
    Device(std::string path, QMutex &mutex);
    virtual ~Device();
    void close();
    void enterBootloader();
    void disableKeyboard();
    void enableKeyboard();
    uint32_t getVersion();
    bool isVersionAtLeast(uint8_t major, uint8_t mid, uint16_t minor);
    void assertVersionIsAtLeast(uint8_t major, uint8_t mid, uint16_t minor);
    void eraseEeprom();
    void shiftData(uint32_t shdata);
    std::vector<uint8_t> shiftDataExt(uint32_t shdata, bool data_idle, bool shcp_idle, bool stcp_idle);
    std::vector<std::vector<uint8_t>> getThresholds();
    std::vector<uint8_t> getKeyState();
    std::vector<uint8_t> getKeyboardDetails();
    std::vector<uint16_t> getSignalValue(uint8_t col, uint8_t row);
    void setDacValue(uint16_t value);
    uint8_t getRowState();
    std::string getKeyboardFilename();
private:
    hid_device *device = NULL;
    QMutex &mutex;
    bool xwhatsit_original_firmware;
    uint32_t version;
    int keystate_matrix_size;
    int getKeystateMatrixSize();
};

#endif // DEVICE_H
