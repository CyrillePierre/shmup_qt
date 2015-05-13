
#ifndef ALLYSHIP_HPP
#define ALLYSHIP_HPP

#include <QObject>

#include "ship.hpp"

// Ensemble des éléments de la scene.
namespace sceneElements
{

	/**
	 * @class AllyShip
	 * Cette classe représente le vaisseaux allié
	 * (le vaisseau qu'on pilote)
	 */
	class AllyShip : public QObject, public Ship
	{
		Q_OBJECT

		public :
			/// @brief Construteur
			AllyShip(float x, float y, int energyMax);

			/// @brief Redéfinition de la méthode paint
			void paint(QPainter *painter,
							   const QStyleOptionGraphicsItem*,
							   QWidget*);
			
			/// @brief Redéfinition de la méthode boudingRect
			QRectF boundingRect() const;

			/// @brief Redéfinition de la zone de collision
			QPainterPath shape() const;	

			/// @brief Destruction du vaisseau
			virtual void remove();

			/// @brief Diminue le niveau d'énergie du vaisseau
			virtual void takeDamage(int damage);

		protected :
			/// @brief Évenement du clavier (touche enfoncée)
			void keyPressEvent(QKeyEvent *event);

			/// @brief Évenement du clavier (touche relachée)
			void keyReleaseEvent(QKeyEvent *event);

			/// @brief Redéfinition de la fonction attack de Ship
			virtual void attack();

			/// @brief Déplacement de l'objet
			virtual void move();

		private :
			/// @brief Calcul de la direction
			void calcDir();

		signals :
			/// @brief le niveau d'énergie a changé
			void energyChanged(int);

			/// @brief mort du vaisseau
			void destroyed();

		protected :
			signed char _dxP;
			signed char _dxN;
			signed char _dyP;
			signed char _dyN;
			bool	_move;
			bool	_attack;
	};

};

#endif
