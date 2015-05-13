
#include "simulateur.hpp"

using sceneElements::Simulateur;

int main(int argc, char *argv[])
{
	Simulateur::get()->init(argc, argv);
	Simulateur::get()->start();
	delete Simulateur::get();
	return 0;
}
