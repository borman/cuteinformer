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
		void pushWidget(QWidget *w);
	private slots:
		void popWidget(QWidget *w);
		void widgetUpdated(StackManager::Item item);
	private:
		QMap<StackManager::Item, QWidget *> map;
		QMap<QWidget *, StackManager::Item> rmap;
		StackManager manager;
};

#endif // WIDGETSTACK_H
