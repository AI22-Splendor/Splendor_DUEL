#include "SplendorDuel.h"
#include "Board.h"
#include "BoardUI.h"
#include "PersonnageBoardUI.h"
#include "GameHandler.h"
#include <qgridlayout.h>
#include <iostream>
#include "Image.h";
#include <qevent.h>
#include "PlayerGemsUI.h"
#include "BoardCard.h"
#include "BackgroundWidgetUI.h"
#include "NobleHandler.h"

using namespace std;
SplendorDuel* SplendorDuel::instance = nullptr;

SplendorDuel::SplendorDuel(Bag* bag, Board* b, DrawPile** drawPiles, Player* p1, Player* p2) :
    QMainWindow(nullptr)
{
    this->setWindowState(Qt::WindowMaximized);
    setWindowTitle("SplendorDuel");
    //on instance notre GameHandler
    SingletonGameHandler::getInstance().Instanciate(bag, b, drawPiles, p1, p2);

    //mise en page avec le widget main
    QWidget* main = new BackgroundWidgetUI(this, QPixmap("./res/playerFond.png"));
    QGridLayout* vl=new QGridLayout(main);
    main->setLayout(vl);

    this->ptab = new PlayersUI*[2]();
    ptab[0] = new PlayersUI(main, p1, 1);
    ptab[1] = new PlayersUI(main, p2, 2);
    QWidget* com = new BackgroundWidgetUI(main, Image::getFond());
    privilege = new PrivilegeBoardUI(com);

    this->board = new CompleteBoardUI(com, *b);
    QHBoxLayout* hbox = new QHBoxLayout();
    com->setLayout(hbox);
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);

    hbox->addWidget(new PersonnageBoardUI(com));
    hbox->addWidget(privilege, 0);
    hbox->addWidget(board);
    hbox->addWidget(new BoardCardUI(com));

    vl->addWidget(ptab[0],0, 0);
    vl->addWidget(com, 1, 0);
    vl->addWidget(ptab[1], 2, 0);

    vl->setColumnStretch(0, 1);
    vl->setRowStretch(1, 9);
    vl->setRowStretch(2, 3);
    vl->setRowStretch(0, 3);
    //on supprime les espace par défault
    vl->setSpacing(0);
    vl->setContentsMargins(0, 0, 0, 0);
    this->setCentralWidget(main);
}

SplendorDuel::~SplendorDuel()
{
    delete instance->board;
    delete[] instance->ptab;
    delete SplendorDuel::instance;
}

void SplendorDuel::addPlayerCard(Card* c, int ptrun) {
    if (ptrun< 0 || ptrun>1)
        return;
    instance->ptab[ptrun]->ajouterCarte(c);
    instance->ptab[ptrun]->addCouronne(c->getCrowns());
    instance->ptab[ptrun]->addPrestiges(c->getPointsPrestige());
    instance->ptab[ptrun]->setPoints(c->getDiscountType());
}

bool SplendorDuel::close(){
    instance->QMainWindow::close();
    SingletonGameHandler::destroy();
    SingletonNobleHandler::destroy();
    return true;
}

void SplendorDuel::keyPressEvent(QKeyEvent* e) { 
    if (e->key() == Qt::Key_N && e->type()==QEvent::KeyPress && e->isAutoRepeat()== false){
        instance->board->changeDirection();
    }
    if (e->key() == Qt::Key_L && e->type() == QEvent::KeyPress && e->isAutoRepeat() == false) {
        instance->board->changeNbGemmesTOSelect();
    }
};

void SplendorDuel::changePtour() {
    if (!SingletonGameHandler::getInstance().gameFinished()) {
        if (SingletonGameHandler::getInstance().isPlayer1Turn()) {
            instance->ptab[0]->changePtour(true);
            instance->ptab[1]->changePtour(false);
        }
        else {
            instance->ptab[0]->changePtour(false);
            instance->ptab[1]->changePtour(true);
        }
    }
    else {
        cout << "Winner is : " << SingletonGameHandler::getInstance().getWinner().getName() << endl;
        instance->close();
    }
}
