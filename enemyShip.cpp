
#include <math.h>
#include <QPainter>
#include <QGraphicsScene>

#include "enemyShip.hpp"
#include "enemyShipAction.hpp"
#include "ball.hpp"
#include "pool.hpp"

using namespace::sceneElements;

EnemyShip::EnemyShip(float x, float y, int energyMax)
	: Ship(x, y, energyMax, Object::ENEMY)
{
}

EnemyShip::EnemyShip()
	: Ship(0, 0, 0, Object::ENEMY)
{
}

void EnemyShip::init(float x, float y, int energyMax)
{
	Ship::init(x, y, energyMax);
}

void EnemyShip::move()
{
	// on appelle chacun des contrôleurs qui vont s'occuper de
	// modifier les caractéristiques du vaisseau
	if (_speedControler)		_speedControler->advance();
	if (_directionControler)	_directionControler->advance();
	if (_attackFreqControler)	_attackFreqControler->advance();

	setRotation(_direction * 57.29577951 - 90);

	// on déplace le vaisseau
	moveBy(_speed * cos(_direction), _speed * sin(_direction));
}

void EnemyShip::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem*,
					  QWidget*)
{
	// dessin d'un triangle jaune
	QPainterPath path;
	path.moveTo(-10, -15);
	path.lineTo(0, 15);
	path.lineTo(10, -15);
	path.lineTo(-10, -15);
	painter->setBrush(Qt::red);
	painter->drawPath(path);
}
		
QRectF EnemyShip::boundingRect() const
{
	return QRectF(-10, -15, 20, 30);
}

void EnemyShip::setControlers(
		EnemyShipAction* speed,
		EnemyShipAction* direction,
		EnemyShipAction* attackFreq)
{
	_speedControler		 = speed;
	_directionControler	 = direction;
	_attackFreqControler = attackFreq;
}

void EnemyShip::attack()
{
	if (!_attackFreq) return;

	if (_attackStep == _attackFreq) {
		Ball *ball = Pool<Ball>::get()->create();
		ball->init(x(), y(), 3, _direction, Object::ENEMYBALL, 5);

		_attackStep = 0;
	}
	else ++_attackStep;
}

void EnemyShip::remove()
{
	delete _speedControler;
	delete _directionControler;
	delete _attackFreqControler;
	Pool<EnemyShip>::get()->remove(this);
}
