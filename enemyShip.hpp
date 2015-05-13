
#ifndef ENEMYSHIP_HPP
#define ENEMYSHIP_HPP

#include "ship.hpp"

namespace objectsControler
{
	class EnemyShipAction;
};

using objectsControler::EnemyShipAction;

// Ensemble des éléments de la scene.
namespace sceneElements
{

	/**
	 * @class EnemyShip
	 * Cette classe représente les vaisseaux enemis
	 */
	class EnemyShip : public Ship
	{
		public :
			/// @brief Constructeur
			EnemyShip(float x, float y, int energyMax);

			/// @brief Constructeur
			EnemyShip();

			/// @brief Initialisation
			void init(float x, float y, int energyMax);

			/// @brief Affectation des comportements pour les 
			/// caractéristiques vitesse, direction et fréquence d'attaque
			void setControlers(EnemyShipAction* speed,
							   EnemyShipAction* direction,
							   EnemyShipAction* attackFreq);

			/// @brief Redéfinition de la fonction qui permet de dessiner
			/// le vaisseau.
			virtual void paint(QPainter							*painter,
							   const QStyleOptionGraphicsItem	*option,
							   QWidget							*widget);

			/// @brief Redéfinition de la fonction boundingRect qui
			/// définit la zone de dessin.
			virtual QRectF boundingRect() const;

			/// @brief Destruction de l'objet
			virtual void remove();

		protected :
			/// @brief Redéfinition de la fonction attack()
			virtual void attack();

			/// @brief Déplacement de l'objet
			virtual void move();

		protected :
			EnemyShipAction*	_speedControler;
			EnemyShipAction*	_directionControler;
			EnemyShipAction*	_attackFreqControler;
	};

};

#endif
