
#include "object.hpp"

using namespace sceneElements;

Object::Object(float			x,
			   float			y,
			   int				damage,
			   CollisionGroup	collision)
	: _direction(0),
	  _speed(0),
	  _damage(damage),
	  _collision(collision)
{
	setPos(x, y);
}

void Object::setDirection(float direction)
{
	_direction = direction;
}

void Object::setSpeed(float speed)
{
	_speed = speed;
}

unsigned int Object::damage() const
{
	return _damage;
}

Object::CollisionGroup Object::collision() const
{
	return _collision;
}

void Object::takeDamage(int)
{
}

void Object::collisionManager()
{
	Object *object;

	foreach (QGraphicsItem *item, collidingItems())
		// on essaye de caster le QGraphicsItem en Object
		if ((object = dynamic_cast<Object*>(item)))

			// on compare bit à bit les catégories de collision
			// si l'objet a un bit en commun, on prend des domages
			if ((_collision & object->collision()) &&
				(_collision != object->collision()))

				// on enlève les dommages correspondant et on détruit
				// et on en donne à l'objet
				takeDamage(object->damage());
}
