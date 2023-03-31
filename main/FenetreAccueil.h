/*
* Auteur : Justin Quiriono
* Date : 11/04/22
*/

#include <QApplication>
#include <qmainwindow.h>
#include <QWidget>
#include <qpushbutton.h>
#include <qlabel.h>
#include <vector>
#include <qgridlayout.h>
#include <qboxlayout.h>
#include <qmenu.h>
#include <qaction.h>
#include <qobject.h>
#include "FenetreParametres.h"
#include "FenetrePrincipale.h"

#pragma once
class FenetreAccueil : public QWidget
{
	Q_OBJECT
public:
	FenetreAccueil();

public slots:
	void recevoirFenetrePara(QString j1, QString j2);

protected:
	QPushButton* jouer, *param, *quit;
	QLabel* noir, *blanc, *blank;
	QLabel* images[5][5] = { new QLabel };
	QLabel* overlay[5][5] = { new QLabel };
	QBoxLayout* boutons;
	QGridLayout* layout, *layout2;
	QMenu* menuAide;
	QAction* menuAPropos, *menuReglements;
	FenetreParametres* f_param;
	FenetrePrincipale* principale;
	void showFenetreParam(void);
	void showPrincipale(void);
	QString joueur1 = QString("Joueur 1"), joueur2 = QString("Joueur 2");
};

