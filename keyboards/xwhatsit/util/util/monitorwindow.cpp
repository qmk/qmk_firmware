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

#include "monitorwindow.h"
#include "ui_monitorwindow.h"
#include <QGraphicsView>
#include <QPainter>
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <iostream>
#include <algorithm>
#include "kbd_defs.h"

MonitorWindow::MonitorWindow(HidThread &thread, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorWindow),
    thread(thread)
{
    ui->setupUi(this);
    keyboard = nullptr;
    current_layout = nullptr;
    connect(&thread, &HidThread::keyboardName, this, &MonitorWindow::on_keyboardName);
    connect(&thread, &HidThread::reportMonitorError, this, &MonitorWindow::on_reportMonitorError);
    connect(&thread, &HidThread::thresholds, this, &MonitorWindow::on_thresholds);
    connect(&thread, &HidThread::keystate, this, &MonitorWindow::on_keystate);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
    HORIZONTAL_MARGIN = 10;
    VERTICAL_MARGIN = 10;
}

void MonitorWindow::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction action1("Close", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(close()));
    contextMenu.addAction(&action1);
    contextMenu.exec(mapToGlobal(pos));
}

MonitorWindow::~MonitorWindow()
{
    delete ui;
}

void MonitorWindow::setMinimumSizeUnits(unsigned int width_units_times_8, unsigned int height_units_times_8)
{
    HORIZONTAL_MARGIN = ui->label_keyboardname->pos().x();
    VERTICAL_MARGIN = ui->label_keyboardname->pos().x();
    this->setMinimumSize(static_cast<int>(width_units_times_8 * MIN_HORIZONTAL_SCALE / 8 + 2 * HORIZONTAL_MARGIN),
                         ui->last_label->geometry().y() + ui->last_label->geometry().height() +
                             static_cast<int>(height_units_times_8 * MIN_VERTICAL_SCALE / 8 + 2 * VERTICAL_MARGIN));
}

void MonitorWindow::loadLayout(QString name)
{
    int i;
    ui->layoutSel->clear();
    for (i=0;i<n_keyboards;i++)
    {
        if (name.compare(QString(keyboards[i].kbd_name))==0)
        {
            keyboard = &keyboards[i];
            is_was_key_pressed = std::vector<std::vector<int>>(static_cast<unsigned long>(keyboard->rows), std::vector<int>(static_cast<unsigned long>(keyboard->cols), 0));
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
            const unsigned int w8 = static_cast<unsigned int>((layout->keys[j].x + layout->keys[j].w)*8 + 0.5);
            const unsigned int h8 = static_cast<unsigned int>((layout->keys[j].y + layout->keys[j].h)*8 + 0.5);
            if (w8 > keyboard_width_uis_times_8) keyboard_width_uis_times_8 = w8;
            if (h8 > keyboard_height_uis_times_8) keyboard_height_uis_times_8 = h8;
        }
    }
    setMinimumSizeUnits(keyboard_width_uis_times_8, keyboard_height_uis_times_8);
}

void MonitorWindow::displaySquare(int x, int y, int w, int h, unsigned int col, unsigned int row, QPainter &painter, bool has_threshold)
{
    QPen textColor(Qt::black);
    painter.setPen(QPen(Qt::black));
    switch (is_was_key_pressed.at(row).at(col))
    {
        case 1:
        case 3:
            textColor = QPen(Qt::white);
            painter.setBrush(QBrush(QColor("#008000")));
            break;
        case 2:
            painter.setBrush(QBrush(QColor("#00FF00")));
            break;
        default:
            painter.setBrush(QBrush(QColor("#FFFFFF")));
            break;
    }
    QRectF rect(x, y, w, h);
    painter.drawRect(rect);
    if (thresholds.size() && has_threshold)
    {
        uint16_t threshold = get_threshold(col, row);
        painter.setPen(textColor);
        painter.drawText(rect, Qt::AlignCenter, QString::number(threshold));
    }
}

void MonitorWindow::updateCurrentLayout()
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

