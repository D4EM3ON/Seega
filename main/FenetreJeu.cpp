/*
* Auteur : Justin Quirion
* Date : 19/04/22
*/
#include <random>
#include "FenetreJeu.h"
#include <qradiobutton.h>

//  0 = blanc
// -1 = vide
//  1 = noir

FenetreJeu::FenetreJeu(QString joueur1, QString joueur2)
	: re(nullptr), quit(nullptr), j1(nullptr), j2(nullptr), v1(nullptr), v2(nullptr), layout(nullptr), layout2(nullptr), layout3(nullptr), layout4(nullptr), groupJ1(nullptr), groupJ2(nullptr), groupP1(nullptr), groupP2(nullptr), game(nullptr), layoutJ1(nullptr), layoutJ2(nullptr), m_qsmDrag(nullptr), m_qsmDrop(nullptr), message(nullptr)
{
	QRadioButton* n = new QRadioButton;
	j1 = new QLabel(joueur1);
	j2 = new QLabel(joueur2);
	j1->setFont(QFont("Arial", 65));
	j1->setAlignment(Qt::AlignCenter);
	j2->setFont(QFont("Arial", 65));
	j2->setAlignment(Qt::AlignCenter);

	re = new QPushButton("Recommencer");
	quit = new QPushButton("Quitter");
	m_qsm = new QSignalMapper;
	m_qsmDrag = new QSignalMapper;
	m_qsmDrop = new QSignalMapper;
	layout2 = new QGridLayout;
	layout3 = new QGridLayout;
	layout4 = new QGridLayout;
	layout = new QGridLayout;
	layoutJ1 = new QGridLayout;
	layoutJ2 = new QGridLayout;

	groupJ1 = new QGroupBox;
	groupJ2 = new QGroupBox;
	groupP1 = new QGroupBox;
	groupP2 = new QGroupBox;
	game = new QGroupBox;

	v1 = new QVBoxLayout;
	v2 = new QVBoxLayout;

	message = new QMessageBox;

	layoutJ1->addWidget(new QLabel(), 0, 0, 2, 3);
	layoutJ1->addWidget(new QLabel(), 1, 0);
	layoutJ1->addWidget(new QLabel(), 2, 0);
	layoutJ1->addWidget(j1, 3, 0, 1, 3);
	layoutJ1->addWidget(new QLabel(), 4, 0);
	layoutJ1->addWidget(new QLabel(), 5, 0);
	layoutJ1->addWidget(new QLabel(), 6, 0);

	layoutJ2->addWidget(new QLabel(), 0, 0);
	layoutJ2->addWidget(new QLabel(), 1, 0);
	layoutJ2->addWidget(new QLabel(), 2, 0);
	layoutJ2->addWidget(j2, 3, 0, 1, 3);
	layoutJ2->addWidget(new QLabel(), 4, 0);
	layoutJ2->addWidget(new QLabel(), 5, 0);
	layoutJ2->addWidget(new QLabel(), 6, 0);

	groupJ1->setLayout(layoutJ1);
	groupJ2->setLayout(layoutJ2);

	for (int i = 0; i < 5; i++) { // pour les 5x5 cases, modifier l'image pour qu'elle soit vide
		for (int j = 0; j < 5; j++, m++) {
			jeu[i][j] = new MonQLabel(-1, i, j, true, false, true); // les sauvegarder dans un array for future use
			if (m == 4) {
				m = 0;
				k += 1;
			}
			if (k < 3) {
				jeuJ1[m][k] = new MonQLabel(0, k, m, false, false, false);
				jeuJ2[m][k] = new MonQLabel(1, k, m, false, false, false);
				layout3->addWidget(jeuJ1[m][k], k, m);
				layout4->addWidget(jeuJ2[m][k], k, m);
			}

			connect(jeu[i][j], SIGNAL(clicked()), m_qsm, SLOT(map()));
			m_qsm->setMapping(jeu[i][j], i * 5 + j);
			
			connect(jeu[i][j], SIGNAL(signalDrag()), m_qsmDrag, SLOT(map()));
			m_qsmDrag->setMapping(jeu[i][j], i * 5 + j);

			connect(jeu[i][j], SIGNAL(signalDrop()), m_qsmDrop, SLOT(map()));
			m_qsmDrop->setMapping(jeu[i][j], i * 5 + j);
			
			layout2->addWidget(jeu[i][j], j, i);
		}
	}
	m = 0;
	k = 0;
	connect(m_qsm, SIGNAL(mappedInt(int)), this, SLOT(slotChangerImage(int))); // conncecter aux fonctions
	connect(m_qsmDrag, SIGNAL(mappedInt(int)), this, SLOT(slotDrag(int)));
	connect(m_qsmDrop, SIGNAL(mappedInt(int)), this, SLOT(slotDrop(int)));

	jeu[2][2]->setClick(false);

	groupP1->setLayout(layout3);
	groupP2->setLayout(layout4);
	game->setLayout(layout2);

	v1->addWidget(groupJ1);
	v1->addWidget(groupP1);
	v2->addWidget(groupJ2);
	v2->addWidget(groupP2);

	layout->addLayout(v1, 0, 0, 2, 2);
	layout->addWidget(game, 0, 3, 5, 5);
	layout->addLayout(v2, 0, 8, 2, 2);
	setLayout(layout);
}

