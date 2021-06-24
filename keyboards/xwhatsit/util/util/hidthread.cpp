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

#include "hidthread.h"
#include <stdio.h>
#include <iostream>

HidThread::HidThread(Communication &comm, QObject *parent) : QThread(parent), comm(comm)
{
    keep_scanning = false;
    abort = false;
    enter_bootloader_path = "";
    autoenter_mode = false;
    close_monitored_device = false;
    shift_data_path = "";
    monitor_path = "";
    monitor_row_state_path = "";
    signal_level_path = "";
    erase_eeprom_path = "";
    enable_keyboard_path = "";
    set_dac = false;
}

HidThread::~HidThread()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

bool HidThread::setScanning(bool enabled)
{
    QMutexLocker locker(&mutex);
    bool previous = this->keep_scanning;
    this->keep_scanning = enabled;
    condition.wakeOne();
    return previous;
}

bool HidThread::setAutoEnter(bool enabled)
{
    QMutexLocker locker(&mutex);
    bool previous = autoenter_mode;
    autoenter_mode = enabled;
    return previous;
}

void HidThread::enterBootloader(std::string path)
{
     QMutexLocker locker(&mutex);
     this->enter_bootloader_path = path;
     condition.wakeOne();
}

void HidThread::monitor(std::string path)
{
    QMutexLocker locker(&mutex);
    this->monitor_path = path;
    condition.wakeOne();
}

void HidThread::monitorRowState(std::string path)
{
    QMutexLocker locker(&mutex);
    this->monitor_row_state_path = path;
    condition.wakeOne();
}

void HidThread::signalLevel(std::string path)
{
    QMutexLocker locker(&mutex);
    this->signal_level_path = path;
    condition.wakeOne();
}

void HidThread::eraseEeprom(std::string path)
{
    QMutexLocker locker(&mutex);
    this->erase_eeprom_path = path;
    condition.wakeOne();
}

void HidThread::closeMonitoredDevice()
{
    QMutexLocker locker(&mutex);
    this->close_monitored_device = true;
    condition.wakeOne();
}

void HidThread::shiftData(std::string path, uint32_t shdata, bool data_idle, bool shcp_idle, bool stcp_idle)
{
    QMutexLocker locker(&mutex);
    this->shift_data = shdata;
    this->shift_data_idle = data_idle;
    this->shift_shcp_idle = shcp_idle;
    this->shift_stcp_idle = stcp_idle;
    this->shift_data_path = path;
    condition.wakeOne();
}

void HidThread::enableKeyboard(std::string path)
{
    QMutexLocker locker(&mutex);
    this->enable_keyboard_path = path;
    condition.wakeOne();
}

void HidThread::setDacValue(uint16_t value)
{
    QMutexLocker locker(&mutex);
    this->set_dac = true;
    this->set_dac_value = value;
    condition.wakeOne();
}

void HidThread::nameTranslation(std::string &name)
{
    if (name.compare("keyboards/xwhatsit/brand_new_model_f_keyboards/f62/f62.c") == 0)
        name = "keyboards/xwhatsit/brand_new_model_f/f62/wcass/wcass.c";
    if (name.compare("keyboards/xwhatsit/brand_new_model_f_keyboards/f77/f77.c") == 0)
        name = "keyboards/xwhatsit/brand_new_model_f/f77/wcass/wcass.c";
    if (name.compare("keyboards/xwhatsit/ibm/f62/xwhatsit_modelf/xwhatsit_modelf.c") == 0)
        name = "keyboards/xwhatsit/ibm/f62/xwhatsit/xwhatsit.c";
    if (name.compare("keyboards/xwhatsit/ibm/f50/xwhatsit_modelf/xwhatsit_modelf.c") == 0)
        name = "keyboards/xwhatsit/ibm/f50/xwhatsit/xwhatsit.c";
    if (name.compare("keyboards/xwhatsit/ibm/f107/xwhatsit_modelf/xwhatsit_modelf.c") == 0)
        name = "keyboards/xwhatsit/ibm/f107/xwhatsit/xwhatsit.c";
    if (name.compare("keyboards/xwhatsit/ibm/5251/xwhatsit_beamspring_rev_4/xwhatsit_beamspring_rev_4.c") == 0)
        name = "keyboards/xwhatsit/ibm/5251/xwhatsit_rev4/xwhatsit_rev4.c";
    if (name.compare("keyboards/xwhatsit/ibm/3276_3278/xwhatsit_beamspring_rev_4/xwhatsit_beamspring_rev_4.c") == 0)
        name = "keyboards/xwhatsit/ibm/3276_3278_75key/xwhatsit_rev4/xwhatsit_rev4.c";
    if (name.compare("keyboards/xwhatsit/ibm/3276_3278/through_hole/through_hole.c") == 0)
        name = "keyboards/xwhatsit/ibm/3276_3278_75key/through_hole/through_hole.c";
    // this is because through_hole has been renamed to universal:
    std::string fromending = "/through_hole/through_hole.c";
    std::string toending = "/universal/universal.c";
    if (name.size() >= fromending.size())
        if (name.compare(name.size() - fromending.size(), fromending.size(), fromending) == 0)
            name = name.substr(0, name.size() - fromending.size()) + toending;
}

