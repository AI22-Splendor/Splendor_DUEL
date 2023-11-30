#include "BackgroundWidgetUI.h"
#include <qpainter.h>

void BackgroundWidgetUI::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    int numRepetitionsWidth = width() / pix.width() + 1;
    int numRepetitionsHeight = height() / pix.height() + 1;

    for (int i = 0; i < numRepetitionsWidth; ++i) {
        for (int j = 0; j < numRepetitionsHeight; ++j) {
            painter.drawPixmap(i * pix.width(), j * pix.height(), pix);
        }
    }
}