void MonitorWindow::paintEvent(QPaintEvent *event)
{
    HORIZONTAL_MARGIN = ui->label_keyboardname->pos().x();
    VERTICAL_MARGIN = ui->label_keyboardname->pos().x();
    Q_UNUSED(event);
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
            displaySquare(x, y, w, h, col, row, painter, row < keyboard->rows - keyboard->extra_direct_rows);
        }
    } else {
        unsigned int col, row;
        double scale_x = (1. * this->width() - 2 * HORIZONTAL_MARGIN) / keyboard->cols;
        double scale_y = (1. * this->height() - VERTICAL_MARGIN - yadd) / keyboard->rows;
        for (row = 0; row < keyboard->rows; row++)
        {
            for (col = 0; col < keyboard->cols; col++)
            {
                const int x__ = static_cast<int>(scale_x * col + 0.5);
                const int y__ = static_cast<int>(scale_y * row + 0.5);
                const int w = static_cast<int>(scale_x * (col + 1) + 0.5) - x__;
                const int h = static_cast<int>(scale_y * (row + 1) + 0.5) - y__;
                const int x = x__ + xadd;
                const int y = y__ + yadd;
                displaySquare(x, y, w, h, col, row, painter, row < keyboard->rows - keyboard->extra_direct_rows);
            }
        }
    }
}

void MonitorWindow::on_layoutSel_activated(const QString &arg1)
{
    Q_UNUSED(arg1);
    updateCurrentLayout();
    if (this->current_layout)
    {
        setMinimumSizeUnits(this->keyboard_width_uis_times_8, this->keyboard_height_uis_times_8);
    } else {
        setMinimumSizeUnits(this->keyboard->cols * 8, this->keyboard->rows * 8);
    }
    this->repaint();
}

void MonitorWindow::on_keyboardName(std::string name)
{
    loadLayout(QString::fromStdString(name));
    this->repaint();
}

void MonitorWindow::on_thresholds(std::vector<std::vector<uint8_t>> thresholds)
{
    this->thresholds = thresholds;
    this->repaint();
}

void MonitorWindow::on_keystate(std::vector<uint8_t> data)
{
    unsigned int col, row;
    int different = 0;
    if (!keyboard) return;
    unsigned int bytes_per_row = 1;
    if (keyboard->cols > 16)
    {
        bytes_per_row = 4;
    } else if (keyboard->cols > 8)
    {
        bytes_per_row = 2;
    }
    for (col=0; col < keyboard->cols; col++)
    {
        for (row=0; row < keyboard->rows; row++)
        {
            uint8_t pressed = (data.at(col / 8 + row * bytes_per_row) >> (col % 8)) & 1;
            int new_is_was_key_pressed = is_was_key_pressed.at(row).at(col);
            if (pressed) new_is_was_key_pressed |= 3;
            else new_is_was_key_pressed &= ~1;
            if (is_was_key_pressed.at(row).at(col) != new_is_was_key_pressed) different = 1;
            is_was_key_pressed.at(row).at(col) = new_is_was_key_pressed;
        }
    }
    if (different) this->repaint();
}

uint16_t MonitorWindow::get_threshold(unsigned int col, unsigned int row)
{
    if (thresholds.at(0).at(0) == 0) return static_cast<uint16_t>((thresholds.at(0).at(1) | (thresholds.at(0).at(2) << 8)));
    unsigned int i;
    unsigned int bytes_per_row = 1;
    if (keyboard->cols > 16)
    {
        bytes_per_row = 4;
    } else if (keyboard->cols > 8)
    {
        bytes_per_row = 2;
    }
    for (i=0;i<thresholds.at(0).at(0); i++)
    {
        if ((thresholds.at(i).at(3 + col / 8 + row * bytes_per_row) >> (col % 8)) & 1)
        {
            return static_cast<uint16_t>(thresholds.at(i).at(1) | (thresholds.at(i).at(2) << 8));
        }
    }
    return 0;
}

void MonitorWindow::on_reportMonitorError(std::string error_message)
{
    QMessageBox::critical(this, "Error", error_message.c_str());
}

void MonitorWindow::on_MonitorWindow_finished(int result)
{
    Q_UNUSED(result);
    thread.closeMonitoredDevice();
}