void HidThread::run()
{
    Device *monitoredDevice = nullptr;
    Device *monitoredRowStateDevice = nullptr;
    Device *signalLevelDevice = nullptr;
    uint8_t cols=0, rows=0, capsense_rows = 0, current_col=0, current_row=0;
    forever {
        mutex.lock();
        bool l_keep_scanning, l_abort, nothing_to_do, l_autoenter_mode, l_close_monitored_device, l_set_dac;
        uint32_t l_shift_data;
        bool l_shift_data_idle, l_shift_shcp_idle, l_shift_stcp_idle;
        std::string l_enter_bootloader_path, l_monitor_path, l_erase_eeprom_path, l_signal_level_path, l_shift_data_path, l_enable_keyboard_path, l_monitor_row_state_path;
        uint16_t l_set_dac_value;
        do {
            l_keep_scanning = this->keep_scanning;
            l_enter_bootloader_path = this->enter_bootloader_path;
            l_monitor_path = this->monitor_path;
            l_signal_level_path = this->signal_level_path;
            l_autoenter_mode = this->autoenter_mode;
            l_close_monitored_device = this->close_monitored_device;
            l_abort = this->abort;
            l_erase_eeprom_path = this->erase_eeprom_path;
            l_shift_data_path = shift_data_path;
            l_shift_data = shift_data;
            l_shift_data_idle = shift_data_idle;
            l_shift_shcp_idle = shift_shcp_idle;
            l_shift_stcp_idle = shift_stcp_idle;
            l_enable_keyboard_path = enable_keyboard_path;
            l_set_dac = set_dac;
            l_set_dac_value = set_dac_value;
            l_monitor_row_state_path = monitor_row_state_path;
            nothing_to_do = (!l_keep_scanning) &&
                            (!l_abort) &&
                            (l_enter_bootloader_path.size()==0) &&
                            (l_monitor_path.size()==0) &&
                            (!l_autoenter_mode) &&
                            (monitoredDevice == nullptr) &&
                            (!l_close_monitored_device) &&
                            (l_erase_eeprom_path.size() == 0) &&
                            (l_signal_level_path.size() == 0) &&
                            (signalLevelDevice == nullptr) &&
                            (l_shift_data_path.size() == 0) &&
                            (l_enable_keyboard_path.size() == 0) &&
                            (!l_set_dac) &&
                            (l_monitor_row_state_path.size() == 0) &&
                            (monitoredRowStateDevice == nullptr);
            if (nothing_to_do) {
                condition.wait(&mutex);
            }
        } while (nothing_to_do);
        mutex.unlock();
        if (l_abort)
            return;
        if (l_enter_bootloader_path.size() != 0)
        {
            try {
                QScopedPointer<Device> dev(comm.open(l_enter_bootloader_path));
                dev.data()->enterBootloader();
            } catch (const std::runtime_error &e1) {
                emit reportError(e1.what());
            }
            mutex.lock();
            this->enter_bootloader_path = "";
            mutex.unlock();
        }
        if (l_shift_data_path.size() != 0)
        {
            try {
                QScopedPointer<Device> dev(comm.open(l_shift_data_path));
                dev.data()->disableKeyboard();
                dev.data()->assertVersionIsAtLeast(2, 0, 3);
                emit reportControlReadback(dev.data()->shiftDataExt(l_shift_data, l_shift_data_idle, l_shift_shcp_idle, l_shift_stcp_idle));
            } catch (const std::runtime_error &e1) {
                emit reportError(e1.what());
            }
            mutex.lock();
            this->shift_data_path = "";
            mutex.unlock();
        }
        if (l_enable_keyboard_path.size() != 0)
        {
            try {
                QScopedPointer<Device> dev(comm.open(l_enable_keyboard_path));
                dev.data()->enableKeyboard();
            } catch (const std::runtime_error &e1) {
                emit reportError(e1.what());
            }
            mutex.lock();
            this->enable_keyboard_path = "";
            mutex.unlock();
        }
        if (l_erase_eeprom_path.size() != 0)
        {
            try {
                QScopedPointer<Device> dev(comm.open(l_erase_eeprom_path));
                dev.data()->assertVersionIsAtLeast(2, 0, 1);
                dev.data()->eraseEeprom();
                emit reportInfo("EEPROM Erase DONE!");
            } catch (const std::runtime_error &e1) {
                emit reportError(e1.what());
            }
            mutex.lock();
            this->erase_eeprom_path = "";
            mutex.unlock();
        }
        if (l_monitor_path.size() != 0)
        {
            try {
                QScopedPointer<Device> dev(comm.open(l_monitor_path));
                dev.data()->assertVersionIsAtLeast(2, 0, 0);
                std::string name = dev.data()->getKeyboardFilename();
                nameTranslation(name);
                emit keyboardName(name);
                emit thresholds(dev.data()->getThresholds());
                dev.data()->disableKeyboard();
                monitoredDevice = dev.take();
            } catch (const std::runtime_error &e1) {
                emit reportMonitorError(e1.what());
            }
            mutex.lock();
            this->monitor_path = "";
            mutex.unlock();
        }
        if (l_monitor_row_state_path.size() != 0)
        {
            try {
                QScopedPointer<Device> dev(comm.open(l_monitor_row_state_path));
                dev.data()->assertVersionIsAtLeast(2, 0, 4);
                std::vector<uint8_t> details = dev.data()->getKeyboardDetails();
                uint8_t rows = details[1];
                uint16_t max_dac = (details[7] | static_cast<uint16_t>((static_cast<uint16_t>(details[8]) << 8)));
                uint8_t capsense_rows = rows;
                if (dev.data()->isVersionAtLeast(2, 0, 5)) {
                    capsense_rows = details[9];
                }
                emit reportRowsAndMaxDac(rows, max_dac, capsense_rows);
                dev.data()->disableKeyboard();
                monitoredRowStateDevice = dev.take();
            } catch (const std::runtime_error &e1) {
                emit reportMonitorError(e1.what());
            }
            mutex.lock();
            monitor_row_state_path = "";
            mutex.unlock();
        }
        if (l_set_dac)
        {
            try {
                if (monitoredRowStateDevice!=nullptr)
                {
                    monitoredRowStateDevice->setDacValue(l_set_dac_value);
                } else {
                    throw std::runtime_error("device not open for row monitoring");
                }
            } catch (const std::runtime_error &e1) {
                emit reportError(e1.what());
            }
            mutex.lock();
            this->set_dac = false;
            mutex.unlock();
        }
        if (l_signal_level_path.size() != 0)
        {
            try {
                QScopedPointer<Device> dev(comm.open(l_signal_level_path));
                dev.data()->assertVersionIsAtLeast(2, 0, 2);
                std::string name = dev.data()->getKeyboardFilename();
                nameTranslation(name);
                emit keyboardName(name);
                dev.data()->disableKeyboard();
                std::vector<uint8_t> details = dev.data()->getKeyboardDetails();
                cols = details[0];
                rows = details[1];
                capsense_rows = rows;
                if (dev.data()->isVersionAtLeast(2, 0, 5)) {
                    capsense_rows = details[9];
                }
                current_col = current_row = 0;
                signalLevelDevice = dev.take();
            } catch (const std::runtime_error &e1) {
                emit reportMonitorError(e1.what());
            }
            mutex.lock();
            this->signal_level_path = "";
            mutex.unlock();
        }
        if (l_close_monitored_device)
        {
            if (monitoredDevice != nullptr)
            {
                monitoredDevice->enableKeyboard();
                delete monitoredDevice;
                monitoredDevice = nullptr;
            }
            if (signalLevelDevice != nullptr)
            {
                signalLevelDevice->enableKeyboard();
                delete signalLevelDevice;
                signalLevelDevice = nullptr;
            }
            if (monitoredRowStateDevice != nullptr)
            {
                monitoredRowStateDevice->enableKeyboard();
                delete monitoredRowStateDevice;
                monitoredRowStateDevice = nullptr;
            }
            mutex.lock();
            this->close_monitored_device = false;
            mutex.unlock();
        }
        if (monitoredDevice != nullptr)
        {
            emit keystate(monitoredDevice->getKeyState());
        }
        if (monitoredRowStateDevice != nullptr)
        {
            emit rowstate(monitoredRowStateDevice->getRowState());
        }
        if (signalLevelDevice != nullptr)
        {
            std::vector<uint16_t> signal_levels = signalLevelDevice->getSignalValue(current_col, current_row);
            unsigned long cnt = signal_levels.size();
            signal_levels.insert(signal_levels.begin(), current_row);
            signal_levels.insert(signal_levels.begin(), current_col);
            current_col += cnt;
            while (current_col >= cols) {
                current_col -= cols;
                current_row += 1;
            }
            if (current_row >= capsense_rows)
            {
                current_row = 0;
                current_col = 0;
            }
            emit reportSignalLevel(signal_levels);
        }
        if (l_keep_scanning)
        {
            msleep(10);
            std::vector<std::string> devices = comm.scan();
            emit scannedDevices(devices);
            if (l_autoenter_mode)
            {
                for(auto value : devices)
                {
                    try {
                        QScopedPointer<Device> dev(comm.open(value));
                        dev.data()->enterBootloader();
                    } catch (...)
                    {
                        // Ignore errors
                    }
                }
            }
        }
    }
}

