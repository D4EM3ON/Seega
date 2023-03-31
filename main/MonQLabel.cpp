/*
* Auteur : Justin Quirion
* Date: 08/04/22
*/
#include <qdebug.h>
#include <qdrag.h>
#include <qmimedata.h>
#include <qpainter.h>
#include <qevent.h>
#include "MonQLabel.h"

MonQLabel::MonQLabel() 
	: QLabel()
{
	// constructeur vide
}

MonQLabel::MonQLabel(int no, int x, int y)
	: QLabel(), m_no(no), m_x(x), m_y(y)
{
	if (m_no == 1) setPixmap(QPixmap("C:/Temp/ImageC08.png"));
	if (m_no == 0) setPixmap(QPixmap("C:/Temp/ImageC07.png"));
	if (m_no == -1) setPixmap(QPixmap("C:/Temp/ImageC00.png"));
	// constructeur
}

MonQLabel::MonQLabel(int no, int x, int y, bool aClick, bool aDrag, bool aDrop)
	: QLabel(), m_no(no), m_x(x), m_y(y), acceptClick(aClick), acceptDrag(aDrag), acceptDrop(aDrop)
{
	if (m_no == 1) setPixmap(QPixmap("C:/Temp/ImageC08.png"));
	if (m_no == 0) setPixmap(QPixmap("C:/Temp/ImageC07.png"));
	if (m_no == -1) setPixmap(QPixmap("C:/Temp/ImageC00.png"));
	setAcceptDrops(acceptDrop);
	// constructeur avec bool
}

MonQLabel::MonQLabel(MonQLabel const& label)
	: QLabel(), m_no(label.m_no), m_x(label.m_x), m_y(label.m_y), acceptClick(label.acceptClick), acceptDrag(label.acceptDrag), acceptDrop(label.acceptDrop)
{
	if (m_no == 1) setPixmap(QPixmap("C:/Temp/ImageC08.png"));
	if (m_no == 0) setPixmap(QPixmap("C:/Temp/ImageC07.png"));
	if (m_no == -1) setPixmap(QPixmap("C:/Temp/ImageC00.png"));
	setAcceptDrops(acceptDrop);
	// constructeur à partir d'un autre monQLabel
}

int MonQLabel::getNo() // aller chercher le no
{
	return m_no;
}

int MonQLabel::getX() { // aller chercher le x
	return m_x;
}
int MonQLabel::getY() { // aller chercher le y
	return m_y;
}

void MonQLabel::setXY(int x, int y) // set x, y
{
	m_x = x;
	m_y = y;
}

void MonQLabel::setNo(int no) // set no
{
	m_no = no;
}

void MonQLabel::setDrop(bool accept) // set drop
{
	acceptDrop = accept;
	setAcceptDrops(acceptDrop);
}

void MonQLabel::setDrag(bool accept) // set drag
{
	acceptDrag = accept;
}

void MonQLabel::setClick(bool accept) // set click
{
	acceptClick = accept;
}

void MonQLabel::changeImage(int no) // set changement d'image
{
	m_no = no;
	if (m_no == 1) setPixmap(QPixmap("C:/Temp/ImageC08.png"));
	if (m_no == 0) setPixmap(QPixmap("C:/Temp/ImageC07.png"));
	if (m_no == -1) setPixmap(QPixmap("C:/Temp/ImageC00.png"));
}

void MonQLabel::setReplay(bool tf) // regarder s'il va rejouer
{
	replay = tf;
}

void MonQLabel::removePiece() // enlever une piece
{
	changeImage(-1);
	setDrop(true);
	setDrag(false);
}

void MonQLabel::clickRemove(bool tf) // regarder s'il peut être enlevé
{
	acceptRemove = tf;
}

bool MonQLabel::getReplay() // regarder s'il peut rejouer
{
	return replay;
}

void MonQLabel::mousePressEvent(QMouseEvent* event) { // ce qui arrive lorsque la souris est pressée
	if (acceptDrag) {
		MonQLabel* child = new MonQLabel(*this);
		child->parent = this;

		QPixmap pixmap = child->pixmap();
		QByteArray itemData;
		QDataStream infoTransmises(&itemData, QIODevice::WriteOnly);

		// Informations transmises sont pixmap, position
		infoTransmises << pixmap << QPoint(event->pos()) << m_no << m_x << m_y;

		QMimeData* mimeData = new QMimeData;
		mimeData->setData("application/x-dnditemdata", itemData);
		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(pixmap);
		drag->setHotSpot(event->pos());

		QPixmap tempPixmap = pixmap;
		QPainter painter;
		painter.begin(&tempPixmap);
		painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
		painter.end();

		child->setPixmap(tempPixmap);

		emit signalDrag();
		if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) child->close();
		else {
			child->setPixmap(pixmap);
		}
	}
	if (acceptClick) {
		emit clicked();
	}
	if (acceptRemove) {
		emit clicked();
	}
}


void MonQLabel::dragEnterEvent(QDragEnterEvent* event) // lorsqu'un drag arrive
{
	if (event->source() == this) {
		event->setDropAction(Qt::MoveAction);
	}
	else {
		event->acceptProposedAction();
	}
}

void MonQLabel::dragMoveEvent(QDragMoveEvent* event) // lorsqu'un drag bouge
{
	if (event->source() == this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else {
		event->acceptProposedAction();
	}
}

void MonQLabel::dropEvent(QDropEvent* event) // lorsqu'il est finalement drop
{
	QByteArray infoImportantes = event->mimeData()->data("application/x-dnditemdata");
	QDataStream infoTransmises(&infoImportantes, QIODevice::ReadOnly);

	QPixmap pixmap;
	QPoint offset;
	MonQLabel* mql;
	int x, y, no;

	infoTransmises >> pixmap >> offset >> no >> x >> y;

	if (event->source() == this ) {
		event->setDropAction(Qt::CopyAction);
		event->accept();
		
	}
	else if (((x == m_x + 1 || x == m_x - 1 || x == m_x) && y == m_y) || (x == m_x && (y == m_y + 1 || y == m_y - 1 || y == m_y))) {
		emit signalDrop();
		event->acceptProposedAction();
		/*this->setPixmap(pixmap);
		this->setDrag(true);
		this->setDrop(false);
		this->m_no = no;
		this->m_x = x;
		this->m_y = y;¸*/
		acceptedDrop = true;
	}

	
}