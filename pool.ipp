
#include <new>
#include <iostream>

#include "simulateur.hpp"

template<typename Obj>
Pool<Obj>::Pool(unsigned int	nbObjects,
				unsigned int	nbIncr)
	: _nbIncr(nbIncr)
{
	addObjects(nbObjects);
}

template<typename Obj>
Pool<Obj>::~Pool()
{
	// Tant que la pile n'est pas vide,
	// on supprime ses éléments
	while (!_objects.empty()) {
		delete _objects.top();
		_objects.pop();
	}
}

template<typename Obj>
Obj *Pool<Obj>::create()
{
	// on vérifie que la pile n'est pas vide.
	// Si elle l'est, on rajoute des objets
	if (_objects.empty()) {
		try { addObjects(_nbIncr); }
		catch (...) { throw; }
	}

	Obj *obj = _objects.top();
	_objects.pop();

	// ajout de l'objet dans la scene
	sceneElements::Simulateur::get()->scene()->addItem(obj);
	return obj;
}

template<typename Obj>
void Pool<Obj>::remove(Obj *object)
{
	// suppression de l'objet de la scene
	sceneElements::Simulateur::get()->scene()->removeItem(object);
	_objects.push(object);
}


template<typename Obj>
void Pool<Obj>::addObjects(unsigned int nb)
{
	Obj *obj;

	// on alloue la mémoire pour "nb" Objets
	try { obj = new Obj[nb]; }
	catch (std::bad_alloc &ba) {
		std::cerr << ba.what() << std::endl;
		throw;
	}

	// puis on les ajoute dans la pile
	for (unsigned int i = 0; i < nb; ++i)
		_objects.push(obj++);
}
