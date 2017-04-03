#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"
#include "bricsBag.h"
#include "observer/subject.h"

/*! \mainpage Le jeu de Tetris multijoueur, projet de c++ 2016-2017
 *
 * Projet réalisé dans le cadre du cours de c++ de l'ESI
 * par Guillaume Jouret et Guillaume Walravens.
 *
 * Un bon point d'entrée est celui de la documentation de
 * l'espace de nom \ref GJ_GW.
 */

/*!
 * \brief Espace de nom de Guillaume Jouret & Guillaume Walravens.
 */
namespace GJ_GW{

/*!
 * \brief Classe déterminant le fonctionnement d'une partie de Tetris.
 *
 * Elle fournit à la vue les données du modèle nécessaires à son bon fonctionnement
 * et implémente \ref Subject.
 */
class Tetris : public Subject{
public:
    constexpr static unsigned MINIMUM_TIMER {500};
    /*!< Valeur minimale acceptée pour le timer. */

    constexpr static unsigned MAXIMUM_TIMER {2000};
    /*!< Valeur maximale acceptée pour le timer. */

private:
    unsigned timer_;
    /*!< Le timer.
     *
     * Il représente le temps entre chaque mouvement automatique de la \ref Bric courante,
     * il se réduit en fonction du niveau de difficulté.
     *
     * Sa valeur est en milliseconde et peut aller de \ref MINIMUM_TIMER à \ref MAXIMUM_MONTH.
     */

    bool gameOver_;
    /*!< L'état de la partie.
     *
     * En cours ou arrêtée.
     */

    Player player_;
    /*!< Le joueur. */

    Board board_;
    /*!< La grille de jeu. */

    BricsBag bag_;
    /*!< Le sac de briques. */

    Bric currentBric_;
    /*!< La brique courante.
     *
     * Celle que contrôle le jeu.
     */

public:

    /*!
     * \brief Constructeur sans argument de \ref Tetris.
     *
     * Il initialise la partie avec les paramètres par défaut,
     * crée un \ref Player, un \ref Board et un \ref BricsBag par défaut.
     */
    Tetris();

    /*!
     * \brief Méthode permettant d'initialiser des briques personnalisées.
     * \param keepDefault indique si le joueur souhaite ajouter ses briques au
     * sac par défaut ou s'il souhaite créé un nouveau sac ne contenant que ses
     * briques personnelles.
     */
    void setBag(bool keepDefault);

    /*!
     * \brief Méthode permettant de lancer une partie de \ref Tetris.
     *
     * Elle ré-initialise la partie avec les paramètres donnés et lance le jeu.
     *
     * \param name le nom du joueur
     * \param width la largeur du \ref Board
     * \param height la hauteur du \ref Board
     * \param level le niveau de difficulté de départ
     */
    void startGame(std::string name, unsigned width, unsigned height, unsigned level = 0);

    /*!
     * \brief Accesseur en lecture du \ref Player.
     * \return le joueur
     */
    Player getPlayer() const;

    /*!
     * \brief Accesseur en lecture du \ref Board.
     *
     * \return la grille de jeu
     */
    Board getBoard() const;

    /*!
     * \brief Accesseur en lecture de la brique courante.
     *
     * \return la brique courante
     */
    Bric getCurrentBric() const;

    /*!
     * \brief Méthode vérifiant l'état de la partie.
     * \return true si la partie est terminée, false sinon
     */
    bool isGameOver() const;

    /*!
     * \brief Méthode permettant d'effectuer autant de déplacement
     * de la \ref Bric courante vers le bas que possible.
     */
    void drop();

    /*!
     * \brief Méthode vérifiant que le mouvement de la \ref Bric courante est valide.
     *
     * Elle crée un fantome de brique à la destination du mouvement et vérifie que le fantôme
     * se trouve dans une zone inoccupée de la grille de jeu.
     *
     * \param dir la direction vers laquelle la brique est déplacée
     * \param dropsCount le nombre de drop effectué, si la méthode a été appelée par un drop
     * \return true si le mouvement peut être effectué, false sinon
     */
    bool checkMove(Direction dir, unsigned dropsCount = 0);

    /*!
     * \brief Méthode vérifiant que la rotation de la \ref Bric courante est valide.
     *
     * Elle crée un fantome de brique à la destination du mouvement et vérifie que le fantôme
     * se trouve dans une zone inoccupée de la grille de jeu.
     */
    void checkRotate();

    /*!
     * \brief Méthode lançant une nouvelle itération du jeu.
     *
     * Une itération de \ref Tetris comprend un mouvement automatique
     * de la \ref Bric courante vers le bas ou la génération d'une
     * nouvelle brique courante si la précédente ne pouvait plus
     * descendre.
     */
    void next();

private:

    /*!
     * \brief Méthode permettant de changer le nom du \ref Player et de remttre à zéro
     * le compteur de lignes remplies (mais pas le score).
     * \param name le nom du joueur
     */
    void setPlayer(std::string name);

    /*!
     * \brief Accesseur en écriture du \ref Board.
     *
     * Il recrée une grille avec les nouveaux paramètres.
     *
     * \param width la largeur de la grille de jeu
     * \param height la hauteur de la grille de jeu
     */
    void setBoard(unsigned width, unsigned height);

    /*!
     * \brief Méthode de validation de la hauteur.
     *
     * Cette méthode vérifie que la valeur de l'attribut n'est pas égale à zéro.
     *
     * \param value la valeur à valider
     * \return la valeur validée
     */
    unsigned validateHeight(unsigned value);

    /*!
     * \brief Méthode de validation de la largeur.
     *
     * Cette méthode vérifie que la valeur de l'attribut n'est pas égale à zéro.
     *
     * \param value la valeur à valider
     * \return la valeur validée
     */
    unsigned validateWidth(unsigned value);

    /*!
     * \brief Méthode plaçant une nouvelle \ref Bric en haut du \ref Board.
     */
    void generateBric();

    /*!
     * \brief Méthode permettant une translation de la brique courante dans une direction donnée.
     *
     * \param direction la direction vers laquelle la brique est déplacée
     */
    void moveBric(Direction dir);

    /*!
     * \brief Méthode permettant de tourner la brique courante de 90°.
     */
    void rotateBric();

    /*!
     * \brief Méthode vérifiant que des lignes ont été remplies.
     *
     * Elle est lancée à chaque fois que la \ref Bric courrante
     * ne peut plus descendre.
     *
     * \param dropCount le nombre de cases traversées par un drop
     */
    void checkLines(unsigned top, unsigned dropsCount);

    /*!
     * \brief Méthode vérifiant qu'aucune condition de fin de partie n'a été remplie.
     *
     * Si un joueur perd ou gagne, elle arrête la partie et affiche le résultat.
     *  - Un joueur perd si la brique suivante ne peut être mise en jeu par manque de place ;
     *  - Un joueur gagne s'il atteint un score suffisant ;
     *  - Un joueur gagne s'il réussi à remplir suffisamment de lignes ;
     *  - la partie s'arrête après un certain temps, le joueur ayant alors le plus haut score l'emporte.
     */
    void endGame();

    /*!
     * \brief Méthode modifiant le temps entre chaque itération en fonction
     * du niveau de difficulté.
     *
     * \return le timer modifié
     */
    void setTimer();

    /*!
     * \brief Méthode modifiant le niveau de difficulté en fonction du nombre de lignes remplies par le joueur.
     */
    void setLevel();

};

} // namespace GJ_GW

#endif // GAME_H
