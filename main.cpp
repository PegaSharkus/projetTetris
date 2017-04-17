#include "view/mwtetris.h"
#include <QApplication>
#include <iostream>

using namespace GJ_GW;

int main(int argc, char *argv[]){
    try{
        QApplication a(argc, argv);
        std::string name {"Joueur"};
        Tetris game(name);
        //MWTetris * w = new MWTetris(game);
        MWTetris w(game);
        w.show();
        return a.exec();
    } catch(const std::invalid_argument & e){
        std::cerr << "Erreur au lancement : "
                  << e.what()
                  << std::endl;
        std::exit(1);
    }
}

/* TODO Principal :
 * annuler dernier mouvement dans création de brique
 * sauvegarde données hors partie, fichier de save (joueur, brique perso, score...)
 */
