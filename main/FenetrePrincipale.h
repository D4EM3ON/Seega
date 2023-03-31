/*
* Auteur : Justin Quiriono
* Date : 19/04/22
*/
#include <qmainwindow.h>
#include <qapplication.h>
#include <qmenu.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qgridlayout.h>

#include "FenetreReglements.h"
#include "FenetreAPropos.h"
#include "FenetreParametres.h"
#include "FenetreJeu.h"

#pragma once
class FenetrePrincipale : public QMainWindow
{
	Q_OBJECT
public:
	FenetrePrincipale(QString j1, QString j2);
	void changeNomJ1(QString j1);
	void changeNomJ2(QString j2);

public slots:
	void recevoirFenetrePara(QString j1, QString j2);

protected:
	QMenu* menuAide, *menuJeu;
	QAction* menuAPropos, * menuReglements, * menuParametres, *menuNouvellePartie, *menuQuit;
	QGridLayout* layout;
	void showReglements(), showNouvelle(), showAPropos(), recevoirMenuPara();
	FenetreAPropos* aPropos;
	FenetreReglements* reglements;
	FenetreParametres* parametres;
	FenetreJeu* jeu;
	QString joueur1, joueur2;
};

