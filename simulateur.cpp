
#include "simulateur.hpp"
#include "map.hpp"
#include "object.hpp"
#include "pool.hpp"
#include "ball.hpp"
#include "enemyShip.hpp"


using namespace sceneElements;

Simulateur::Simulateur()
{}

void Simulateur::init(int argc, char **argv)
{
	_app	= new QApplication(argc, argv);
	_widget	= new QWidget();
	_grid	= new QGridLayout(_widget);
	_scene	= new QGraphicsScene;
	_view	= new QGraphicsView(_scene);
	_timer	= new QTimer();
	_pBar	= new QProgressBar();
	_text	= new QGraphicsSimpleTextItem();

	_grid->addWidget(_view, 0, 0);
	_grid->addWidget(_pBar, 1, 0);

	_scene->setSceneRect(-VIEW_X_MAX,		-VIEW_Y_MAX,
						 2 * VIEW_X_MAX,	2 * VIEW_Y_MAX);

	_view->setWindowTitle("Choute-zem-heupe");
	_view->setBackgroundBrush(Qt::black);

	_view->setFixedSize(2 * VIEW_X_MAX + 4, 2 * VIEW_Y_MAX + 4);
	_widget->setFixedSize(2 * VIEW_X_MAX + 25, 2 * VIEW_Y_MAX + 55);

	_widget->show();
	
	_map = new Map("genMap.txt", _scene);

	connect(_timer,	SIGNAL(timeout()),
			this,	SLOT(step()));
}

Simulateur::~Simulateur()
{
	delete _map;
	delete _text;
	delete _pBar;
	delete _view;
	delete _timer;
	delete _grid;
	delete _widget;
	delete _app;
}

int Simulateur::start()
{
	_map->loadFile();
	_timer->start(TMP_FRAME);
	return _app->exec();
}

void Simulateur::step()
{
	_map->advance();
	_scene->advance();
}

void Simulateur::stop()
{
	_timer->stop();
}

QGraphicsScene *Simulateur::scene()
{
	return _scene;
}

QProgressBar *Simulateur::lifeBar()
{
	return _pBar;
}

void Simulateur::levelCompleted()
{
	if (_text->text() != NULL) return;

	_text->setFont(QFont("Helvetica", 30));
	_text->setBrush(Qt::red);
	_text->setZValue(1);
	_text->setText("Level completed");
	_text->setPos(-145, -30);
	_scene->addItem(_text);
}

void Simulateur::gameOver()
{
	_text->setFont(QFont("Helvetica", 30));
	_text->setBrush(Qt::red);
	_text->setZValue(1);
	_text->setText("Game Over");
	_text->setPos(-105, -30);
	_scene->addItem(_text);
}
