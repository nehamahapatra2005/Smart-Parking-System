#include "ThemeToggle.h"

#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QEasingCurve>

// Creates the theme switch
ThemeToggle::ThemeToggle(QWidget *parent)
    : QAbstractButton(parent),
      animation(new QPropertyAnimation(this, "knobPosition")),
      m_knobPosition(0.0) {

    setCheckable(true);
    setCursor(Qt::PointingHandCursor);

    // Smaller size so it fits better in the sidebar
    setFixedSize(54, 28);

    // Smooth sliding animation
    animation->setDuration(350);
    animation->setEasingCurve(QEasingCurve::InOutCubic);

    connect(
        this,
        &QAbstractButton::toggled,
        this,
        [this](bool checked) {

            animation->stop();

            animation->setStartValue(m_knobPosition);
            animation->setEndValue(checked ? 1.0 : 0.0);

            animation->start();
        }
    );
}

// Size used by the sidebar layout
QSize ThemeToggle::sizeHint() const {
    return QSize(54, 28);
}

// Current knob position
qreal ThemeToggle::knobPosition() const {
    return m_knobPosition;
}

// Updates the knob while it is moving
void ThemeToggle::setKnobPosition(qreal position) {
    m_knobPosition = position;
    update();
}

// Draws the switch
void ThemeToggle::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const qreal w = width();
    const qreal h = height();

    // ---------------------------------------------------------
    // Background
    // ---------------------------------------------------------

    QRectF background(
        1,
        1,
        w - 2,
        h - 2
    );

    painter.setPen(Qt::NoPen);

    if (isChecked()) {
        // Dark mode
        painter.setBrush(QColor("#2f80ed"));
    } else {
        // Light mode
        painter.setBrush(QColor("#d9dee7"));
    }

    painter.drawRoundedRect(
        background,
        h / 2,
        h / 2
    );

    // ---------------------------------------------------------
    // Small inactive icons
    // ---------------------------------------------------------

    painter.setFont(
        QFont("Sans", 8, QFont::Normal)
    );

    // Light mode icon on the left
    painter.setPen(
        isChecked()
            ? QColor("#7fa9df")
            : QColor("#8b95a5")
    );

    painter.drawText(
        QRectF(5, 0, 20, h),
        Qt::AlignCenter,
        "☀"
    );

    // Dark mode icon on the right
    painter.setPen(
        isChecked()
            ? QColor("#dce9ff")
            : QColor("#8b95a5")
    );

    painter.drawText(
        QRectF(w - 25, 0, 20, h),
        Qt::AlignCenter,
        "☾"
    );

    // ---------------------------------------------------------
    // Sliding knob
    // ---------------------------------------------------------

    const qreal knobSize = 22.0;

    const qreal left =
        3.0;

    const qreal right =
        w - knobSize - 3.0;

    const qreal x =
        left +
        (right - left) * m_knobPosition;

    painter.setBrush(Qt::white);

    painter.drawEllipse(
        QRectF(
            x,
            (h - knobSize) / 2,
            knobSize,
            knobSize
        )
    );

    // ---------------------------------------------------------
    // Active icon inside the knob
    // ---------------------------------------------------------

    painter.setFont(
        QFont("Sans", 8, QFont::Bold)
    );

    painter.setPen(
        isChecked()
            ? QColor("#2f80ed")
            : QColor("#6b7280")
    );

    painter.drawText(
        QRectF(
            x,
            (h - knobSize) / 2,
            knobSize,
            knobSize
        ),
        Qt::AlignCenter,
        isChecked() ? "☾" : "☀"
    );
}