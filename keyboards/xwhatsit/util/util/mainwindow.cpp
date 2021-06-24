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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <QMessageBox>
#include <QMetaType>
#include <QMenu>
#include <QAction>
#include "columntester.h"
#include "rowdactester.h"

Q_DECLARE_METATYPE(std::vector<std::string>)
Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<std::vector<uint8_t> >)
Q_DECLARE_METATYPE(std::vector<uint8_t>)
Q_DECLARE_METATYPE(std::vector<uint16_t>)
Q_DECLARE_METATYPE(uint8_t)

MainWindow::MainWindow(Communication &comm, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    comm(comm),
    thread(comm)
{
    ui->setupUi(this);
    qRegisterMetaType<std::vector<std::string>>("vector_of_strings");
    qRegisterMetaType<std::string>("std_string");
    qRegisterMetaType<std::vector<std::vector<uint8_t>>>("vector_of_vector_of_uint8t");
    qRegisterMetaType<std::vector<uint8_t>>("vector_of_uint8t");
    qRegisterMetaType<std::vector<uint16_t>>("vector_of_uint16t");
    qRegisterMetaType<uint8_t>("uint8_t");
    qRegisterMetaType<uint16_t>("uint16_t");
    connect(&thread, &HidThread::scannedDevices, this, &MainWindow::on_updateScannedDevices);
    connect(&thread, &HidThread::reportError, this, &MainWindow::on_reportError);
    connect(&thread, &HidThread::reportInfo, this, &MainWindow::on_reportInfo);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
    thread.start();
    thread.setScanning(true);
}

void MainWindow::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1("Close", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(close()));
    contextMenu.addAction(&action1);
    contextMenu.exec(mapToGlobal(pos));
}

void MainWindow::on_updateScannedDevices(std::vector<std::string> devices)
{
    int i;
    for (i=ui->listWidget->count()-1;i>=0;i--)
    {
        bool found = false;
        for (auto value : devices)
        {
            if (ui->listWidget->item(i)->text().toStdString().compare(value)==0)
            {
                found = true;
            }
        }
        if (!found) {
            delete ui->listWidget->takeItem(i);
        }
    }
    int countBefore = ui->listWidget->count();
    for (auto value : devices)
    {
        bool found = false;
        for (i=ui->listWidget->count()-1;i>=0;i--)
        {
            if (ui->listWidget->item(i)->text().toStdString().compare(value)==0)
            {
                found = true;
            }
        }
        if (!found)
        {
            ui->listWidget->addItem(QString::fromStdString(value));
        }
    }
    if ((countBefore == 0) && (ui->listWidget->count() == 1))
    {
        ui->listWidget->setCurrentRow(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    bool is_xwhatsit = false;
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item)
    {
        is_xwhatsit = is_xwhatsit_original_firmware_path(item->text().toStdString());
    }
    bool enabled = !!ui->listWidget->currentItem();
    ui->enterBootloaderPushbutton->setEnabled(enabled);
    ui->keypressMinotorPushButton->setEnabled(enabled && !is_xwhatsit);
    ui->eraseEepromPushButton->setEnabled(enabled && !is_xwhatsit);
    ui->signalLevelPushButton->setEnabled(enabled && !is_xwhatsit);
    ui->columnTesterButton->setEnabled(enabled && !is_xwhatsit);
    ui->rowDacPushButton->setEnabled(enabled && !is_xwhatsit);
    Q_UNUSED(is_xwhatsit);
}

void MainWindow::on_enterBootloaderPushbutton_clicked()
{
    thread.enterBootloader(ui->listWidget->currentItem()->text().toStdString());
}

void MainWindow::on_reportError(std::string error_message)
{
    QMessageBox::critical(this, "Error", error_message.c_str());
}

void MainWindow::on_reportInfo(std::string info_message)
{
    QMessageBox::information(this, "Info", info_message.c_str());
}

void MainWindow::on_keypressMinotorPushButton_clicked()
{
    MonitorWindow *mw = new MonitorWindow(thread, this);
    mw->setAttribute(Qt::WA_DeleteOnClose);
    //mw->setWindowModality(Qt::WindowModal);
    thread.monitor(ui->listWidget->currentItem()->text().toStdString());
    bool previousScanning = thread.setScanning(false);
    this->setEnabled(false);
    mw->setEnabled(true);
    mw->exec();
    this->setEnabled(true);
    thread.setScanning(previousScanning);
}

void MainWindow::on_autoEnterModeCheckBox_stateChanged(int arg1)
{
    thread.setAutoEnter(arg1);
}

void MainWindow::on_eraseEepromPushButton_clicked()
{
    thread.eraseEeprom(ui->listWidget->currentItem()->text().toStdString());
}

void MainWindow::on_signalLevelPushButton_clicked()
{
    SignalLevelMonitorWindow *mw = new SignalLevelMonitorWindow(thread, this);
    mw->setAttribute(Qt::WA_DeleteOnClose);
    //mw->setWindowModality(Qt::WindowModal);
    thread.signalLevel(ui->listWidget->currentItem()->text().toStdString());
    bool previousScanning = thread.setScanning(false);
    this->setEnabled(false);
    mw->setEnabled(true);
    mw->exec();
    this->setEnabled(true);
    thread.setScanning(previousScanning);
}

void MainWindow::on_columnTesterButton_clicked()
{
    std::string path = ui->listWidget->currentItem()->text().toStdString();
    ColumnTester *ctw = new ColumnTester(thread, path, this);
    ctw->setAttribute(Qt::WA_DeleteOnClose);
    bool previousScanning = thread.setScanning(false);
    thread.shiftData(path, 0, 0, 0 ,0);
    this->setEnabled(false);
    ctw->setEnabled(true);
    ctw->exec();
    thread.shiftData(path, 0, 0, 0, 0);
    this->setEnabled(true);
    thread.enableKeyboard(path);
    thread.setScanning(previousScanning);
}

void MainWindow::on_rowDacPushButton_clicked()
{
    std::string path = ui->listWidget->currentItem()->text().toStdString();
    RowDacTester *w = new RowDacTester(thread, path, this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    bool previousScanning = thread.setScanning(false);
    thread.monitorRowState(path);
    this->setEnabled(false);
    w->setEnabled(true);
    w->exec();
    this->setEnabled(true);
    thread.setScanning(previousScanning);
}
