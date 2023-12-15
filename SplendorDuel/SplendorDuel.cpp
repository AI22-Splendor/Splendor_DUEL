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

#include "BackgroundWidgetUI.h"
<<<<<<< Updated upstream
=======
#include "NobleHandler.h"
#include <iostream>
>>>>>>> Stashed changes

using namespace std;
SplendorDuel* SplendorDuel::instance = nullptr;

SplendorDuel::SplendorDuel(Bag& bag, Board& b, DrawPile** drawPiles, Player* p1, Player* p2) :
    QMainWindow(nullptr)
{
    this->setWindowState(Qt::WindowMaximized);
    setWindowTitle("SplendorDuel");
    //on instance notre GameHandler
    GameHandler::getInstance().Instanciate(bag, b, drawPiles, p1, p2);

    //mise en page avec le widget main
    QWidget* main = new BackgroundWidgetUI(this, QPixmap("./res/playerFond.png"));
    QGridLayout* vl=new QGridLayout(main);
    main->setLayout(vl);

    this->ptab = new PlayersUI*[2]();
    ptab[0] = new PlayersUI(main, p1, 1);
    ptab[1] = new PlayersUI(main, p2, 2);
    QWidget* com = new BackgroundWidgetUI(main, Image::getFond());
    privilege = new PrivilegeBoardUI(com);

    this->board = new CompleteBoardUI(com, b);
    QHBoxLayout* hbox = new QHBoxLayout();
    com->setLayout(hbox);
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);
<<<<<<< Updated upstream
=======
    
    
    
    this->boardcards = new BoardCardUI(com);
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
>>>>>>> Stashed changes

    hbox->addWidget(new PersonnageBoardUI(com));
    hbox->addWidget(privilege, 0);
    hbox->addWidget(board);
    hbox->addWidget(boardcards);

    vl->addWidget(ptab[0],0, 0);
    vl->addWidget(com, 1, 0);
    vl->addWidget(ptab[1], 2, 0);

    vl->setColumnStretch(0, 1);
    vl->setRowStretch(1, 9);
    vl->setRowStretch(2, 3);
    vl->setRowStretch(0, 3);
    //on supprime les espace par d�fault
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
    if (!GameHandler::getInstance().gameFinished()) {
        if (GameHandler::getInstance().isPlayer1Turn()) {
            instance->ptab[0]->changePtour(true);
            instance->ptab[1]->changePtour(false);
        }
        else {
            if (!SingletonGameHandler::getInstance().isPlayer2AI()){
                instance->ptab[0]->changePtour(false);
                instance->ptab[1]->changePtour(true);
            }else{
                instance->ptab[0]->changePtour(false);
                instance->ptab[1]->changePtour(true);
                SingletonGameHandler::getInstance().getAI()->play();
            }
        }
    }
    else {
        cout << "Winner is : " << GameHandler::getInstance().getWinner().getName() << endl;
        instance->close();
    }
}
