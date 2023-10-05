#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SplendorDuel.h"
#include <iostream>

class SplendorDuel : public QMainWindow
{
    Q_OBJECT

public:
    SplendorDuel(QWidget *parent = nullptr);
    ~SplendorDuel();


    bool close();

private:
    Ui::SplendorDuelClass ui;
};
