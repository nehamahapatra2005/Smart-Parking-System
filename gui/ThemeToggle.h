#ifndef THEME_TOGGLE_H
#define THEME_TOGGLE_H

#include <QAbstractButton>
#include <QPropertyAnimation>
#include <QSize>

// Small animated switch for light and dark mode
class ThemeToggle : public QAbstractButton {
    Q_OBJECT

    Q_PROPERTY(qreal knobPosition READ knobPosition WRITE setKnobPosition)

public:
    explicit ThemeToggle(QWidget *parent = nullptr);

    QSize sizeHint() const override;

    qreal knobPosition() const;
    void setKnobPosition(qreal position);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPropertyAnimation* animation;
    qreal m_knobPosition;
};

#endif