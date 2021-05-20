#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma region "Les "includes" vont ici"
#include <iostream>
#include "cppitertools/range.hpp"
#include "Jeu.hpp"
#pragma endregion
#pragma region "Fonctions de base pour vous aider"
#include <fstream>
#include "gsl/span"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(std::istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(std::istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
std::string lireString(std::istream& fichier)
{
	std::string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], std::streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
gsl::span<Jeu*> spanListeJeux(const ListeJeux& lj)
{
	return gsl::span(lj.elements, lj.nElements);
}
gsl::span<Designer*> spanListeDesigners(const ListeDesigners& ld)
{
	return gsl::span(ld.elements, ld.nElements);
}
#pragma endregion


//TODO: Fonction qui cherche un designer par son nom dans une ListeJeux
// Cette fonction renvoie le pointeur vers le designer si elle le trouve dans
// un des jeux de la ListeJeux. En cas contraire, elle renvoie un pointeur nul.

Designer* findDesigner(const ListeJeux& lj, Designer d)
{
	for (int i = 0; i < lj.nElements; i++)
	{
		for (int j = 0; j < lj.elements[i]->designers.nElements; j++) {

			if (lj.elements[i]->designers.elements[j]->nom == d.nom)
			{
				return &d;
			}
			else
			{
				return nullptr;
			}
		}
	}
}



Designer* lireDesigner(std::istream& f, const ListeJeux& lj)
{
	Designer d = {}; // On initialise une structure vide de type Designer
	d.nom = lireString(f);
	d.anneeNaissance = lireUint16(f);
	d.pays = lireString(f);
	// Rendu ici, les champs précédents de la structure designer sont remplis
	// avec la bonne information

	//TODO: Ajouter en mémoire le designer lu. Il faut revoyer le pointeur créé
	// Attention, valider si le designer existe déjà avant de le créer, sinon
	// on va avoir des doublons car plusieurs jeux ont des designers en commun
	// dans le fichier binaire. Afficher un message lorsque l'allocation du
	// designer est réussie

	Designer* temp = findDesigner(lj, d);
	if (temp == nullptr)
	{
		return new Designer(d);
		
	}
	else
	{
		return temp;
	}
	
}

//TODO: Fonction qui double le tableau de jeux de ListeJeux
// Cette fonction doit recevoir en paramètre la nouvelle capacité du nouveau
// tableau. Il faut allouer un nouveau tableau plus grand, copier ce qu'il y
// avait dans l'ancien, et éliminer l'ancien trop petit. N'oubliez pas, on copie
// des pointeurs de jeux. Il n'y a donc aucune nouvelle allocation ici !

ListeJeux doublerCapaciteTableau(ListeJeux& lj, unsigned int capacite)
{
	
	ListeJeux* dbl = new ListeJeux[lj.capacite * 2];

	for (int i = 0; i < lj.nElements; i++) 
	{
		dbl->elements[i] = lj.elements[i];
	}
	delete[] lj.elements;

	lj.elements = dbl->elements;

	return lj;
	
}




//TODO: Fonction pour ajouter un Jeu à ListeJeux
// Le jeu existant déjà en mémoire, on veut uniquement ajouter le pointeur vers
// le jeu existant. De plus, en cas de saturation du tableau elements, cette
// fonction doit doubler la taille du tableau elements de ListeJeux et détruire
// l'ancien. Utilisez la fonction de doublement écrite plus haut.

// trouver les sous problemes dans un probleme plus gros (logique de prog)
void ajouterJeu(ListeJeux& lj, Jeu* j)
{
	if(lj.nElements != lj.capacite)
		lj.elements[lj.nElements] = j;

	else 
	{
		doublerCapaciteTableau(lj, lj.capacite);
		lj.elements[lj.nElements] = j;
	}
}


Jeu* lireJeu(std::istream& f, ListeJeux& lj)
{
	Jeu j = {}; // On initialise une structure vide de type Jeu
	j.titre = lireString(f);
	j.anneeSortie = lireUint16(f);
	j.developpeur = lireString(f);
	j.designers.nElements = lireUint8(f);
	// Rendu ici, les champs précédents de la structure jeu sont remplis avec la
	// bonne information

	//TODO: Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé
	// Attention, il faut aussi créer un tableau dynamique pour les designers
	// que contient un jeu. Servez-vous de votre fonction d'ajout de jeu car la
	// liste de jeux participé est une ListeJeu. Afficher un message lorsque
	// l'allocation du jeu est réussie
}

ListeJeux creerListeJeux(const std::string nomFichier)
{
	std::ifstream f(nomFichier, std::ios::binary);
	f.exceptions(std::ios::failbit);
	int nElements = lireUint16(f);
	ListeJeux lj = {};
	for(int n : iter::range(nElements))
	{
		lj.nElements = n;
		//TODO: Ajouter un jeu à ListeJeux
		
	}
	lj.nElements = nElements;
	//TODO: Renvoyez la ListeJeux
}

//TODO: Fonction qui détermine si un designer participe encore à un jeu

//TODO: Fonction pour détruire un designer (libération de mémoire allouée)
// Lorsqu'on détruit un designer, on affiche son nom pour fins de débogage

//TODO: Fonction qui enlève un jeu de ListeJeux
// Attention, ici il n'a pas de désallocation de mémoire. Elle enlève le
// pointeur de la ListeJeux, mais le jeu pointé existe encore en mémoire.
// Puisque l'ordre de la ListeJeux n'a pas être conservé, on peut remplacer le
// jeu à être retiré par celui présent en fin de liste et décrémenter la taille
// de celle-ci

//TODO: Fonction pour détruire un jeu (libération de mémoire allouée)
// Attention, ici il faut relâcher toute les cases mémoires occupées par un jeu.
// Par conséquent, il va falloir gérer le cas des designers (un jeu contenant
// une ListeDesigners). On doit commencer par enlever le jeu à détruire des jeux
// qu'un designer a participé (listeJeuxParticipes). Si le designer n'a plus de
// jeux présents dans sa liste de jeux participés, il faut le supprimer.  Pour
// fins de débogage, affichez le nom du jeu lors de sa destruction.

//TODO: Fonction pour détruire une ListeJeux et tous ses jeux

void afficherDesigner(const Designer& d)
{
	std::cout << "\t" << d.nom << ", " << d.anneeNaissance << ", " << d.pays
			  << std::endl;
}
//TODO: Fonction pour afficher les infos d'un jeu ainsi que ses designers
// Servez-vous de la fonction afficherDesigner ci-dessus

//TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne
// Servez-vous de la fonction d'affichage d'un jeu crée ci-dessus. Votre ligne
// de séparation doit être différent de celle utilisée dans le main

