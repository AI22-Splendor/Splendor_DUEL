#include "SplendorDuel.h"
#include "Board.h"
#include "BoardUI.h"
#include "PersonnageBoardUI.h"
#include "GameHandler.h"
#include <qgridlayout.h>
#include <iostream>
#include <qpalette.h>
#include "Message.h"
#include "Image.h";
#include <qevent.h>
#include "PlayerGemsUI.h"
#include "BoardCard.h"
#include "FinPartie.h"
#include "BackgroundWidgetUI.h"
#include "NobleHandler.h"
#include "XmlWriter.h"

using namespace std;
SplendorDuel* SplendorDuel::instance = nullptr;

SplendorDuel::SplendorDuel(Bag* bag, Board* b, DrawPile** drawPiles, Player* p1, Player* p2, bool autoDiplayCards) :
    QMainWindow(nullptr)
{
    this->setWindowState(Qt::WindowMaximized);
    setWindowTitle("SplendorDuel");
    //on instance notre GameHandler
    SingletonGameHandler::getInstance().Instanciate(bag, b, drawPiles, p1, p2, autoDiplayCards);

    //mise en page avec le widget main
    QWidget* main = new BackgroundWidgetUI(this, QPixmap("./res/playerFond.png"));
    QGridLayout* vl=new QGridLayout(main);
    main->setLayout(vl);

    this->ptab = new PlayersUI*[2]();
    ptab[0] = new PlayersUI(main, *p1, 1);
    ptab[1] = new PlayersUI(main, *p2, 2);
    QWidget* com = new BackgroundWidgetUI(main, Image::getFond());
    privilege = new PrivilegeBoardUI(com);

    this->board = new CompleteBoardUI(com, *b);
    QHBoxLayout* hbox = new QHBoxLayout();
    com->setLayout(hbox);
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);
    
    QWidget* leftBoard = new QWidget(com);
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    leftBoard->setLayout(vbox);
    message = new InformationMessageUI(leftBoard);
    vbox->addWidget(message);
    vbox->addWidget(new PersonnageBoardUI(leftBoard));
    vbox->setStretch(0, 1);
    vbox->setStretch(1, 8);

    hbox->addWidget(leftBoard);
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
    delete message;
}

void SplendorDuel::addPlayerCard(Card* c, int ptrun) {
    if (ptrun< 0 || ptrun>1)
        return;
    instance->ptab[ptrun]->ajouterCarte(c);
    instance->ptab[ptrun]->addCouronne(c->getCrowns());
    instance->ptab[ptrun]->addPrestiges(c->getPointsPrestige());
    instance->ptab[ptrun]->setPoints(c->getDiscountType());
}

void SplendorDuel::addPlayerPrestige(int nbPoints, int pturn) {
    if (pturn < 0 || pturn>1)
        return;
    instance->ptab[pturn]->addPrestiges(nbPoints);
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
        FinPartie* fin = new FinPartie();
        fin->show();
        if (fin->exec() == FinPartie::Accepted) {
            //TODO REPLAY
            instance->close();
        }else {
            instance->close();
        }
    }
}


void SplendorDuel::refreshMessage() {
    instance->message->setMessage(SingletonGameHandler::getInstance().getActionMessage());
}

void SplendorDuel::closeEvent(QCloseEvent* event) {
    string savefilename = "./res/savefile.xml";
    if (!SingletonGameHandler::getInstance().gameFinished()) {
        XmlWriter::createSaveFile(savefilename);
    }
    else {
        remove(savefilename.c_str());
    }
}