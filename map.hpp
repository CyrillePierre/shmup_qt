
#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <queue>
#include <stack>
#include <QGraphicsScene>

#include "objectFactory.hpp"

#define FACTORY_FILE "genFactory.txt"

/**
 * @class Map
 * Cette classe correspond au niveau dans lequel vont être chargé et créer
 * l'ensemble des objets.
 */
class Map : public QObject
{
	Q_OBJECT

	public :
		/// @brief Constructeur
		Map(const std::string &fileName, QGraphicsScene* scene);

		/// @brief Execution de l'étape suivante
		void advance();

		/// @brief Chargement du fichier contenant le niveau
		void loadFile();

	signals :
		/// @brief fin du level
		void mapFinished();

	private :
		struct Level;
		struct Coord;

		QGraphicsScene*		_scene;
		ObjectFactory		_objFactory;
		std::string			_fileName;
		std::queue<Level*>	_objects;
		bool				_finished;
};

/**
 * @struct Level
 * Cette structure appartient à la classe Map. Elle permet de coupler
 * un numéro d'étape à une liste d'identifiant.
 */
struct Map::Level
{
	unsigned int		step;
	std::stack<Coord*>	coord;
};

/**
 * @struct Coord
 * Cette structure contient l'identifiant et la position de l'objet
 * à creer.
 */
struct Map::Coord
{
	unsigned int	id;
	float			x;
	float			y;
};

#endif
