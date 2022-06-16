#include "mywidget.h"
#include "ugfx/src/ginput/ginput_driver_mouse.h"

extern GMouse* qwidgetMouse;
extern gCoord qwidgetMouseX;
extern gCoord qwidgetMouseY;
extern gCoord qwidgetMouseZ;
extern gU16 qwidgetMouseButtons;

MyWidget::MyWidget(QWidget* parent) : QWidget(parent)
{
    // GMouse
    if (!qwidgetMouse) {
        qFatal("MyWidget::MyWidget(): Invalid GMouse (nullptr).");
    }
    qwidgetMouse->display = nullptr;	// Set your display here!
}

void MyWidget::mousePressEvent(QMouseEvent* event)
{
    event->accept();

    qwidgetMouseX = event->x();
    qwidgetMouseY = event->y();
    qwidgetMouseZ = 1;

    if (event->buttons() & Qt::LeftButton) {
        qwidgetMouseButtons = GINPUT_MOUSE_BTN_LEFT;
    } else if (event->buttons() & Qt::RightButton) {
        qwidgetMouseButtons = GINPUT_MOUSE_BTN_RIGHT;
    }

    _gmouseWakeup(qwidgetMouse);
}

void MyWidget::mouseReleaseEvent(QMouseEvent* event)
{
    event->accept();

    qwidgetMouseZ = 0;
    qwidgetMouseButtons = 0;

    _gmouseWakeup(qwidgetMouse);
}

void MyWidget::mouseMoveEvent(QMouseEvent* event)
{
    event->accept();

    qwidgetMouseX = event->x();
    qwidgetMouseY = event->y();

    _gmouseWakeup(qwidgetMouse);
}
