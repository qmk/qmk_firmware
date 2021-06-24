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

#include "signal_level.h"
#include "ui_signal_level.h"
#include <QGraphicsView>
#include <QPainter>
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <iostream>
#include <algorithm>
#include "kbd_defs.h"

SignalLevelMonitorWindow::SignalLevelMonitorWindow(HidThread &thread, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalLevelMonitorWindow),
    thread(thread)
{
    ui->setupUi(this);
    keyboard = nullptr;
    current_layout = nullptr;
    connect(&thread, &HidThread::keyboardName, this, &SignalLevelMonitorWindow::on_keyboardName);
    connect(&thread, &HidThread::reportMonitorError, this, &SignalLevelMonitorWindow::on_reportMonitorError);
    connect(&thread, &HidThread::reportSignalLevel, this, &SignalLevelMonitorWindow::on_signallevel);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
    HORIZONTAL_MARGIN = 10;
    VERTICAL_MARGIN = 10;
}

void SignalLevelMonitorWindow::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1("Close", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(close()));
    contextMenu.addAction(&action1);
    contextMenu.exec(mapToGlobal(pos));
}

SignalLevelMonitorWindow::~SignalLevelMonitorWindow()
{
    delete ui;
}

void SignalLevelMonitorWindow::setMinimumSizeUnits(unsigned int width_units_times_8, unsigned int height_units_times_8)
{
    HORIZONTAL_MARGIN = ui->label_keyboardname->pos().x();
    VERTICAL_MARGIN = ui->label_keyboardname->pos().x();
    this->setMinimumSize(static_cast<int>(width_units_times_8 * MIN_HORIZONTAL_SCALE / 8 + 2 * HORIZONTAL_MARGIN),
                         ui->last_label->geometry().y() + ui->last_label->geometry().height() +
                             static_cast<int>(height_units_times_8 * MIN_VERTICAL_SCALE / 8 + 2 * VERTICAL_MARGIN));
}

void SignalLevelMonitorWindow::loadLayout(QString name)
{
    int i;
    ui->layoutSel->clear();
    for (i=0;i<n_keyboards;i++)
    {
        if (name.compare(QString(keyboards[i].kbd_name))==0)
        {
            keyboard = &keyboards[i];
            this->signal_level = std::vector<std::vector<uint16_t>>(static_cast<unsigned long>(keyboard->rows-keyboard->extra_direct_rows), std::vector<uint16_t>(static_cast<unsigned long>(keyboard->cols), 0xFFFFU));
            this->max_signal_level = std::vector<std::vector<uint16_t>>(static_cast<unsigned long>(keyboard->rows-keyboard->extra_direct_rows), std::vector<uint16_t>(static_cast<unsigned long>(keyboard->cols), 0xFFFFU));
            this->min_signal_level = std::vector<std::vector<uint16_t>>(static_cast<unsigned long>(keyboard->rows-keyboard->extra_direct_rows), std::vector<uint16_t>(static_cast<unsigned long>(keyboard->cols), 0xFFFFU));
            int j;
            for (j=0;j<keyboard->n_layouts;j++)
            {
                ui->layoutSel->addItem(QString(keyboard->layouts[j].lay_name));
            }
            break;
        }
    }
    ui->layoutSel->addItem(QString("Matrix (without showing skipped columns/rows)"));
    QString name_simp = name;
    if (name.startsWith("keyboards/")) name_simp = name.mid(strlen("keyboards/"));
    int lastslash = name_simp.lastIndexOf("/");
    if (lastslash > 0) name_simp = name_simp.left(lastslash);
    ui->label_keyboardname->setText(QString("Keyboard: ") + name_simp);
    ui->layoutSel->setEnabled(true);
    if (!keyboard)
    {
        on_reportMonitorError("Unknown keyboard (you may need to update the util version)!");
        this->close();
        return;
    }
    keyboard_width_uis_times_8 = 0;
    keyboard_height_uis_times_8 = 0;
    for (i=0;i<keyboard->n_layouts;i++)
    {
        const struct lay_def *layout = &keyboard->layouts[i];
        int j;
        for (j=0;j<layout->n_keys;j++)
        {
            unsigned int w8 = static_cast<unsigned int>((layout->keys[j].x + layout->keys[j].w)*8 + 0.5);
            unsigned int h8 = static_cast<unsigned int>((layout->keys[j].y + layout->keys[j].h)*8 + 0.5);
            if (w8 > keyboard_width_uis_times_8) keyboard_width_uis_times_8 = w8;
            if (h8 > keyboard_height_uis_times_8) keyboard_height_uis_times_8 = h8;
        }
    }
    setMinimumSizeUnits(keyboard_width_uis_times_8, keyboard_height_uis_times_8);
}

