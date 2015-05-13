
#ifndef SHIP_HPP
#define SHIP_HPP

#include <list>
#include <string>

#include "object.hpp"

class Ball;

// Ensemble des éléments de la scene.
namespace sceneElements
{

	/**
	 * @class Ship
	 * Cette classe correspond aux vaisseaux
	 */
	class Ship : public Object
	{
		public :
			/// @brief Modification de la fréquence d'attaque
			void setAttackFreq(float value);

			/// @brief Retourne le niveau d'énergie
			unsigned int energy() const;

			/// @brief Execution du step suivant
			virtual void advance(int);

			/// @brief Diminue le niveau d'énergie du vaisseau
			virtual void takeDamage(int damage);

		protected :
			/// @brief Constructeur
			Ship(float			x, 
				 float			y, 
				 int			energyMax, 
				 CollisionGroup	colGrp);

			/// @brief Initialisation
			void init(float x, float y, int energyMax);

			/// @brief Création d'une boulette en fonction de la
			/// fréquence d'attaque
			virtual void attack() = 0;

			/// @brief déplacement du vaisseau
			virtual void move() = 0;

		protected :
			int				_energyMax;
			int				_energy;
			unsigned int	_attackFreq;
			unsigned int	_attackStep;
	};

};

#endif
