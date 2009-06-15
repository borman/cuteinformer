#include "widgetstack.h"

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>

WidgetStack::WidgetStack(QObject *parent)
	:	QObject(parent), manager(this)
{
	connect(&manager, SIGNAL(updated(StackManager::Item)), SLOT(widgetUpdated(StackManager::Item)));
}

void WidgetStack::pushWidget(QWidget *w)
{
	StackManager::Item item = manager.push(w->height());
	map[item] = w;
	rmap[w] = item;
	
	connect(w, SIGNAL(popFromStack(QWidget *)), SLOT(popWidget(QWidget *)));
	placeWidget(w, manager.bottom(item));
	w->show();
}

void WidgetStack::popWidget(QWidget *w)
{
	StackManager::Item item = rmap[w];
	manager.pop(item);
	map.remove(item);
	rmap.remove(w);
}

void WidgetStack::widgetUpdated(StackManager::Item item)
{
	QWidget *w = map[item];
	Q_ASSERT(w);
	
	placeWidget(w, manager.bottom(item));
}

void WidgetStack::placeWidget(QWidget *w, int pos)
{
	QPoint wp = QApplication::desktop()->availableGeometry(w).bottomRight()
						 +QPoint(-w->width(), -w->height()-pos);
	w->move(wp);
}
