/*
* Auteur : Justin Quiriono
* Date : 11/04/22
*/

#include <qmenubar.h>
#include "FenetreAccueil.h"



FenetreAccueil::FenetreAccueil()
	: jouer(nullptr), param(nullptr), quit(nullptr), boutons(nullptr), layout(nullptr), layout2(nullptr), blanc(nullptr), noir(nullptr), blank(nullptr), menuAide(nullptr), menuAPropos(nullptr), menuReglements(nullptr), f_param(nullptr), principale(nullptr)
{
	setWindowTitle("SEEGA - Accueil");

	layout = new QGridLayout; // déclaration et définition
	layout2 = new QGridLayout;
	jouer = new QPushButton("Jouer");
	param = new QPushButton("Parametres");
	quit = new QPushButton("Quitter");
	boutons = new QHBoxLayout;
	blanc = new QLabel;
	noir = new QLabel;
	blank = new QLabel;
	menuAide = new QMenu;

	connect(quit, &QPushButton::clicked, this, &std::exit); // fermer l'application si poussé
	connect(param, &QPushButton::clicked, this, &FenetreAccueil::showFenetreParam); // montrer parametres si poussé
	connect(jouer, &QPushButton::clicked, this, &FenetreAccueil::showPrincipale);

	blanc->setPixmap(QPixmap("C:/Temp/ImageC07.png")); // set les images
	blank->setPixmap(QPixmap("C:/Temp/ImageC00.png"));
	noir->setPixmap(QPixmap("C:/Temp/ImageC08.png"));

	boutons->addWidget(jouer); // ajout des boutons au horizontal layout
	boutons->addWidget(param);
	boutons->addWidget(quit);

	for (int i = 0; i < 5; i++) { // pour les 5x5 cases, modifier l'image pour qu'elle soit vide
		for (int j = 0; j < 5; j++) {
			images[i][j] = new QLabel;
			images[i][j]->setPixmap(QPixmap("C:/Temp/ImageC00.png")); // les sauvegarder dans un array for future use
			layout2->addWidget(images[i][j], j, i);
		}
	}

	layout->addLayout(layout2, 0, 0);
	layout->addLayout(boutons, 1, 0);

	setLayout(layout);
}

void FenetreAccueil::showFenetreParam(void) // montrer la fenetre des parametres
{
	if (f_param != nullptr) delete f_param;
	f_param = new FenetreParametres(&joueur1, &joueur2);
	connect(f_param, &FenetreParametres::signalFromPara, this, &FenetreAccueil::recevoirFenetrePara); // recevoir de parametres noms joueurs, connecter
	f_param->show();
}

void FenetreAccueil::showPrincipale(void)
{
	if (principale != nullptr) delete principale;
	principale = new FenetrePrincipale(joueur1, joueur2);
	this->close();
	principale->show();
}

void FenetreAccueil::recevoirFenetrePara(QString j1, QString j2)
{
	joueur1 = j1; // assigner le nom des joueurs
	joueur2 = j2;
	//principale->changeNomJ1(joueur1);
	//principale->changeNomJ2(joueur2);
}
