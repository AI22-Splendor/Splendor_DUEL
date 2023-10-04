#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SplendorDuel.h"

class SplendorDuel : public QMainWindow
{
    Q_OBJECT

public:
    SplendorDuel(QWidget *parent = nullptr);
    ~SplendorDuel();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SplendorDuelClass ui;
};
