#include "SplendorDuel.h"

SplendorDuel::SplendorDuel(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
}

SplendorDuel::~SplendorDuel()
{
    
}

bool SplendorDuel::close(){
    QMainWindow::close();
    return true;
}