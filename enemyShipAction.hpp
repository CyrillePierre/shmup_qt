
#ifndef ENEMYSHIPACTION_HPP
#define ENEMYSHIPACTION_HPP

#include <QObject>

namespace sceneElements
{
	class EnemyShip;
}

using sceneElements::EnemyShip;

// Ensemble des contrôleurs d'objets
namespace objectsControler
{
	// liste des contrôleurs
	enum
	{
		LINEAR,		///< classe : LinearAction
		CONSTANT	///< classe : ConstantAction
	};

	/**
	 * @class EnemyShipAction
	 * Cette classe correspond au comportement des vaisseaux enemis
	 */
	class EnemyShipAction : public QObject
	{
		Q_OBJECT

		public :
			// typedef pour simplifier l'écriture d'un pointeur de
			// fonction sur une fonction de EnemyShip
			typedef void (EnemyShip::*ESFunction)(float);

		public :
			/// @brief Constructeur
			EnemyShipAction(EnemyShip*	enemyShip,
							ESFunction	function,
							int			nbStep);

			/// @brief avancement de l'action
			virtual void advance() = 0;

		signals :
			/// @brief Signal de la fin du comportement
			void onActionFinished();

		protected :
			EnemyShip*		_enemyShip;
			ESFunction		_function;
			unsigned int	_nbStep;
			unsigned int	_nbStepMax;
			bool			_finished;
	};

};

#endif
