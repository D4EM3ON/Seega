/*
* Auteur : Justin Quiriono
* Date : 11/04/22
*/
#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(QString j1, QString j2)
	: menuAide(nullptr), menuAPropos(nullptr), menuReglements(nullptr), menuParametres(nullptr), menuJeu(nullptr), menuNouvellePartie(nullptr), menuQuit(nullptr), aPropos(nullptr), reglements(nullptr), parametres(nullptr), layout(nullptr)
{
	joueur1 = j1;
	joueur2 = j2;
	setWindowTitle("SEEGA - Fenêtre principale"); // titre de la fenetre
	menuAide = new QMenu; // déclarer tous les attributs
	menuJeu = new QMenu;
	menuAPropos = new QAction(QString::fromUtf8("À Propos"));
	menuReglements = new QAction(QString::fromUtf8("Règlements"));
	menuParametres = new QAction(QString::fromUtf8("Paramètres"));
	menuNouvellePartie = new QAction(QString::fromUtf8("Nouvelle Partie"));
	menuQuit = new QAction(QString::fromUtf8("Quitter"));
	layout = new QGridLayout;
	jeu = new FenetreJeu(joueur1, joueur2);

	menuJeu = menuBar()->addMenu("Jeu"); // faire le menu jeu
	menuAide = menuBar()->addMenu("Aide"); // faire le menu aide

	menuAide->addAction(menuReglements); // ajout actions menu aide
	menuAide->addAction(menuAPropos);

	menuJeu->addAction(menuNouvellePartie); // ajout actions menu jeu
	menuJeu->addAction(menuParametres);
	menuJeu->addAction(menuQuit);

	connect(menuQuit, &QAction::triggered, this, &std::exit); // fermer le tout
	connect(menuReglements, &QAction::triggered, this, &FenetrePrincipale::showReglements); // ouvrir fenetre de reglements
	connect(menuAPropos, &QAction::triggered, this, &FenetrePrincipale::showAPropos); // ouvrir fenetre à propos
	connect(menuParametres, &QAction::triggered, this, &FenetrePrincipale::recevoirMenuPara); // ouvrir fenetre parametres
	connect(menuNouvellePartie, &QAction::triggered, this, &FenetrePrincipale::showNouvelle);

	FenetrePrincipale::setCentralWidget(jeu);
}

void FenetrePrincipale::changeNomJ1(QString j1)
{
	jeu->changeNomJ1(j1);
}

void FenetrePrincipale::changeNomJ2(QString j2)
{
	jeu->changeNomJ2(j2);
}

void FenetrePrincipale::showReglements()
{
	if (reglements != nullptr) delete reglements; // si deja fenetre, l'enlever 
	reglements = new FenetreReglements; // faire une fenetre
	reglements->show(); // montrer la fenetre
}

void FenetrePrincipale::showAPropos()
{
	if (aPropos != nullptr) delete aPropos;
	aPropos = new FenetreAPropos;
	aPropos->show();
}

void FenetrePrincipale::recevoirMenuPara()
{
	if (parametres != nullptr) delete parametres; 
	parametres = new FenetreParametres(&joueur1, &joueur2); // faire fenetre avec noms joueurs
	connect(parametres, &FenetreParametres::signalFromPara, this, &FenetrePrincipale::recevoirFenetrePara); // recevoir de parametres noms joueurs, connecter
	parametres->show();
}

void FenetrePrincipale::showNouvelle()
{
	delete jeu;
	jeu = new FenetreJeu(joueur1, joueur2);
	FenetrePrincipale::setCentralWidget(jeu);
}

void FenetrePrincipale::recevoirFenetrePara(QString j1, QString j2)
{
	joueur1 = j1; // assigner le nom des joueurs
	joueur2 = j2;
	jeu->changeNomJ1(joueur1);
	jeu->changeNomJ2(joueur2);
}
