#pragma once

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget* parent = nullptr);
    virtual ~MyWidget() = default;

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
    Q_DISABLE_COPY(MyWidget)
};
