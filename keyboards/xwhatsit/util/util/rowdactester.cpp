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

#include "rowdactester.h"
#include "ui_rowdactester.h"
#include <QPainter>
#include <QMessageBox>

RowDacTester::RowDacTester(HidThread &thread, std::string path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RowDacTester),
    thread(thread),
    path(path),
    rowstate(0)
{
    ui->setupUi(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(&thread, &HidThread::rowstate, this, &RowDacTester::on_rowstate);
    connect(&thread, &HidThread::reportMonitorError, this, &RowDacTester::on_reportMonitorError);
    connect(&thread, &HidThread::reportRowsAndMaxDac, this, &RowDacTester::on_reportRowsAndMaxDac);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}

void RowDacTester::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1("Close", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(close()));
    contextMenu.addAction(&action1);
    contextMenu.exec(mapToGlobal(pos));
}

RowDacTester::~RowDacTester()
{
    delete ui;
}

void RowDacTester::on_horizontalSlider_valueChanged(int value)
{
    update_value(value);
}

void RowDacTester::on_spinBox_valueChanged(int value)
{
    update_value(value);
}

void RowDacTester::update_value(int value)
{
    if (ui->horizontalSlider->value() != value)
    {
        ui->horizontalSlider->setValue(value);
    }
    if (ui->spinBox->value() != value)
    {
        ui->spinBox->setValue(value);
    }
    const double max_voltage = ui->doubleSpinBoxSupply->value();
    const double max_dac_value = this->max_dac;
    const double dac_voltage = max_voltage / max_dac_value * value;
    QString dac_voltage_str;
    dac_voltage_str.sprintf("%04.2f V", dac_voltage);
    ui->dac_voltage->setText(dac_voltage_str);
    const double pullup = 20;
    const double pulldown = 4.7;
    const double drv = 20;
    const double thresh_voltage = (dac_voltage + max_voltage * drv / pullup) / ( 1. + (1./pulldown + 1./pullup) * drv);
    QString thresh_voltage_str;
    thresh_voltage_str.sprintf("%04.2f V", thresh_voltage);
    ui->threshold_voltage->setText(thresh_voltage_str);
    thread.setDacValue(static_cast<uint16_t>(value));
}

void RowDacTester::update_powersupply_value(int value_10mV)
{
    if (ui->horizontalSliderSupply->value() != value_10mV)
    {
        if (ui->horizontalSliderSupply->maximum() < value_10mV)
        {
            ui->horizontalSliderSupply->setMaximum(value_10mV);
        }
        ui->horizontalSliderSupply->setValue(value_10mV);

    }
    if ((int)(ui->doubleSpinBoxSupply->value() * 100 + 0.5) != value_10mV)
    {
        ui->doubleSpinBoxSupply->setValue(value_10mV / 100.);
    }
    update_value(ui->spinBox->value());
}

void RowDacTester::on_horizontalSliderSupply_valueChanged(int value)
{
    update_powersupply_value(value);
}

void RowDacTester::on_doubleSpinBoxSupply_valueChanged(double value)
{
     update_powersupply_value((int)(value * 100 + 0.5));
}

void RowDacTester::on_rowstate(uint8_t rowstate)
{
    this->rowstate = rowstate;
    this->repaint();
}

void RowDacTester::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    const int yadd = ui->threshold_voltage->geometry().y() + ui->threshold_voltage->geometry().height() + VERTICAL_MARGIN;
    const int xadd = HORIZONTAL_MARGIN;
    const int nrows = this->rows;
    double cell_width = (1. * this->width() - HORIZONTAL_MARGIN) / nrows;
    double cell_height = (1. * this->height() - VERTICAL_MARGIN - yadd);
    painter.setPen(QPen(Qt::black));
    int i;
    for (i=0;i<nrows;i++)
    {
        if ((this->rowstate >> i) & 1)
        {
            painter.setBrush(QBrush(QColor("#00FF00")));
        } else {
            painter.setBrush(QBrush(QColor("#008000")));
        }

        QRectF rect(xadd + i * cell_width, yadd, cell_width - HORIZONTAL_MARGIN, cell_height);
        painter.drawRect(rect);
    }
    this->setMinimumHeight(yadd + VERTICAL_MARGIN + VERTICAL_MARGIN * 3);
}

void RowDacTester::on_reportMonitorError(std::string error_message)
{
    QMessageBox::critical(this, "Error", error_message.c_str());
}

void RowDacTester::on_RowDacTester_finished(int result)
{
    Q_UNUSED(result);
    thread.closeMonitoredDevice();
}

void RowDacTester::on_reportRowsAndMaxDac(uint8_t rows, uint16_t max_dac, uint8_t capsense_rows)
{
    (void)rows; // unused
    this->rows = capsense_rows;
    this->max_dac = max_dac;
    this->ui->spinBox->setMaximum(max_dac);
    this->ui->horizontalSlider->setMaximum(max_dac);
    update_value(max_dac);
    this->repaint();
}
