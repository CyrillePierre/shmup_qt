
#ifndef OBJECTFACTORY_HPP
#define OBJECTFACTORY_HPP

#include <QGraphicsScene>
#include <map>
#include <sstream>

#include "enemyShipAction.hpp"

namespace sceneElements {
	class Object;
	class EnemyShip;
};

/**
 * @class ObjectFactory
 * Cette classe permet de créer des Objets
 */
class ObjectFactory
{
	public : // typedef
		typedef std::map<unsigned int, std::stringstream*> MapSS;

	public : // méthode publique
		/// @brief Constructeur
		ObjectFactory(const char *fileName, QGraphicsScene *scene);

		/// @brief Construction d'un objet à partir de son id
		sceneElements::Object *create(unsigned int	id,
									  float			x,
									  float			y);

	private : // méthode privée
		/// @brief creation d'un EnemyShip
		sceneElements::EnemyShip *createEnemyShip(
				std::stringstream *tmpSS, float x, float y);

		/// @brief creation d'un contrôleur de vaisseau enemi
		objectsControler::EnemyShipAction *createEnemyShipAction(
				std::stringstream *ss,
				sceneElements::EnemyShip* enemyShip,
				objectsControler::EnemyShipAction::ESFunction function);

	private : // attribut
		QGraphicsScene*	_scene;
		MapSS			_defObjets;
};

#endif
