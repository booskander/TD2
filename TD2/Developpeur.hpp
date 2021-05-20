#pragma once
#include <string>
struct Jeu;
struct Designer;
struct Developpeur
{
	std::string nom;
	unsigned int anneeFondation;
	unsigned int nEmployes;
	Designer* listeDesigners;
};
