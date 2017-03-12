#include "mwtetris.h"
#include "ui_mwtetris.h"
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>

MWTetris::MWTetris(GJ_GW::Game * game, QWidget *parent) : QMainWindow(parent), game_{game}, ui(new Ui::MWTetris)
{
    ui->setupUi(this);
    connexion();

    setName();
    generateBoard();
}

MWTetris::~MWTetris(){
    delete ui;
}

void MWTetris::connexion(){
    connect(ui->action_Quitter, &QAction::triggered, &QCoreApplication::quit);
    connect(ui->action_Nouveau, &QAction::triggered, this, &MWTetris::createGame);
    connect(ui->action_Fermer, &QAction::triggered, this, &MWTetris::closeGame);
    // TODO : aide? cf qtpendu.pdf
}

void MWTetris::createGame(){
    ConfigDialog cd {this};
    auto ret = cd.exec();
    if(ret == QDialog::Rejected) return;

    std::string name {cd.getName()};
    unsigned width {cd.getWidth()};
    unsigned height {cd.getHeight()};
    if(! name.empty() || width != 0 || height != 0){
        GJ_GW::Game *game = new GJ_GW::Game(name, width, height);
        delete game_;
        game_ = game;
        setName();
        generateBoard();
    }
}

void MWTetris::closeGame(){
    delete game_;
    game_ = nullptr;
}

void MWTetris::setName(){
    ui->lbPlayerName->setText(QString::fromStdString(game_->getPlayer().getName()));
}

void MWTetris::generateBoard(){
    QWidget *window = new QWidget();
    QGridLayout *layout = new QGridLayout();

    QLabel * lb1 = new QLabel;
    lb1->setStyleSheet("QLabel {background-color : red}");
    layout->addWidget(lb1,0,0,1,1);
    layout->addWidget(new QLabel,0,1,1,1);
    layout->addWidget(new QLabel,1,1,1,1);
    layout->addWidget(new QLabel,1,0,1,1);

    window->setLayout(layout);
}

void MWTetris::turn(){
    game_->getPlayer().rotateBric();
}

void MWTetris::down(){
    game_->getPlayer().moveBric();
}

void MWTetris::drop(){
    game_->getPlayer().moveBric(1);
}

void MWTetris::left(){
    game_->getPlayer().moveBric(2);
}

void MWTetris::right(){
    game_->getPlayer().moveBric(3);
}
