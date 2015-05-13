
#ifndef LINEARACTION_HPP
#define LINEARACTION_HPP

#include "enemyShipAction.hpp"

// Ensemble des contrôleurs d'objets
namespace objectsControler
{

	/**
	 * @class LinearAction
	 * Cette classe correspond à une modification linéaire d'une
	 * caractéristique d'un vaisseau.
	 */
	class LinearAction : public EnemyShipAction
	{
		public :
			/// @brief Constructeur
			LinearAction(EnemyShip*	enemyShip,
						 ESFunction	function,
						 int		nbStep,
						 float		first,
						 float		last);

			/// @brief Destructeur
			~LinearAction();

			/// @brief Avancement du comportement
			void advance();

		private :
			float	_value;
			float	_increment;
	};

};

#endif
