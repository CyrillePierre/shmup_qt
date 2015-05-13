
#include <fstream>
#include <string>

#include "objectFactory.hpp"
#include "object.hpp"
#include "pool.hpp"
#include "enemyShip.hpp"
#include "constantAction.hpp"
#include "linearAction.hpp"
#include "listAction.hpp"

using namespace std;
using namespace sceneElements;
namespace oc = objectsControler;

ObjectFactory::ObjectFactory(const char *fileName, QGraphicsScene *scene)
	: _scene(scene)
{
	string tmpString;
	unsigned int id = 0;
	ifstream file(fileName, ios_base::in);

	// tant qu'on peut lire on le stocke dans un string
	while (file >> tmpString) {

		// si on arrive à une instruction "id"
		if (tmpString	== "id") {
			
			// on récupère le nouvel id pour ensuite créer un
			// nouveau stringstream
			file >> id;
			_defObjets[id] = new stringstream;
		}

		// sinon on ajoute les données dans le stringstream
		else *_defObjets[id] << tmpString << ' ';
	}

	file.close();
}

Object *ObjectFactory::create(unsigned int id, float x, float y)
{
	stringstream *tmpSS, tmpSSCopie;
	string tmpString;
	MapSS::iterator posId = _defObjets.find(id);

	// on vérifie que la clé existe
	if (posId == _defObjets.end()) return NULL;
	tmpSS = posId->second;

	// on travaille avec une copie de tmpSS
	// (histoire de pouvoir l'utiliser plusieurs fois)
	tmpSSCopie << tmpSS->str();
	
	tmpSSCopie >> tmpString;
	if (tmpString == "EnemyShip")
		return createEnemyShip(&tmpSSCopie, x, y);

	return NULL;
}

EnemyShip *ObjectFactory::createEnemyShip(
		stringstream*	ss,
		float			x,
		float			y)
{
	string				tmpString;
	float				tmpFloat;
	EnemyShip*			enemyShip;
	EnemyShipAction		*speed, *dir, *atk;

	*ss >> tmpFloat;
	// on crée un nouvel EnemyShip (à partir de la piscine)
	enemyShip = Pool<EnemyShip>::get()->create();
	enemyShip->init(x, y, tmpFloat);

	// création du contrôleur de vitesse
	*ss >> tmpString; // lecture de "speed"
	speed = createEnemyShipAction(ss, enemyShip, &EnemyShip::setSpeed);

	// création du contrôleur de direction
	*ss >> tmpString; // lecture de "direction"
	dir = createEnemyShipAction(ss, enemyShip, &EnemyShip::setDirection),
	
	// création du contrôleur de fréquence d'attaque
	*ss >> tmpString; // lecture de "attackFreq"
	atk = createEnemyShipAction(ss, enemyShip, &EnemyShip::setAttackFreq);

	enemyShip->setControlers(speed, dir, atk);

	return enemyShip;
}

oc::EnemyShipAction *ObjectFactory::createEnemyShipAction(
		stringstream*					ss,
		EnemyShip*						enemyShip,
		oc::EnemyShipAction::ESFunction	function)
{
	oc::EnemyShipAction *esa = NULL;
	unsigned int		tmpUInt;
	string				tmpString;
	float				tmpFloat, tmpFloat2;

	*ss >> tmpString;

	// ConstantAction
	if (tmpString == "constant") {
		*ss >> tmpUInt;		// durée du contrôleur (en étape)
		*ss >> tmpFloat;	// valeur constante à affecter
		esa = new oc::ConstantAction(
				enemyShip,
				function,
				tmpUInt,
				tmpFloat);
	}

	// LinearAction
	else if (tmpString == "linear") {
		*ss >> tmpUInt;		// durée du contrôleur (en étape)
		*ss >> tmpFloat;	// valeur de départ
		*ss >> tmpFloat2;	// valeur de fin
		esa = new oc::LinearAction(
				enemyShip,
				function,
				tmpUInt,
				tmpFloat,
				tmpFloat2);
	}

	// ListAction
	else if (tmpString == "list") {
		oc::ListAction *l = new oc::ListAction();

		// appel récursif de la fonction pour créer une liste
		// de contrôleur (tant que l'on a pas NULL)
		while ((esa = createEnemyShipAction(ss, enemyShip, function)))
			l->addAction(esa);

		return l;
	}

	// lecture d'un mauvais mot ("direction" ou "attackFreq")
	else ss->unget();

	return esa;
}
