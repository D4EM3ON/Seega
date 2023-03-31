/*
* Auteur : Justin Quiriono
* Date : 11/04/22
*/
#include "FenetreAPropos.h"

FenetreAPropos::FenetreAPropos()
	: nom(nullptr), version(nullptr), concepteur(nullptr), quit(nullptr), layout(nullptr)
{
	setWindowTitle("SEEGA - A Propos");

	layout = new QVBoxLayout; // déclaration et définition
	nom = new QLabel;
	version = new QLabel;
	concepteur = new QLabel;
	quit = new QPushButton("Fermer");
	connect(quit, &QPushButton::clicked, this, &FenetreAPropos::close); // fermer quand c'est poussé

	nom->setText("Nom du jeu : Seega");
	version->setText("Version : 0.1");
	concepteur->setText("Auteur : Justin Quirion");

	layout->addWidget(nom); // ajout des widgets au layoit
	layout->addWidget(version);
	layout->addWidget(concepteur);
	layout->addWidget(quit);
	setLayout(layout);
}