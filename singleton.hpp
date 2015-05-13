
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/**
 * @class Singleton
 * Cette classe permet rajouter une méthode statique aux classe fille
 * pour contraindre la création d'instance à une seule.
 */
template<typename T>
class Singleton
{
	public :
		/// @brief création d'une unique instance
		static T *get()
		{
			static T *t = new T();
			return t;
		}
};

#endif