void FenetreJeu::changeNomJ1(QString joueur1) // changer noms
{
	j1->setText(joueur1);
}

void FenetreJeu::changeNomJ2(QString joueur2)
{
	j2->setText(joueur2);
}

void FenetreJeu::slotChangerImage(const int& nb) // changer image avant drag & drop
{
	if (c == 0) c1 = round(rand() % 2);
	if (c < 24) { // premier 24
		if (++c % 2 != 0) c1 = !c1;

		int j = nb % 5;
		int i = (nb - j) / 5;
		jeu[i][j]->changeImage(c1);
		jeu[i][j]->setDrop(false);

		if (!c1) {
			jeuJ1[jj1][ij1]->changeImage(-1);
			if (jj1 == 0) {
				ij1 -= 1;
				jj1 = 4;
			}
			jj1--;
		}
		else {
			jeuJ2[jj2][ij2]->changeImage(-1);
			if (jj2 == 0) {
				ij2 -= 1;
				jj2 = 4;
			}
			jj2--;
		}
		
		jeu[i][j]->setClick(false);
		jeu[i][j]->setNo(c1);
	}
	if (c == 24) { // a 24 images
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (jeu[i][j]->getNo() != -1 && jeu[i][j]->getNo() == c1) {
					jeu[i][j]->setDrag(true);
					disconnect(jeu[i][j], SIGNAL(clicked()), m_qsm, SLOT(map()));
					disconnect(m_qsm, SIGNAL(mappedInt(int)), this, SLOT(slotChangerImage(int)));
				}
			}
		}
		if (lookCannotPlay(c1)) clickPlay(!c1); 
		if (lookPartieNulle()) messageWon();
	}
}

void FenetreJeu::slotDrag(const int& nb)
{
	m_dragImage = nb;
}

