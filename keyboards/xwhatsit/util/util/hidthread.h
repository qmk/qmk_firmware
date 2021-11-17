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

#ifndef HIDTHREAD_H
#define HIDTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <vector>
#include <string>
#include "communication.h"
#include "device.h"

class HidThread : public QThread
{
    Q_OBJECT

public:
    HidThread(Communication &comm, QObject *parent = nullptr);
    ~HidThread() override;
    bool setScanning(bool enabled);
    bool setAutoEnter(bool enabled);
    void enterBootloader(std::string path);
    void monitor(std::string path);
    void monitorRowState(std::string path);
    void signalLevel(std::string path);
    void eraseEeprom(std::string path);
    void closeMonitoredDevice();
    void shiftData(std::string path, uint32_t shdata, bool data_idle, bool shcp_idle, bool stcp_idle);
    void enableKeyboard(std::string path);
    void setDacValue(uint16_t value);
    Device *connectToDevice(std::string path);
signals:
    void scannedDevices(std::vector<std::string> devices);
    void reportError(std::string error_message);
    void reportInfo(std::string error_message);
    void keyboardName(std::string name);
    void thresholds(std::vector<std::vector<uint8_t>>);
    void keystate(std::vector<uint8_t>);
    void rowstate(uint8_t);
    void reportMonitorError(std::string error_message);
    void reportSignalLevel(std::vector<uint16_t>);
    void reportRowsAndMaxDac(uint8_t rows, uint16_t max_dac, uint8_t capsense_rows);
    void reportControlReadback(std::vector<uint8_t>);

protected:
    void run() override;

private:
    bool abort;
    bool keep_scanning;
    bool autoenter_mode;
    bool close_monitored_device;
    uint32_t shift_data;
    bool shift_data_idle;
    bool shift_shcp_idle;
    bool shift_stcp_idle;
    std::string shift_data_path;
    std::string enter_bootloader_path;
    std::string monitor_path;
    std::string monitor_row_state_path;
    std::string signal_level_path;
    std::string erase_eeprom_path;
    std::string enable_keyboard_path;
    bool set_dac;
    uint16_t set_dac_value;
    QMutex mutex;
    QWaitCondition condition;
    Communication &comm;
    void nameTranslation(std::string &name);
};

#endif // HIDTHREAD_H
