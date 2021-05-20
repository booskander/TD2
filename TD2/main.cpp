#include "bibliotheque_cours/bibliotheque_cours.hpp"
#include "bibliotheque_cours/debogage_memoire.hpp"
#include "bibliotheque_cours/verification_allocation.hpp"
#include "fonctions.hpp"
int main(int argc, char** args)
{
	#pragma region "Bibliothèque du cours"
	#ifdef VERIFICATION_ALLOCATION_INCLUS
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	#endif
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion

	//int* fuite = new int;
	std::locale::global(std::locale{""}); // Pour afficher les accents
	//TODO: Appel à votre fonction de création de la liste de jeux
	// N'oubliez pas que le fichier se nomme jeux.bin
	static const std::string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	std::cout << ligneSeparation << std::endl;
	std::cout << "Premier jeu de la liste :" << std::endl;
	//TODO: Appel à votre fonction d'affichage de votre liste de jeux
	//TODO: Appel à votre fonction de destruction de la liste de jeux

	
	return 0;
}