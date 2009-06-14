#include "stackview.h"

StackView::StackView(QWidget *parent)
	: QWidget(parent), manager(new StackManager(this))
{
	connect(manager, SIGNAL(updated(StackManager::Item)), SLOT(itemUpdated(StackManager::Item)));
}

const int item_width = 160;
void StackView::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	foreach (StackManager::Item item, items)
	{
		StackManager::Metric pos, h;
		pos = manager->bottom(item);
		h = manager->height(item);
		QRect rect(width()-item_width, height()-pos-h, item_width, h);
		p.fillRect(rect, Qt::black);
	}
}

void StackView::mousePressEvent(QMouseEvent *event)
{
	if (event->button()==Qt::LeftButton)
	{
		items << manager->push(20+rand()%50);
	}
	if (event->button()==Qt::RightButton)
	{
		QList<StackManager::Item>::iterator it = items.begin();
		while (it!=items.end())
		{
			StackManager::Item item = *it;
			StackManager::Metric pos, h;
			pos = manager->bottom(item);
			h = manager->height(item);
			QRect rect(width()-item_width, height()-pos-h, item_width, h);
			if (rect.contains(event->pos()))
			{
				manager->pop(item);
				it = items.erase(it);
			}
			else
				it++;
		}
	}
	if (event->button()==Qt::MidButton)
	{
		manager->setSpacing(30);
	}
	update();
}

void StackView::itemUpdated(StackManager::Item)
{
	update();
}
