
#include <cmath>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QProgressBar>

#include "allyShip.hpp"
#include "ball.hpp"
#include "pool.hpp"

using namespace sceneElements;

AllyShip::AllyShip(float x, float y, int energyMax)
	: Ship(x, y, energyMax, Object::ALLY),
	  _dxP(0),
	  _dxN(0),
	  _dyP(0),
	  _dyN(0),
	  _move(false),
	  _attack(false)
{
	// on règle la QProgressBar qui correspond à la barre de vie
	// du vaisseau
	QProgressBar *lifeBar = Simulateur::get()->lifeBar();
	lifeBar->setRange(0, energyMax);
	lifeBar->setValue(energyMax);

	// Le vaisseau allié possède le focus
	setFlags(QGraphicsItem::ItemIsFocusable);
	setFocus();

	connect(this,		SIGNAL(energyChanged(int)),
			lifeBar,	SLOT(setValue(int)));	

	connect(this,				SIGNAL(destroyed()),
			Simulateur::get(),	SLOT(gameOver()));
}

void AllyShip::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem*,
					  QWidget*)
{
	// dessin d'un triangle jaune
	QPainterPath path;
	path.moveTo(-10, 15);
	path.lineTo(0, -15);
	path.lineTo(10, 15);
	path.lineTo(-10, 15);
	painter->setBrush(Qt::yellow);
	painter->drawPath(path);
	setFocus();
}

void AllyShip::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_Right :	_dxP = 1;		break;
		case Qt::Key_Left :		_dxN = -1;		break;
		case Qt::Key_Down :		_dyP = 1;		break;
		case Qt::Key_Up :		_dyN = -1;		break;
		case Qt::Key_Space :	_attack = true;	break;
	}

	calcDir();
}

void AllyShip::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_Right :	_dxP = 0;			break;
		case Qt::Key_Left :		_dxN = 0;			break;
		case Qt::Key_Down :		_dyP = 0;			break;
		case Qt::Key_Up :		_dyN = 0;			break;
		case Qt::Key_Space :	_attack = false;	break;
	}

	calcDir();
}

void AllyShip::calcDir()
{
	// le mouvement n'est activé que si l'une des touche est pressé
	if (!_dxP && !_dxN && !_dyP && !_dyN) _move = false;
	else _move = true;

	// on calcul la direction à partir  de l'arc tangente à deux
	// paramètre des coordonnées x et y
	_direction = atan2(_dyP + _dyN, _dxP + _dxN);

	// on oriente le vaisseau comme il faut ( * 360 / 2 PI )
	setRotation((_dxP + _dxN) * 14.32);
}

void AllyShip::move()
{
	if (_move)
		moveBy(_speed * cos(_direction),
			   _speed * sin(_direction));

	if (x() > VIEW_X_MAX)	setX(VIEW_X_MAX);
	if (x() < -VIEW_X_MAX)	setX(-VIEW_X_MAX);
	if (y() > VIEW_Y_MAX)	setY(VIEW_Y_MAX);
	if (y() < -VIEW_Y_MAX)	setY(-VIEW_Y_MAX);
}

QRectF AllyShip::boundingRect() const
{
	return QRectF(-10, -15, 20, 30);
}

void AllyShip::attack()
{
	if (!_attack) return;

	if (_attackStep == _attackFreq) {

		// création et initialisation d'une boulette à partir
		// de Pool<Ball>
		Ball *ab = Pool<Ball>::get()->create();
		ab->init(x(), y(), 6, -1.57 + (_dxP + _dxN) * 0.20,
				 Object::ALLYBALL, 3);

		_attackStep = 0;
	}
	else ++_attackStep;
}

QPainterPath AllyShip::shape() const
{
	QPainterPath path;
	path.addRect(-3, -3, 6, 6);
	return path;
}

void AllyShip::remove()
{
	scene()->removeItem(this);
	emit destroyed();
}

void AllyShip::takeDamage(int damage)
{
	_energy -= damage;
	emit energyChanged(_energy);
}
