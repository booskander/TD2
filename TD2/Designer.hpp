#pragma once
#include <string>
#include "ListeJeux.hpp"
struct Designer
{
	std::string nom;
	unsigned int anneeNaissance;
	std::string pays;
	ListeJeux listeJeuxParticipes;
};