void FenetreJeu::slotDrop(const int& nb) // lorsqu'il se fait drop
{
	beginPlay(nb);
	
	int finalI = -1, finalJ = -1;


	c1 = !c1; // changement du joueur

	if (jeu[iDrop + 2][jDrop]->getNo() == jeu[iDrop][jDrop]->getNo() && jeu[iDrop + 1][jDrop]->getNo() != jeu[iDrop][jDrop]->getNo()) {
		if (jeu[iDrop][jDrop]->getX() < 3 && (jeu[iDrop + 1][jDrop]->getX() != 2 || jeu[iDrop + 1][jDrop]->getY() != 2)) {
			if (jeu[iDrop + 1][jDrop]->getNo() == 0) { // main logique du jeu plus haut, répété pour les 100 prochaines lignes
				jeuJ1[m1][k1]->changeImage(0); // si c'est un blanc
				m1++;
				if (m1 == 4) {
					m1 = 0;
					k1 += 1;
					replay = true;
				}
			}
			if (jeu[iDrop + 1][jDrop]->getNo() == 1) {
				jeuJ2[m2][k2]->changeImage(1); // si c'est un noir
				m2++;
				if (m2 == 4) {
					m2 = 0;
					k2 += 1;
				}
				replay = true;
				}
			jeu[iDrop + 1][jDrop]->removePiece();
			finalI = iDrop + 1;
			finalJ = jDrop;
		}
	}
			
	if (jeu[iDrop - 2][jDrop]->getNo() == jeu[iDrop][jDrop]->getNo() && jeu[iDrop - 1][jDrop]->getNo() != jeu[iDrop][jDrop]->getNo()) {
		if (jeu[iDrop][jDrop]->getX() > 1 && (jeu[iDrop - 1][jDrop]->getX() != 2 || jeu[iDrop - 1][jDrop]->getY() != 2)) {
			if (jeu[iDrop - 1][jDrop]->getNo() == 0) {
				jeuJ1[m1][k1]->changeImage(0);
				m1++;
				if (m1 == 4) {
					m1 = 0;
					k1 += 1;
				}
				replay = true;
			}
			if (jeu[iDrop - 1][jDrop]->getNo() == 1) {
				jeuJ2[m2][k2]->changeImage(1);
				m2++;
				if (m2 == 4) {
					m2 = 0;
					k2 += 1;
				}
				replay = true;
			}
			jeu[iDrop - 1][jDrop]->removePiece();
			finalI = iDrop - 1;
			finalJ = jDrop;
		}
	}

	if (jeu[iDrop][jDrop + 2]->getNo() == jeu[iDrop][jDrop]->getNo() && jeu[iDrop][jDrop + 1]->getNo() != jeu[iDrop][jDrop]->getNo()) {
		if (jeu[iDrop][jDrop]->getY() < 3 && (jeu[iDrop][jDrop + 1]->getX() != 2 || jeu[iDrop][jDrop + 1]->getY() != 2)) {
			if (jeu[iDrop][jDrop + 1]->getNo() == 0) {
				jeuJ1[m1][k1]->changeImage(0);
				m1++;
				if (m1 == 4) {
					m1 = 0;
					k1 += 1;
				}
				replay = true;
			}
			if (jeu[iDrop][jDrop + 1]->getNo() == 1) {
				jeuJ2[m2][k2]->changeImage(1);
				m2++;
				if (m2 == 4) {
					m2 = 0;
					k2 += 1;
				}
				replay = true;
			}
			jeu[iDrop][jDrop + 1]->removePiece();
			finalI = iDrop;
			finalJ = jDrop + 1;
		}
		
	}
	if (jeu[iDrop][jDrop - 2]->getNo() == jeu[iDrop][jDrop]->getNo() && jeu[iDrop][jDrop - 1]->getNo() != jeu[iDrop][jDrop]->getNo()) {
		if (jeu[iDrop][jDrop]->getY() > 1 && (jeu[iDrop][jDrop - 1]->getX() != 2 || jeu[iDrop][jDrop - 1]->getY() != 2)) {
			if (jeu[iDrop][jDrop - 1]->getNo() == 0) {
				jeuJ1[m1][k1]->changeImage(0);
				m1++;
				if (m1 == 4) {
					m1 = 0;
					k1 += 1;
				}
				replay = true;
			}
			if (jeu[iDrop][jDrop - 1]->getNo() == 1) {
				jeuJ2[m2][k2]->changeImage(1);
				m2++;
				if (m2 == 4) {
					m2 = 0;
					k2 += 1;
				}
				replay = true;
			}
			jeu[iDrop][jDrop - 1]->removePiece();
			finalI = iDrop;
			finalJ = jDrop - 1;
		}
	}
	if (replay) { // s'il peut rejouer
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				jeu[i][j]->setDrag(false);
			}
		}
		jeu[iDrop][jDrop]->setReplay(true);
		jeu[iDrop][jDrop]->setDrag(true);
		canReplay = true;
	}
	else {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
 				if (jeu[i][j]->getNo() != -1 && jeu[i][j]->getNo() == c1) {
					jeu[i][j]->setDrag(true);
				}
				else jeu[i][j]->setDrag(false);
				jeu[i][j]->clickRemove(false);
				jeu[i][j]->setReplay(false);
			}
		}
	}
	if (k1 == 3 || k2 == 3) messageWon();  // regarder si l'un ou l'autre a gagné
	if (lookCannotPlay(c1)) clickPlay(!c1); // regarder si on peut jouer
	if (lookPartieNulle()) messageWon(); // regarder si la partie est nulle (lignes de pions)
}

void FenetreJeu::removeClick(const int& nb) // pour enlever si jamais il est pogmé
{
	int j = nb % 5;
	int i = (nb - j) / 5;
	jeu[i][j]->changeImage(-1);
	jeu[i][j]->setDrop(true);
	if (!c1 && !removed) {
		jeuJ2[m2][k2]->changeImage(1);
		m2++;
		if (m2 == 4) {
			m2 = 0;
			k2 += 1;
		}
		removed = true;
	}
	else if (c1 && !removed) {
		jeuJ1[m1][k1]->changeImage(0);
		m1++;
		if (m1 == 4) {
			m1 = 0;
			k1 += 1;
		}
		removed = true;
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			jeu[i][j]->clickRemove(false);
		}
	}
}

