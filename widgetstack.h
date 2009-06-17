#ifndef WIDGETSTACK_H
#define WIDGETSTACK_H

#include <QObject>
#include <QMap>
#include "stackmanager.h"
#include "abstract_notification_widget.h"

class WidgetStack: public QObject
{
	Q_OBJECT
	public:
		WidgetStack(QObject *parent = NULL);
	public slots:
		void push(AbstractNotificationWidget *w);
		void pop(AbstractNotificationWidget *w);
	private slots:
		void widgetUpdated(StackManager::Item item);
		void destroyed(QObject *o);
	private:
		QMap<StackManager::Item, AbstractNotificationWidget *> map;
		QMap<AbstractNotificationWidget *, StackManager::Item> rmap;
		StackManager manager;
};

#endif // WIDGETSTACK_H
