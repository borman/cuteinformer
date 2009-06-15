#ifndef WIDGETSTACK_H
#define WIDGETSTACK_H

#include <QObject>
#include <QMap>
#include "stackmanager.h"

class WidgetStack: public QObject
{
	Q_OBJECT
	public:
		WidgetStack(QObject *parent = NULL);
	public slots:
		void pushWidget(QWidget *w);
		void popWidget(QWidget *w);
	private slots:
		void widgetUpdated(StackManager::Item item);
	private:
		void placeWidget(QWidget *w, int pos);
		
		QMap<StackManager::Item, QWidget *> map;
		QMap<QWidget *, StackManager::Item> rmap;
		StackManager manager;
};

#endif // WIDGETSTACK_H
