
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QGraphicsItem>
#include <iostream>

// Ensemble des éléments de la scene.
namespace sceneElements
{

	/**
	 * @class Object
	 * Cette classe correspond au objets mobiles du jeu
	 */
	class Object : public QGraphicsItem
	{
		public :
			// groupe de collision
			enum CollisionGroup
			{
				/* Les colonnes correspondent aux groupes dans lequel
				 * les objets sont en collision.
				 * Mais les objets d'un même type ne peuvent entrer 
				 * en collision.
				 *
				 * Par exemple :
				 * ALLY est dans deux groupes (colonne 1 et 0).
				 * Il est donc en collision avec :
				 *		- ENEMY
				 *		- ENEMYBALL
				 *		- NEUTRAL
				 *		- ALL
				 * car eux aussi font partit de ces groupes.
				 */
									//			7 6 5 4  3 2 1 0
									//			----------------
				SCENERY		= 0x00,	//			0 0 0 0  0 0 0 0
				ENEMYBALL	= 0x02,	//			0 0 0 0  0 0 1 0
				ALLY		= 0x03,	//			0 0 0 0  0 0 1 1
				ALLYBALL	= 0x04,	//			0 0 0 0  0 1 0 0
				ENEMY		= 0x05,	//			0 0 0 0  0 1 0 1
				NEUTRAL		= 0x07,	//			0 0 0 0  0 1 1 1
				ALL			= 0xff	//			1 1 1 1  1 1 1 1
			};

		public :
			/// @brief modification de la vitesse
			void setSpeed(float speed);

			/// @brief modification de la direction
			void setDirection(float direction);

			/// @brief Destruction de l'objet
			virtual void remove() = 0;

			/// @brief Retourne la quantité de dommage
			unsigned int damage() const;

			/// @brief Retourne le champ de collision
			CollisionGroup collision() const;

			/// @brief Reception de dégats
			virtual void takeDamage(int damage);

		protected :
			/// @brief Constructeur
			Object(float			x,
				   float			y,
				   int				damage		= 0,
				   CollisionGroup	collision	= SCENERY);
		
			/// @brief exécution du step suivant
			virtual void advance(int) = 0;

			/// @brief Gestion des collisions
			void collisionManager();

		protected :
			float			_direction;
			float			_speed;
			int				_damage;
			CollisionGroup	_collision;
	};

};

#endif
