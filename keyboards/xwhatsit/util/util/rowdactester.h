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

#ifndef ROWDACTESTER_H
#define ROWDACTESTER_H

#include <QDialog>
#include <QMenu>
#include "hidthread.h"

namespace Ui {
class RowDacTester;
}

class RowDacTester : public QDialog
{
    Q_OBJECT

public:
    explicit RowDacTester(HidThread &thread, std::string path, QWidget *parent);
    ~RowDacTester();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void ShowContextMenu(const QPoint &pos);

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int value);

    void on_horizontalSliderSupply_valueChanged(int value);

    void on_doubleSpinBoxSupply_valueChanged(double value);

    void on_RowDacTester_finished(int result);

    void on_rowstate(uint8_t);

    void on_reportMonitorError(std::string error_message);

    void on_reportRowsAndMaxDac(uint8_t rows, uint16_t max_dac, uint8_t capsense_rows);

private:
    Ui::RowDacTester *ui;
    void update_value(int value);
    void update_powersupply_value(int value_10mV);
    static const int HORIZONTAL_MARGIN = 10;
    static const int VERTICAL_MARGIN = 10;
    HidThread &thread;
    std::string path;
    uint8_t rowstate;
    uint8_t rows;
    uint16_t max_dac;
};

#endif // ROWDACTESTER_H
