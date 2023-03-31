/*
* Auteur : Justin Quirion
* Date: 08/04/22
*/
#pragma once
#include <qlabel.h>
#include <QDragEnterEvent>
#include <QDragMoveEvent>

class MonQLabel : public QLabel
{
	Q_OBJECT
public:
	MonQLabel();
	MonQLabel(int no, int x, int y);
	MonQLabel(int no, int x, int y, bool aClick, bool aDrag, bool aDrop);
	MonQLabel(MonQLabel const& label);
	int getNo();
	int getX();
	int getY();
	void setXY(int x, int y);
	void setNo(int no);

	void setDrop(bool accept);
	void setDrag(bool accept);
	void setClick(bool accept);
	void changeImage(int no);
	void setReplay(bool tf);

	void removePiece();
	void clickRemove(bool tf);

	bool getReplay();

signals:
	void clicked();
	void signalDrop();
	void signalDrag();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	int m_no, m_x, m_y;
	bool acceptClick, acceptDrag, acceptDrop, acceptRemove = false, acceptedDrop = false, replay = false;
	MonQLabel* parent = this;
};

std::istream& operator>>(std::istream& flux, MonQLabel* obj);