bool FenetreJeu::lookCannotPlay(int no) // regarder s'il ne peut pas jouer
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (jeu[i][j]->getNo() == no) {
				if ((i < 4 && jeu[i + 1][j]->getNo() == -1) || (i > 0 && jeu[i - 1][j]->getNo() == -1) || (j > 0 && jeu[i][j - 1]->getNo() == -1) || (j < 4 && jeu[i][j + 1]->getNo() == -1)) {
					return false; // si autour pas de -1
				}
			}
		}
	}
	return true;
}

void FenetreJeu::clickPlay(int no) // mettre pour qu'ils peuvent s'enlever
{
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++) {
			if (jeu[i][j]->getNo() == no) {
				if ((i < 4 && jeu[i + 1][j]->getNo() == !no) || (i > 0 && jeu[i - 1][j]->getNo() == !no) || (j > 0 && jeu[i][j - 1]->getNo() == !no) || (j < 4 && jeu[i][j + 1]->getNo() == !no)) {
					jeu[i][j]->clickRemove(true);
					connect(jeu[i][j], SIGNAL(clicked()), m_qsm, SLOT(map()));
				}
			}
		}
	}
	removed = false;
	connect(m_qsm, SIGNAL(mappedInt(int)), this, SLOT(removeClick(int)));
}

void FenetreJeu::beginPlay(int nb) // début du jeu
{
	replay = false;
	m_dropImage = nb;
	jDrop = nb % 5;
	iDrop = (nb - jDrop) / 5;
	jDrag = m_dragImage % 5;
	iDrag = (m_dragImage - jDrag) / 5;

	int dragPixmap = jeu[iDrag][jDrag]->getNo();
	int dropPixmap = jeu[iDrop][jDrop]->getNo();

	jeu[iDrag][jDrag]->changeImage(dropPixmap);
	jeu[iDrag][jDrag]->setDrag(false);
	jeu[iDrag][jDrag]->setDrop(true);

	jeu[iDrop][jDrop]->changeImage(dragPixmap);
	jeu[iDrop][jDrop]->setDrag(true);
	jeu[iDrop][jDrop]->setDrop(false);

	jeu[iDrop][jDrop]->setNo(dragPixmap);
	jeu[iDrag][jDrag]->setNo(dropPixmap);

	canReplay = false;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (jeu[i][j]->getReplay()) {
				canReplay = true;
				c1 = !c1;
				break;
			}
		}
	}

	if (!canReplay) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (jeu[i][j]->getNo() != -1 && jeu[i][j]->getNo() == c1) {
					jeu[i][j]->setDrag(true);
				}
				else jeu[i][j]->setDrag(false);
				jeu[i][j]->clickRemove(false);
			}
		}
	}
}

bool FenetreJeu::lookPartieNulle(void) { // regarder si la partie est nulle
	int i = 0;
	for (int j = 0; j < 5; j++) {
			if (jeu[i][j]->getNo() == jeu[i + 1][j]->getNo() && jeu[i][j]->getNo() == jeu[i + 2][j]->getNo() && jeu[i][j]->getNo() == jeu[i + 3][j]->getNo() && jeu[i][j]->getNo() == jeu[i + 4][j]->getNo() && jeu[i][j]->getNo() != -1) return true;
	}

	int j = 0;
	for (int i = 0; i < 5; i++) {
		if (jeu[i][j]->getNo() == jeu[i][j + 1]->getNo() && jeu[i][j]->getNo() == jeu[i][j + 2]->getNo() && jeu[i][j]->getNo() == jeu[i][j + 3]->getNo() && jeu[i][j]->getNo() == jeu[i][j + 4]->getNo() && jeu[i][j]->getNo() != -1) return true;
	}
	
	return false;
}

void FenetreJeu::messageWon() { // regarder qui est le gagnant, l'afficher
	int counterJ1 = 0;
	int counterJ2 = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (jeuJ1[i][j]->getNo() != -1) counterJ1++;
			if (jeuJ2[i][j]->getNo() != -1) counterJ2++;
		}
	}
	message->setWindowTitle(QString::fromLatin1("Félicitations !"));
	if (counterJ1 > counterJ2) message->setText("Le gagnant de cette partie est... " + j2->text() + " ! Bravo !");
	else if (counterJ1 < counterJ2) message->setText("Le gagnant de cette partie est... " + j1->text() + " ! Bravo !");
	else {
		message->setWindowTitle("Partie nulle");
		message->setText(QString::fromLatin1("Personne n'a gagné, la partie est nulle."));
	}
	message->setStandardButtons(QMessageBox::Ok);
	message->setIcon(QMessageBox::Information);
	message->exec();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			jeu[i][j]->setDrop(false);
			jeu[i][j]->setDrag(false);
		}
	}

}