#include "WidgetStack.h"

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>

// TODO: what to do if somebody has deleted our widget?

WidgetStack::WidgetStack(QObject *parent)
	:	QObject(parent), manager(this)
{
	connect(&manager, SIGNAL(updated(StackManager::Item)), SLOT(widgetUpdated(StackManager::Item)));
}

void WidgetStack::push(AbstractNotificationWidget *w)
{
	StackManager::Item item = manager.push(w->height());
	map[item] = w;
	rmap[w] = item;
	
	connect(w, SIGNAL(popFromStack(AbstractNotificationWidget *)), SLOT(pop(AbstractNotificationWidget *)));
	connect(w, SIGNAL(destroyed(QObject *)), SLOT(destroyed(QObject *)));
	w->setPosition(manager.bottom(item));
	w->showNotification();
}

void WidgetStack::pop(AbstractNotificationWidget *w)
{
	StackManager::Item item = rmap[w];
	manager.pop(item);
	map.remove(item);
	rmap.remove(w);
}

void WidgetStack::widgetUpdated(StackManager::Item item)
{
	AbstractNotificationWidget *w = map[item];
	w->setPosition(manager.bottom(item));
}

void WidgetStack::destroyed(QObject *o)
{
	AbstractNotificationWidget *w = qobject_cast<AbstractNotificationWidget *>(o);
	if (w && rmap.contains(w))
	{
		map.remove(rmap[w]);
		rmap.remove(w);
	}
}
