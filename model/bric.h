
#ifndef BRIC_H
#define BRIC_H

#include "direction.h"
#include "position.h"
#include <vector>
#include <algorithm>

/*!
 * \brief Espace de nom de Guillaume Jouret & Guillaume Walravens.
 */
namespace GJ_GW{

/*!
 * \brief Classe représentant une brique de Tetris.
 *
 * La forme de la brique est représentée par un ensemble de \ref Position
 * et sa longueur est connue.
 */
class Bric{

    std::vector<Position> shape_;
    /*!< La forme de la brique.
     *
     * Représente l'ensemble des cases qui sont remplies par la brique.
     */

    unsigned side_;
    /*!< La taille de côté de la brique en nombre de cases. */

public:

    /*!
     * \brief Constructeur sans argument de \ref Bric.
     *
     * Il initialise la brique avec une \ref Position par défaut.
     */
    Bric();

    /*!
     * \brief Constructeur de \ref Bric.
     *
     * Construit une brique à partir des \ref Position couvertes par la brique
     * dans un repère carré, la longueur de la brique est la taille de côté
     * de ce repère.
     *
     * \param shape les \ref Position remplies
     */
    Bric(std::vector<Position> shape);

    /*!
     * \brief Accesseur en lecture de la forme de la brique.
     *
     * Cette méthode est nécessaire à la génération des \ref Bric
     * sur la grille.
     *
     * \return la forme de la brique
     */
    std::vector<Position> getShape() const;

    /*!
     * \brief Accesseur en lecture de la longueur de la brique.
     * \return la taille en nombre de \ref Position
     */
    unsigned getSide() const;

    unsigned getHigherY();

    /*!
     * \brief Méthode qui tourne la brique.
     *
     * Si l'on imagine la brique comme étant dans un carré de case :
     * tourne les positions des cases de ce carrée de 90°.
     */
    void rotate();

    /*!
     * \brief Méthode déplaçant la brique dans une direction.
     * \param dir la direction choisie
     */
    void move(Direction dir);

    /*!
     * \brief Méthode vérifiant qu'une \ref Position fait partie de la brique.
     *
     * \param pos la localisation de la \ref Position à vérifier
     * \return true si la brique occupe la position, false sinon
     */
    bool contains(Position &pos) const;

    /*!
     * \brief Méthode convertissant une \ref Bric en std::string.
     * \return une représentation d'une brique sous la forme d'une std::string
     */
    std::string to_string() const;

    //amis

    friend std::ostream & operator<<(std::ostream & out, const Bric & in);
};

//prototypes

/*!
 * \brief Opérateur d'injection d'une \ref Bric dans un flux en sortie.
 * \param out le flux en sortie
 * \param in la \ref Bric à injecter
 * \return le flux après l'injection
 */
std::ostream & operator<<(std::ostream & out, const Bric & in);

} // namespace GJ_GW

#endif // BRIC_H