#ifndef STACKVIEW_H
#define STACKVIEW_H

#include <QtGui>
#include "stackmanager.h"

class StackView: public QWidget
{
	Q_OBJECT
	public:
		StackView(QWidget *parent = NULL);
	protected:
		void paintEvent(QPaintEvent *event);
		void mousePressEvent(QMouseEvent *event);
	private slots:
		void itemUpdated(StackManager::Item);
	private:
		StackManager *manager;
		QList<StackManager::Item> items;
};

#endif // STACKVIEW_H

