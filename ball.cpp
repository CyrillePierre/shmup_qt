
#include "pool.hpp"
#include <math.h>

#include "ball.hpp"
#include "simulateur.hpp"

using namespace sceneElements;

Ball::Ball(float			x, 
		   float			y, 
		   float			speed, 
		   float			direction,
		   unsigned int		damage)
	: Object(x, y, damage), _remove(false)
{
	_dx = speed * cos(direction);
	_dy = speed * sin(direction);

	// Les boulettes apparaisse en arrière plan 
	// (par rapport aux vaisseau)
	setZValue(-1);
}

Ball::Ball() : Object(0, 0)
{
	// Les boulettes apparaisse en arrière plan 
	// (par rapport aux vaisseau)
	setZValue(-1);
}

void Ball::init(float			x, 
				float			y, 
				float			speed, 
				float			direction,
				CollisionGroup	collision,
				unsigned int	damage)
{
	_dx = speed * cos(direction);
	_dy = speed * sin(direction);

	_collision	= collision;
	_damage		= damage;
	_remove		= false;

	setPos(x, y);
}


void Ball::paint(QPainter	*painter,
			     const QStyleOptionGraphicsItem*,
				 QWidget*)
{
	switch (_collision) {
		case Object::ALLYBALL	:	painter->setBrush(Qt::blue);	break;
		case Object::ENEMYBALL	:	painter->setBrush(Qt::red);		break;
		default :					painter->setBrush(Qt::green);	break;
	}

	painter->setPen(QPen(Qt::white, 3));
	painter->drawEllipse(-5, -5, 10, 10);
}

QRectF Ball::boundingRect() const
{
	return QRectF(-5, -5, 10, 10);
}

void Ball::remove()
{
	Pool<Ball>::get()->remove(this);
}

void Ball::advance(int)
{
	// destruction retardé de l'objet
	if (_remove) { remove(); return; }

	// déplacement de la boulette
	moveBy(_dx, _dy);

	// gestion des collisions
	collisionManager();

	if (x() < -SCENE_X_MAX || x() > SCENE_X_MAX ||
		y() < -SCENE_Y_MAX || y() > SCENE_Y_MAX)
		remove();
}

void Ball::takeDamage(int)
{
	_remove = true;
}
