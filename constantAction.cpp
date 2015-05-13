
#include "constantAction.hpp"

using namespace objectsControler;

ConstantAction::ConstantAction(
		EnemyShip*	enemyShip,
		ESFunction	function,
		int			nbStep,
		float		value)
	: EnemyShipAction(enemyShip, function, nbStep),
	  _value(value)
{
}

ConstantAction::~ConstantAction()
{
}	

void ConstantAction::advance()
{
	// On appelle la fonction qu'à la première étape
	if (_nbStep == 0) (_enemyShip->*_function)(_value);

	// Puis on incrémente le nombre d'étape
	if (_nbStep < _nbStepMax) ++_nbStep;

	// À la dernière étape, on envoie le signal de fin.
	else if (!_finished) {
		emit onActionFinished();
		_finished = true;
	}
}