QColor SignalLevelMonitorWindow::getColor(uint16_t value, uint16_t mins, uint16_t maxs)
{
    double scale = (value - mins + 0.0) / (maxs - mins);
    uint8_t red = static_cast<uint8_t>(0xff * (1 - scale) + 0xc0 * scale);
    uint8_t green = static_cast<uint8_t>(0xff * scale + 0xc0 * (1 - scale));
    uint8_t blue = 0xc0;
    return QColor(red, green, blue);
}

void SignalLevelMonitorWindow::displaySquare(int x, int y, int w, int h, unsigned int col, unsigned int row, uint16_t mins, uint16_t maxs, QPainter &painter)
{
    painter.setPen(QPen(Qt::black));
    painter.setBrush(Qt::NoBrush);
    QRectF rect(x, y, w, h);
    painter.drawRect(rect);
    if ((signal_level.at(row).at(col)!=0xffffu) && (mins!=maxs))
    {
        painter.setPen(Qt::NoPen);
        QString maxstring = QString::number(max_signal_level.at(row).at(col));
        QString currstring = QString::number(signal_level.at(row).at(col));
        QString minstring = QString::number(min_signal_level.at(row).at(col));
        painter.setBrush(QBrush(getColor(max_signal_level.at(row).at(col), mins, maxs)));
        QRectF recti_max(x+1, y+1, w-1, (h-1) / 3);
        painter.drawRect(recti_max);
        painter.setBrush(QBrush(getColor(signal_level.at(row).at(col), mins, maxs)));
        QRectF recti_curr(x+1, y+1 + (h-1) / 3, w-1, (h-1) / 3);
        painter.drawRect(recti_curr);
        painter.setBrush(QBrush(getColor(min_signal_level.at(row).at(col), mins, maxs)));
        QRectF recti_min(x+1, y+1 + (h-1) / 3 *2, w-1, h-1 - ((h-1) / 3) * 2);
        painter.drawRect(recti_min);
        painter.setPen(Qt::black);
        painter.drawText(recti_max, Qt::AlignCenter, maxstring);
        painter.drawText(recti_curr, Qt::AlignCenter, currstring);
        painter.drawText(recti_min, Qt::AlignCenter, minstring);

    } else {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor("#FFFFFF")));
        QRectF recti(x+1, y+1, w-1, h-1);
        painter.drawRect(recti);
        if (signal_level.at(row).at(col)!=0xffffu)
        {
            painter.setPen(Qt::black);
            QString currstring = QString::number(signal_level.at(row).at(col));
            painter.drawText(recti, Qt::AlignCenter, currstring);
        }
    }
}

void SignalLevelMonitorWindow::updateCurrentLayout()
{
    int i;
    this->current_layout = nullptr;
    for (i=0;i<keyboard->n_layouts;i++)
    {
        if (ui->layoutSel->currentText().compare(QString(keyboard->layouts[i].lay_name))==0)
        {
            this->current_layout = &keyboard->layouts[i];
            return;
        }
    }
}

void SignalLevelMonitorWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    HORIZONTAL_MARGIN = ui->label_keyboardname->pos().x();
    VERTICAL_MARGIN = ui->label_keyboardname->pos().x();
    if (!keyboard) return;
    QPainter painter(this);
    int xadd = HORIZONTAL_MARGIN;
    int yadd = ui->last_label->geometry().y() + ui->last_label->geometry().height() + VERTICAL_MARGIN;
    updateCurrentLayout();
    const struct lay_def *layout = this->current_layout;
    if (layout)
    {
        double scale_x = (1. * this->width() - 1 - 2 * HORIZONTAL_MARGIN) * 8 / keyboard_width_uis_times_8;
        double scale_y = (1. * this->height() - 1 - VERTICAL_MARGIN - yadd) * 8 / keyboard_height_uis_times_8;
        int j;
        uint16_t mins = 0xffffu, maxs = 0xffffu;
        for (j=0;j<layout->n_keys;j++)
        {
            const unsigned int col = layout->keys[j].col;
            const unsigned int row = layout->keys[j].row;
            if (row >= (keyboard->rows-keyboard->extra_direct_rows))
                break;
            if (signal_level.at(row).at(col)!=0xffffu)
            {
                if ((mins == 0xffffu) || (mins > min_signal_level.at(row).at(col)))
                {
                    mins = min_signal_level.at(row).at(col);
                }
                if ((maxs == 0xffffu) || (maxs < max_signal_level.at(row).at(col)))
                {
                    maxs = max_signal_level.at(row).at(col);
                }
            }
        }
        for (j=0;j<layout->n_keys;j++)
        {
            const unsigned int col = layout->keys[j].col;
            const unsigned int row = layout->keys[j].row;
            const int x_ = static_cast<int>(layout->keys[j].x * 8 + 0.5);
            const int y_ = static_cast<int>(layout->keys[j].y * 8 + 0.5);
            const int w_ = static_cast<int>(layout->keys[j].w * 8 + 0.5);
            const int h_ = static_cast<int>(layout->keys[j].h * 8 + 0.5);
            const int x__ = static_cast<int>(scale_x * x_ / 8 + 0.5);
            const int y__ = static_cast<int>(scale_y * y_ / 8 + 0.5);
            const int w = static_cast<int>(scale_x * (x_ + w_) / 8 + 0.5) - x__;
            const int h = static_cast<int>(scale_y * (y_ + h_) / 8 + 0.5) - y__;
            const int x = x__ + xadd;
            const int y = y__ + yadd;
            if (row < (keyboard->rows-keyboard->extra_direct_rows)) {
                displaySquare(x, y, w, h, col, row, mins, maxs, painter);
            }
        }
    } else {
        unsigned int col, row;
        double scale_x = (1. * this->width() - 2 * HORIZONTAL_MARGIN) / keyboard->cols;
        double scale_y = (1. * this->height() - VERTICAL_MARGIN - yadd) / (keyboard->rows-keyboard->extra_direct_rows);
        uint16_t mins = 0xffffu, maxs = 0xffffu;
        for (row = 0; row < (keyboard->rows-keyboard->extra_direct_rows); row++)
        {
            for (col = 0; col < keyboard->cols; col++)
            {
                if (signal_level.at(row).at(col)!=0xffffu)
                {
                    if ((mins == 0xffffu) || (mins > min_signal_level.at(row).at(col)))
                    {
                        mins = min_signal_level.at(row).at(col);
                    }
                    if ((maxs == 0xffffu) || (maxs < max_signal_level.at(row).at(col)))
                    {
                        maxs = max_signal_level.at(row).at(col);
                    }
                }
            }
        }
        for (row = 0; row < (keyboard->rows-keyboard->extra_direct_rows); row++)
        {
            for (col = 0; col < keyboard->cols; col++)
            {
                const int x__ = static_cast<int>(scale_x * col + 0.5);
                const int y__ = static_cast<int>(scale_y * row + 0.5);
                const int w = static_cast<int>(scale_x * (col + 1) + 0.5) - x__;
                const int h = static_cast<int>(scale_y * (row + 1) + 0.5) - y__;
                const int x = x__ + xadd;
                const int y = y__ + yadd;
                displaySquare(x, y, w, h, col, row, mins, maxs, painter);
            }
        }
    }
}

void SignalLevelMonitorWindow::on_layoutSel_activated(const QString &arg1)
{
    Q_UNUSED(arg1);
    updateCurrentLayout();
    if (this->current_layout)
    {
        setMinimumSizeUnits(this->keyboard_width_uis_times_8, this->keyboard_height_uis_times_8);
    } else {
        setMinimumSizeUnits(this->keyboard->cols * 8, (keyboard->rows-keyboard->extra_direct_rows) * 8);
    }
    this->repaint();
}

void SignalLevelMonitorWindow::on_keyboardName(std::string name)
{
    loadLayout(QString::fromStdString(name));
    this->repaint();
}

void SignalLevelMonitorWindow::on_signallevel(std::vector<uint16_t> data)
{
    if (!keyboard)
    {
        return;
    }
    uint16_t col = data.at(0);
    uint16_t row = data.at(1);
    unsigned int i;
    bool different = false;
    for (i=2;i<data.size();i++)
    {
        if (signal_level.at(row).at(col) != data.at(i))
        {
            different = true;
        }
        signal_level.at(row).at(col) = data.at(i);
        if ((min_signal_level.at(row).at(col)==0xffffu) || (data.at(i) < min_signal_level.at(row).at(col)))
        {
            min_signal_level.at(row).at(col) = data.at(i);
        }
        if ((max_signal_level.at(row).at(col)==0xffffu) || (data.at(i) > max_signal_level.at(row).at(col)))
        {
            max_signal_level.at(row).at(col) = data.at(i);
        }
        col += 1;
        if (col >= keyboard->cols)
        {
            col -= keyboard->cols;
            row += 1;
        }
        if (row >= (keyboard->rows-keyboard->extra_direct_rows))
        {
            break;
        }
    }
    if (different)
        this->repaint();
}

void SignalLevelMonitorWindow::on_reportMonitorError(std::string error_message)
{
    QMessageBox::critical(this, "Error", error_message.c_str());
}

void SignalLevelMonitorWindow::on_SignalLevelMonitorWindow_finished(int result)
{
    Q_UNUSED(result);
    thread.closeMonitoredDevice();
}
