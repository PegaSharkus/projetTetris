#include "view/mwtetris.h"
#include <QApplication>
#include <iostream>

using namespace GJ_GW;

int main(int argc, char *argv[]){
    try{
        QApplication a (argc, argv);
        //std::string name {"Joueur"};
        //MultiTetris game(name);
        MWTetris w;
        w.show();
        return a.exec();
    } catch(const std::invalid_argument & e){
        std::cerr << "Erreur au lancement : "
                  << e.what()
                  << std::endl;
        std::exit(1);
    }
}

/*
TODO principal
- pour réseau : QTCPSocket
- mettre QTimer et QElapsedTimer dans model (tetris est un qobject)
- choix QThread ou librairie Thread
- remplacer QGridLayout & QLabel par QPixmap & QPainter ou optimiser utilisation QLabel
- remplacer QTimer par librairie c++
*/
