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

#ifndef COLUMNTESTER_H
#define COLUMNTESTER_H

#include <QDialog>
#include <QPoint>
#include <QPushButton>
#include <vector>
#include "hidthread.h"

namespace Ui {
class ColumnTester;
}

class ColumnTester : public QDialog
{
    Q_OBJECT

public:
    explicit ColumnTester(HidThread &thread, std::string path, QWidget *parent = nullptr);
    ~ColumnTester();

private slots:
    void onButtonClicked();
    void ShowContextMenu(const QPoint &pos);
    void onReportControlState(std::vector<uint8_t>);

private:
    Ui::ColumnTester *ui;
    std::vector<QPushButton *> buttons;
    HidThread &thread;
    std::string path;
};

#endif // COLUMNTESTER_H
