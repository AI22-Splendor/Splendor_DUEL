#include "PlayerPoints.h"
#include <qpainter.h>
#include "Image.h"


PlayerPoints::PlayerPoints(QWidget* parent) : QWidget(parent) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
PlayerPoints::~PlayerPoints() {

}

void PlayerPoints::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, width(), height(), Image::getPlayersPoints());
}