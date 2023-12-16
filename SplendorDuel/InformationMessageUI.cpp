#include "InformationMessageUI.h"
#include <qpainter.h>
#include <qgridlayout.h>
#include <qevent.h>

InformationMessageUI::InformationMessageUI(QWidget* parent) : err(false), button("aide", this), QWidget(parent), afficher(false), message(Message("", "")) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20, 20);
    button.setFixedSize(50, 50);
    QHBoxLayout hbox(this);
    hbox.addWidget(&button, 0, Qt::AlignLeft);
    connect(&button, SIGNAL(clicked()), this, SLOT(showInformation()));
}

void InformationMessageUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	QFont font = painter.font();
    if (err) {
        button.setStyleSheet("Background-color: #ff0000");
    }
    else {
        if (afficher) {
            button.setStyleSheet("Background-color: #ffffff");
        }
        else {
            if(message.getString().length()>0)
                button.setStyleSheet("Background-color: #c7c7c7");
            else
                button.setStyleSheet("Background-color: #707070");
        }
    }
    if (message.getString().length() > 0 && afficher) {
        QFont font = painter.font();
        int leftMargin = 50;
        int availableWidth = width() - leftMargin;
        QFontMetricsF fontMetrics(font);
        QRectF textRect = fontMetrics.boundingRect(QRectF(0, 0, availableWidth, height()), Qt::AlignCenter, message.getString());

        qreal scaleFactorWidth = availableWidth / textRect.width();
        qreal scaleFactorHeight = height() / textRect.height();
        qreal scaleFactor = qMin(scaleFactorWidth, scaleFactorHeight);

        int newPointSize = static_cast<int>(font.pointSizeF() * scaleFactor);

        font.setPointSize(newPointSize);
        painter.setFont(font);
        painter.setPen(message.getColor());
        painter.fillRect(0, 0, leftMargin, height(), Qt::white);

        painter.drawText(leftMargin, 0, availableWidth, height(), Qt::AlignCenter, message.getString());
    }
}

void InformationMessageUI::showInformation() {
    if (message.getString().length() > 0) {
        afficher = !afficher;
    }
    else {
        this->err = true;
        startTimer(150);
    }
    this->update();
}

void InformationMessageUI::timerEvent(QTimerEvent* event) {
    static int nbErr = 0;
    if (nbErr == 5) {
        this->err = false;
        this->killTimer(event->timerId());
        nbErr = 0;
        update();
    }
    else {
        nbErr++;
        this->err = !err;
        this->update();
    }
}

void InformationMessageUI::setMessage(Message m){
    message = m;
    if (message.getString().length() == 0) {
        afficher = false;
    }
    update();
}