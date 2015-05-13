
#include "linearAction.hpp"

using namespace objectsControler;

LinearAction::LinearAction(
		EnemyShip*	enemyShip,
		ESFunction	function,
		int			nbStep,
		float		first,
		float		last)
	: EnemyShipAction(enemyShip, function, nbStep),
	  _value(first)
{
	// La variable _increment contient la distance entre first et last
	// divisé par le nombre d'étape
	_increment = (last - first) / nbStep;
}

LinearAction::~LinearAction()
{
}

void LinearAction::advance()
{
	// tant qu'on est pas à la dernière étape
	if ( _nbStep < _nbStepMax) {
		_value += _increment;				// on augmente la valeur
		(_enemyShip->*_function)(_value);	// on appelle la fonction
		++_nbStep;							// on passe à l'étape suivante
	}

	// Si c'est la dernière étape, on envoie le signal correspondant.
	else if (!_finished) {
		emit onActionFinished();
		_finished = true;
	}
}
