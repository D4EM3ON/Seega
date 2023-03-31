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
class FenetreReglements : public QWidget
{
	Q_OBJECT
public:
	FenetreReglements();

protected:
	QLabel* reglements, *reglements2, *reglements3, *reglements4, *reglements5;
	QPushButton* quit;
	QVBoxLayout* layout;
};

