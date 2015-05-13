
#ifndef BALL_HPP
#define BALL_HPP

#include "object.hpp"

class QGraphicsScene;

// Ensemble des éléments de la scene.
namespace sceneElements
{

	/**
	 * @class Ball
	 * Cette classe contient les informations non partagé des boulettes.
	 */
	class Ball : public Object
	{
		public :
			/// @brief Constructeur
			Ball(float				x,
				 float				y,
				 float				speed,
				 float				direction,
				 unsigned int		damage);

			/// @brief Constructeur
			Ball();

			/// @brief Initialisation
			void init(float				x, 
					  float				y, 
					  float				speed, 
					  float				direction,
					  CollisionGroup	collision,
					  unsigned int		damage);

			/// @brief redéfinition de la fonction advance de
			/// QGraphicsEllipseItem
			virtual void advance(int);

			/// @brief Définition du sprite de la boulette
			void paint(QPainter	*painter,
					   const QStyleOptionGraphicsItem*,
					   QWidget*);

			/// @brief Redéfinition de la méthode boudingRect
			QRectF boundingRect() const;

			/// @brief Destruction de l'objet
			virtual void remove();

			/// @brief Réception de dégats
			virtual void takeDamage(int damage);

		protected :
			float	_dx;
			float	_dy;
			bool	_remove;
	};

};

#endif
