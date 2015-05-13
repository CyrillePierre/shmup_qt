
#include "enemyShipAction.hpp"

using namespace objectsControler;

EnemyShipAction::EnemyShipAction(
			EnemyShip*	enemyShip,
			ESFunction	function,
			int			nbStep)
	: _enemyShip(enemyShip),
	  _function(function),
	  _nbStep(0),
	  _nbStepMax(nbStep),
	  _finished(false)
{}
