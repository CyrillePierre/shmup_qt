
#ifndef SIMULATEUR_HPP
#define SIMULATEUR_HPP

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QProgressBar>
#include <QGridLayout>
#include <QGraphicsRectItem>

#include "singleton.hpp"

// Nombre de frames par seconde
#define NB_FRAMES	25

// temps d'une frame
#define TMP_FRAME	1000 / NB_FRAMES

#define SCENE_X_MAX 250
#define SCENE_Y_MAX 350
#define VIEW_X_MAX	200
#define VIEW_Y_MAX	300

class Map;

// Ensemble des éléments de la scene.
namespace sceneElements
{

	/**
	 * @class Simulateur
	 * Cette classe représente l'interface graphique du jeu
	 */
	class Simulateur : public QObject, public Singleton<Simulateur>
	{
		Q_OBJECT

		public :
			/// @brief Destructeur
			~Simulateur();

			/// @brief initialisation
			void init(int argc, char **argv);

			/// @brief Démarrage du jeu
			int start();

			/// @brief Arrêt du jeu
			void stop();

			/// @brief Retourne un pointeur sur la scene
			QGraphicsScene *scene();

			/// @brief Retourne la barre de vie
			QProgressBar *lifeBar();

		public slots :
			/// @brief Étape suivante :
			void step();

			/// @brief Fin du niveau
			void levelCompleted();

			/// @brief partie terminée
			void gameOver();

		private :
			/// @brief Constructeur
			Simulateur();

		private :
			QApplication*				_app;
			QWidget*					_widget;
			QGridLayout*				_grid;
			QGraphicsScene*				_scene;
			QGraphicsView*				_view;
			QGraphicsSimpleTextItem*	_text;
			QTimer*						_timer;
			QProgressBar*				_pBar;
			Map*						_map;

			friend class Singleton<Simulateur>;
	};

};

#endif
