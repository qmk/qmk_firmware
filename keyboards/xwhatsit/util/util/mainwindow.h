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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "monitorwindow.h"
#include "signal_level.h"
#include "communication.h"
#include "hidthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Communication &comm, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_updateScannedDevices(std::vector<std::string> devices);
    void on_reportError(std::string error_message);
    void on_reportInfo(std::string info_message);
    void on_listWidget_itemSelectionChanged();
    void on_enterBootloaderPushbutton_clicked();
    void on_keypressMinotorPushButton_clicked();

    void on_autoEnterModeCheckBox_stateChanged(int arg1);

    void on_eraseEepromPushButton_clicked();

    void on_signalLevelPushButton_clicked();
    void ShowContextMenu(const QPoint &pos);

    void on_columnTesterButton_clicked();

    void on_rowDacPushButton_clicked();

private:
    Ui::MainWindow *ui;
    Communication &comm;
    HidThread thread;
};

#endif // MAINWINDOW_H
