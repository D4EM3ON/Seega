/*
* Auteur : Justin Quiriono
* Date : 11/04/22
*/
#include <qapplication.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qboxlayout.h>

#pragma once
class FenetreAPropos : public QWidget
{
	Q_OBJECT
public:
	FenetreAPropos();

protected:
	QLabel* nom;
	QLabel* version;
	QLabel* concepteur;
	QPushButton* quit;
	QVBoxLayout* layout;
};

