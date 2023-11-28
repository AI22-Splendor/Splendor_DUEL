#include "CompleteBoardUI.h"
#include <qgridlayout.h>
#include <qevent.h>

CompleteBoardUI::CompleteBoardUI(QWidget* parent, Board b):QWidget(parent), board(this), remplir(this) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(QSize(50*5, 50*6));
    QVBoxLayout* grid = new QVBoxLayout(this);
    setLayout(grid);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(0);

    board.setGemmes(b);
    //on y ajoute tous les composant
    grid->addWidget(&remplir);
    grid->addWidget(&board);

    grid->setStretch(1, 6);
    grid->setStretch(0, 1);
}

void CompleteBoardUI::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    remplir.resize(board.width(), remplir.height());
    resize(board.width(), board.height() + remplir.height());
}


CompleteBoardUI::~CompleteBoardUI(){ QWidget::~QWidget(); }