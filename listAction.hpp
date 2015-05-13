
#ifndef LISTACTION_HPP
#define LISTACTION_HPP

#include "enemyShipAction.hpp"

namespace objectsControler
{

	/**
	 * @class ListAction
	 * Cette classe correspond à une d'objet de type EnemyShipAction.
	 */
	class ListAction : public EnemyShipAction
	{
		Q_OBJECT

		public :
			/// @brief Constructeur
			ListAction();

			/// @brief ajout d'un contrôleur
			void addAction(EnemyShipAction* esa);

			/// @brief Avancement du comportement
			void advance();

		public slots :
			/// @brief réception du signal de la fin d'une des actions
			/// de la liste
			void handleEnd();

		private :
			std::list<EnemyShipAction*>	_actions;
	};

};

#endif
