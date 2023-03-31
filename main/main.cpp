/*
* Auteur : Justin Quirion
* Date : 11/04/22
*/

#include <iostream>
#include <qapplication.h>
#include "FenetreAccueil.h"
#include "FenetreAPropos.h"
#include "FenetreReglements.h"
#include "FenetrePrincipale.h"
#include "FenetreJeu.h"

using namespace::std;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	FenetreAccueil f;

	f.show();

	return app.exec();
}