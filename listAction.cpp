
#include "listAction.hpp"

using namespace objectsControler;

ListAction::ListAction()
	: EnemyShipAction(NULL, NULL, 0)
{
}

void ListAction::addAction(EnemyShipAction* esa)
{
	// on ajoute le nouveau contrôleur puis on connecte
	// son signal de fin au slot handlend()
	_actions.push_back(esa);
	connect(esa,	SIGNAL(onActionFinished()),
			this,	SLOT(handleEnd()));
}	


void ListAction::advance()
{
	// tant que la liste n'est pas vide, on éxécute 
	// le premier contrôleur de la liste
	if (!_actions.empty())
		_actions.front()->advance();

	// si c'est vide alors c'est la fin
	else if (_finished) {
		emit onActionFinished();
		_finished = true;
	}
}

void ListAction::handleEnd()
{
	delete _actions.front();
	_actions.pop_front();
}
