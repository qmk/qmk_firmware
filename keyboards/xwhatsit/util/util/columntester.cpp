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

#include "columntester.h"
#include "ui_columntester.h"
#include <QSizePolicy>
#include <stdio.h>
#include <QMenu>
#include <QAction>

ColumnTester::ColumnTester(HidThread &thread, std::string path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColumnTester),
    thread(thread),
    path(path)
{
    ui->setupUi(this);
    int i;
    for (i=1;i<24;i++)
    {
        QPushButton *button = new QPushButton(QString::number(i), this);
        buttons.push_back(button);
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        button->setMinimumSize(20, 0);
        button->setCheckable(true);
        button->setStyleSheet(":checked {background-color: #c0FFc0; color:black }");
        ui->horizontalLayout->addWidget(button);
        connect(button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    }
    connect(ui->pushButton_data, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_shcp, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_stcp, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(&thread, &HidThread::reportControlReadback, this, &ColumnTester::onReportControlState);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}

void ColumnTester::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1("Close", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(close()));
    contextMenu.addAction(&action1);
    contextMenu.exec(mapToGlobal(pos));
}

ColumnTester::~ColumnTester()
{
    for(auto const& value: buttons) {
        delete value;
    }

    delete ui;
}

void ColumnTester::onButtonClicked()
{
    uint32_t data = 0;
    for (int i=0;i<23;i++)
    {
        if (buttons[i]->isChecked())
        {
            data |= 1 << i;
        }
    }
    thread.shiftData(path, data,
                     ui->pushButton_data->isChecked(),
                     ui->pushButton_shcp->isChecked(),
                     ui->pushButton_stcp->isChecked());
}

void ColumnTester::onReportControlState(std::vector<uint8_t> readback)
{
    const bool enabled = readback.size() != 0;
    ui->pushButton_data->setEnabled(enabled);
    ui->pushButton_shcp->setEnabled(enabled);
    ui->pushButton_stcp->setEnabled(enabled);
    ui->label_control_set->setEnabled(enabled);
    ui->label_control_readback->setEnabled(enabled);
    if (enabled) {
        if (readback[0]) ui->frame_data->setStyleSheet("background-color:#c0FFc0");
        else ui->frame_data->setStyleSheet("background-color:");
        if (readback[1]) ui->frame_shcp->setStyleSheet("background-color:#c0FFc0");
        else ui->frame_shcp->setStyleSheet("background-color:");
        if (readback[2]) ui->frame_stcp->setStyleSheet("background-color:#c0FFc0");
        else ui->frame_stcp->setStyleSheet("background-color:");
    }
}
