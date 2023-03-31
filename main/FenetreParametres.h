/*
* Auteur : Justin Quiriono
* Date : 19/04/22
*/
#include <qwidget.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qgroupbox.h>
#include <qgridlayout.h>
#include <qboxlayout.h>
#include <qlineedit.h>

#pragma once
class FenetreParametres : public QWidget
{
	Q_OBJECT
public:
	FenetreParametres();
	FenetreParametres(QString* j1, QString* j2);


signals:
	void signalFromPara(QString j10, QString j20);

protected:
	QPushButton* annuler,* OK;
	QLineEdit* joueur1, *joueur2;
	QLabel* monImage1, *labelJ1, *labelJ2;
	QGroupBox* joueurs;
	QGridLayout* layout;
	QString j1, j2;
	QVBoxLayout* verticalLabel, *verticalEdit;
	QHBoxLayout* box;
	void pushedOK();
};

