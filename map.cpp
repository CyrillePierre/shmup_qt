
#include <fstream>

#include "map.hpp"
#include "allyShip.hpp"
#include "simulateur.hpp"

using namespace std;
using namespace sceneElements;

namespace oc = objectsControler;

Map::Map(const string &fileName, QGraphicsScene* scene)
	: _scene(scene),
	  _objFactory(FACTORY_FILE, _scene),
	  _fileName(fileName),
	  _finished(false)
{
	// création d'un vaisseau allié
	AllyShip *allyShip = new AllyShip(0, 200, 50);
	allyShip->setAttackFreq(4);
	allyShip->setSpeed(4);
	_scene->addItem(allyShip);

	connect(this,				SIGNAL(mapFinished()),
			Simulateur::get(),	SLOT(levelCompleted()));
}

void Map::advance()
{
	static unsigned int step = 0;

	// on vérifie si la file n'est pas vide
	if (!_objects.empty()) {
		Level* level = _objects.front();

		// si l'étape actuel correspond à celle dans la file
		// on va pouvoir créer des objets
		if (level->step == step) {
			Coord* coord;

			// tant que la pile d'objet à créer n'est pas vide
			while (!level->coord.empty()) {
				coord = level->coord.top();

				// on crée l'objet à partir des infos contenus dans
				// la structure Coord
				_objFactory.create(coord->id, coord->x, coord->y);

				// on peut ensuite l'enlever de la pile
				level->coord.pop();
				delete coord;
			}

			// une fois que la pile est vide, on peut supprimer
			// cette étape
			_objects.pop();
			delete level;
		}
	}
	else if (!_finished) {
		emit mapFinished();
		_finished = true;
	}


	++step;
}

void Map::loadFile()
{
	Level*			level;
	unsigned int	tmpValue;
	string			tmpString;

	ifstream file(_fileName.c_str(), ios_base::in);

	// tant qu'on peut lire "step", on boucle
	while (file >> tmpString) {

		// lecture du numéro d'étape
		file >> tmpValue;			
		level = new Level;
		level->step = tmpValue;		

		// tant qu'on peut lire un identifiant, on boucle
		while (file >> tmpValue) {
			level->coord.push(new Coord);
			
			// l'identifiant et la position sont stocké dans la
			// structure Coord
			level->coord.top()->id = tmpValue;
			file >> level->coord.top()->x;
			file >> level->coord.top()->y;
		}

		// la lecture à échoué car le fichier contenais une chaine de
		// caractère, il faut donc remettre cette chaine dans le ficher
		file.unget();
		file.clear();

		// on fini par ajouter l'étape dans la file
		_objects.push(level);
	}

	file.close();
}
