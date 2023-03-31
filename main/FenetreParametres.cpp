/*
* Auteur : Justin Quiriono
* Date : 19/04/22
*/

#include "FenetreParametres.h"

FenetreParametres::FenetreParametres()
	: annuler(nullptr), OK(nullptr), joueur1(nullptr), joueur2(nullptr), monImage1(nullptr), layout(nullptr), joueurs(nullptr), verticalEdit(nullptr), verticalLabel(nullptr), box(nullptr)
{
	annuler = new QPushButton("Annuler"); // définir et déclarer
	OK = new QPushButton("OK");
	joueurs = new QGroupBox;
	joueur1 = new QLineEdit("Joueur 1");
	joueur2 = new QLineEdit("Joueur 2");
	monImage1 = new QLabel;
	labelJ2 = new QLabel;
	labelJ1 = new QLabel;
	layout = new QGridLayout;
	verticalEdit = new QVBoxLayout;
	verticalLabel = new QVBoxLayout;
	box = new QHBoxLayout;

	labelJ1->setText("Joueur #1 : "); 
	labelJ2->setText("Joueur #2 : ");

	verticalLabel->addWidget(labelJ1);
	verticalLabel->addWidget(labelJ2);

	verticalEdit->addWidget(joueur1);
	verticalEdit->addWidget(joueur2);

	box->addLayout(verticalLabel);
	box->addLayout(verticalEdit);

	joueurs->setLayout(box);

	monImage1->setPixmap(QPixmap("C:/Temp/ImageC09.jpg")); 
	layout->addWidget(monImage1, 0, 0, 6, 4); // ajout de l'image

	joueurs->setTitle("Nom des joueurs"); 

	layout->addWidget(joueurs, 0, 4); // ajout des widgets au layout
	layout->addWidget(annuler, 4, 4);
	layout->addWidget(OK, 5, 4);
	 
	connect(annuler, &QPushButton::clicked, this, &FenetreParametres::close); // fermer si c'est poussé
	connect(OK, &QPushButton::clicked, this, &FenetreParametres::pushedOK); // enregistrer les changements si OK dans la fonction pushedOK
	setLayout(layout);
}

FenetreParametres::FenetreParametres(QString* j1, QString* j2) // meme chose que le blank, sauf non-vide
{
	annuler = new QPushButton("Annuler");
	OK = new QPushButton("OK");
	joueurs = new QGroupBox;
	joueur1 = new QLineEdit(*j1);
	joueur2 = new QLineEdit(*j2);
	monImage1 = new QLabel;
	labelJ2 = new QLabel;
	labelJ1 = new QLabel;
	layout = new QGridLayout;
	verticalEdit = new QVBoxLayout;
	verticalLabel = new QVBoxLayout;
	box = new QHBoxLayout;

	labelJ1->setText("Joueur #1 : ");
	labelJ2->setText("Joueur #2 : ");

	verticalLabel->addWidget(labelJ1);
	verticalLabel->addWidget(labelJ2);

	verticalEdit->addWidget(joueur1);
	verticalEdit->addWidget(joueur2);

	box->addLayout(verticalLabel);
	box->addLayout(verticalEdit);

	joueurs->setLayout(box);

	monImage1->setPixmap(QPixmap("C:/Temp/ImageC09.jpg"));
	layout->addWidget(monImage1, 0, 0, 6, 4);

	joueurs->setTitle("Nom des joueurs");

	layout->addWidget(joueurs, 0, 4);
	layout->addWidget(annuler, 4, 4);
	layout->addWidget(OK, 5, 4);

	connect(annuler, &QPushButton::clicked, this, &FenetreParametres::close);
	connect(OK, &QPushButton::clicked, this, &FenetreParametres::pushedOK);
	setLayout(layout);
}

void FenetreParametres::pushedOK() // set le texte et emettre le signal avec les noms des joueurs
{
	j1 = joueur1->text();
	j2 = joueur2->text();
	emit signalFromPara(j1, j2);
	close();
}
