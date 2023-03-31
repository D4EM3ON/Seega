/*
* Auteur : Justin Quiriono
* Date : 11/04/22
*/
#include "FenetreReglements.h"

using namespace::std;

FenetreReglements::FenetreReglements()
	: layout(nullptr), reglements(nullptr), quit(nullptr), reglements2(nullptr), reglements3(nullptr), reglements4(nullptr), reglements5(nullptr)
{
	setWindowTitle(QString("SEEGA - Règlements"));

	layout = new QVBoxLayout; // déclarer, ouverture de tout
	reglements = new QLabel;
	reglements2 = new QLabel;
	reglements3 = new QLabel;
	reglements4 = new QLabel;
	reglements5 = new QLabel;
	quit = new QPushButton("Fermer");
	connect(quit, &QPushButton::clicked, this, &FenetreReglements::close); // fermer la fenetre

	// déclarer messages à ajouter dans un paragraphe (ne marchait pas sans ces strings)
	string msg = "Le sandwich diagonal ne compte pas. Les pièces ne sont prises que lorsque l’adversaire fait un mouvement qui la prend en sandwich. Par exemple, si ";
	string msg1 = "vous déplacez votre pièce entre deux pièces de votre adversaire, votre pièce est en sécurité. ";

	// définir paragraphes
	reglements->setText(QString::fromUtf8("Seega est joué sur un tableau de 5 cases sur 5, dont la case centrale est barrée. Le tableau est tout d’abord vide et chaque joueur commence avec 12 pièces de sa propre couleur."));
	reglements2->setText(QString::fromUtf8("Les joueurs décident au hasard qui commence. À tour de rôle, les joueurs placent 2 pièces chacune n’importe où sur le tableau, à l’exception du carré central. Lorsque toutes les pièces sont placées, le deuxième joueur commence la phase de mouvement en déplaçant les pièces. Une pièce peut se déplacer d’un carré dans n’importe quelle direction horizontale ou verticale. Les mouvements diagonaux ne sont pas autorisés. Dans cette phase, les pièces peuvent se déplacer sur la case centrale."));
	reglements3->setText(QString::fromUtf8("Si un joueur est complètement bloqué de manière à ne pouvoir effectuer aucun mouvement, le joueur bloqué est autorisé à retirer l’une des pièces de l’adversaire pour dégager un chemin. Cette situation ne survient généralement que lors des premiers mouvements de la partie. Si un joueur emprisonne une pièce ennemie entre deux des siennes, la pièce de jeu est capturée et retirée du tableau. Le piégeage diagonal ne compte pas ici. Après avoir déplacé une pièce pour capturer un ennemi, le joueur peut continuer à déplacer la même pièce. Si, lors du déplacement d’une pièce, deux ou trois ennemis se retrouvent piégés simultanément, tous ces ennemis piégés sont capturés et retirés du plateau."));
	reglements4->setText(QString::fromUtf8("Une pièce est prise (retirée du tableau) lorsqu’elle est prise en sandwich par deux des pièces de l’adversaire. Le sandwich diagonal ne compte pas. Les pièces ne sont prises que lorsque l’adversaire fait un mouvement qui la prend en sandwich. Par exemple, si vous déplacez votre pièce entre deux pièces de votre adversaire, votre pièce est en sécurité."));
	reglements5->setText(QString::fromUtf8("Une pièce sur la case centrale est à l’abri de la capture, mais peut elle-même être utilisée pour capturer des pièces ennemies. La partie est gagnée par le joueur qui a capturé toutes les pièces de son ennemi. Le gagnant est trouvé lors de 2 situations: s'il a capturé toutes les pièces de son adversaire, ou lorsqu'une personne forme une colonne (5 pions en ligne) et qu'il a mangé plus de pions que son adversaire. Si les deux ont mangés le même nombre de pions, la partie est nulle."));

	// pour qu'on puisse les voir sur l'écran 
	reglements->setWordWrap(true);
	reglements2->setWordWrap(true);
	reglements3->setWordWrap(true);
	reglements4->setWordWrap(true);
	reglements5->setWordWrap(true);

	// les ajouter au layout
	layout->addWidget(reglements);
	layout->addWidget(reglements2);
	layout->addWidget(reglements3);
	layout->addWidget(reglements4);
	layout->addWidget(reglements5);
	layout->addWidget(quit);

	setLayout(layout);
}
