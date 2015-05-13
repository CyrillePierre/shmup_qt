
#include "ship.hpp"
#include "ball.hpp"
#include "simulateur.hpp"

using namespace sceneElements;

Ship::Ship(float			x,
		   float			y,
		   int				energyMax,
		   CollisionGroup	colGrp)
	: Object(x, y, 5, colGrp),
	  _energyMax(energyMax),
	  _energy(energyMax),
	  _attackFreq(0),
	  _attackStep(0)
{
}

void Ship::init(float x, float y, int energyMax)
{
	_energyMax	= energyMax;
	_energy		= energyMax;
	_attackFreq	= 0;

	setPos(x, y);
}

void Ship::setAttackFreq(float value)
{
	_attackFreq = value;
	_attackStep = value;
}

void Ship::advance(int)
{
	// Destruction du vaisseau si il n'a plus d'énergie.
	// La destruction est faite au début de l'étape suivante pour
	// permettre au gestionnaire d'éffectuer toute les collisions
	// avant de détruire l'objet.
	if (_energy <= 0) {
		remove();
		return;
	}

	// déplcament de l'objet
	move();

	if (x() < -SCENE_X_MAX || x() > SCENE_X_MAX ||
		y() < -SCENE_Y_MAX || y() > SCENE_Y_MAX)
		remove();

	// gestion des collisions
	collisionManager();

	// et on attaque
	attack();
}

unsigned int Ship::energy() const
{
	return _energy;
}

void Ship::takeDamage(int damage)
{
	_energy -= damage;
}
