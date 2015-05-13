
#ifndef CONSTANTACTION_HPP
#define CONSTANTACTION_HPP

#include "enemyShipAction.hpp"

// Ensemble des contrôleurs d'objets
namespace objectsControler
{

	/**
	 * @class ConstantAction
	 * Cette classe correspond à une modification constante d'une 
	 * caractéristique d'une vaisseau.
	 */
	class ConstantAction : public EnemyShipAction
	{
		public :
			/// @brief Constructeur
			ConstantAction(EnemyShip*	enemyShip,
						   ESFunction	function,
						   int			nbStep,
						   float		value);
			
			/// @brief Destructeur
			~ConstantAction();

			/// @brief Avancement du comportement
			void advance();

		private :
			float	_value;
	};

};

#endif
