
#ifndef POOL_HPP
#define POOL_HPP

#include <stack>

#include "singleton.hpp"

// nombre minimum d'objet par défaut
#define NB_OBJ_MINI 20

// nombre d'objet rajouté à chaque nouvel appel système
#define NB_OBJ_INCR 10

/**
 * @class Pool
 * Cette classe correspond à une bassine. Elle permet de créer
 * et détruire des boulettes en minimisant les appels système pour
 * alouer de la mémoire.
 */
template<typename Obj>
class Pool : public Singleton< Pool<Obj> >
{
	public :
		/// @brief Constructeur
		Pool(unsigned int	nbObjects	= NB_OBJ_MINI,
			 unsigned int	nbIncr		= NB_OBJ_INCR);

		/// @brief Destructeur
		~Pool();
		
		/// @brief Construction d'un objet
		Obj* create();

		/// @brief Destruction d'un objet
		void remove(Obj *object);

	private :
		/// @brief Agrandissement de la bassine avec "nb" objets
		void addObjects(unsigned int nb);
	
	private :
		std::stack<Obj*>	_objects;
		unsigned int		_nbIncr;
};

#include "pool.ipp"

#endif
