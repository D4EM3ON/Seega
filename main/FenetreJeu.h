/*
* Auteur : Justin Quirion
* Date : 19/04/22
*/

#include <qapplication.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <qgridlayout.h>
#include <qsignalmapper.h>
#include <map>
#include <qgroupbox.h>
#include <qmessagebox.h>
#include "MonQLabel.h"

#pragma once

class FenetreJeu : public QWidget
{
	Q_OBJECT
public:
	FenetreJeu(QString joueur1, QString joueur2);
	void changeNomJ1(QString joueur1);
	void changeNomJ2(QString joueur2);

public slots:
	void slotChangerImage(const int& nb);
	void slotDrag(const int& nb);
	void slotDrop(const int& nb);
	void removeClick(const int& nb);

protected:
	QPushButton* re, * quit;
	QLabel* j1, *j2;
	QVBoxLayout* v1, *v2;
	QGridLayout* layout, *layout2, *layout3, *layout4, *layoutJ1, *layoutJ2;
	MonQLabel* jeu[5][5], * jeuJ1[4][3], * jeuJ2[4][3], *overlay[5][5];
	QSignalMapper* m_qsm, *m_qsmDrag, *m_qsmDrop;
	QGroupBox* groupJ1, * groupJ2, * groupP1, * groupP2, * game;
	QMessageBox* message;
	int c = 0, c1 = 1, m_dragImage, m_dropImage, ij1 = 2, jj1 = 3, jj2 = 3, ij2 = 2, m = 0, k = 0, m1 = 0, m2 = 0, k1 = 0, k2 = 0, jDrop, iDrop, jDrag, iDrag;
	bool last = true, removed = false;
	bool lookCannotPlay(int no);
	void clickPlay(int no);
	bool replay, canReplay;
	void beginPlay(int nb);
	bool lookPartieNulle();
	void messageWon();
};

