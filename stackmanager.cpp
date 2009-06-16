#include "stackmanager.h"

#include <QList>
#include <QMap>
#include <QTimer>
#include <QTime>
#include <QDebug>

#include <cmath>

struct StackManagerPrivate
{
	struct ItemData
	{
		StackManager::Item id;
		StackManager::Metric height;
		StackManager::Metric position;
		StackManager::Metric speed; // pixels/sec
	};
	QList<ItemData> items;
	QMap<StackManager::Item, int> map;
	QTimer updateTimer;
	QTime timeDiff;
	StackManager::Item next_id;
	StackManager::Metric acceleration;
	StackManager::Metric spacing;
	
	StackManagerPrivate(StackManager *owner)
		: updateTimer(owner), next_id(0), acceleration(3000), spacing(10)
	{
	}
};

StackManager::StackManager(QObject *parent)
: QObject(parent), d(new StackManagerPrivate(this))
{
	connect(&d->updateTimer, SIGNAL(timeout()), SLOT(updatePositions()));
	d->updateTimer.setSingleShot(false);
	d->updateTimer.setInterval(1000/50);
}

StackManager::Metric StackManager::acceleration() const
{
	return d->acceleration;
}
void StackManager::setAcceleration(StackManager::Metric value)
{
	d->acceleration = value;
}

StackManager::Metric StackManager::spacing() const
{
	return d->spacing;
}

void StackManager::setSpacing(StackManager::Metric value)
{
	d->spacing = value;
	animate();
}

StackManager::Metric StackManager::bottom(StackManager::Item i) const
{
	int index = d->map[i];
	return d->items.at(index).position;
}

StackManager::Metric StackManager::height(StackManager::Item i) const
{
	int index = d->map[i];
	return d->items.at(index).height;
}

StackManager::Metric StackManager::totalHeight() const
{
	const StackManagerPrivate::ItemData &top = d->items.last();
	return top.position+top.height;
}

StackManager::Item StackManager::push(StackManager::Metric h)
{
	Item item = d->next_id++;
	d->map[item] = d->items.count();
	
	StackManagerPrivate::ItemData item_data;
	item_data.id = item;
	item_data.height = h;
	if (d->items.isEmpty())
		item_data.position = 0;
	else
	{
		const StackManagerPrivate::ItemData &top = d->items.last();
		item_data.position = top.position+top.height+d->spacing;
	}
	item_data.speed = 0;
	d->items.append(item_data);
	
	return item;
}

void StackManager::pop(StackManager::Item item)
{
	QMap<Item, int>::iterator m_i = d->map.find(item);
	if (m_i==d->map.end())
		return;
	d->items.removeAt(m_i.value());
	m_i = d->map.erase(m_i);
	for (; m_i!=d->map.end(); m_i++)
		m_i.value()--;
	
	animate();
}

inline qreal sgn(qreal x)
{
	return (x<0)?-1:1;
}

void StackManager::updatePositions()
{
	bool need_actions = false;
	qreal dt = d->timeDiff.restart()/1000.0;
	
	for (QList<StackManagerPrivate::ItemData>::iterator item = d->items.begin(), prev_item;
				item!=d->items.end(); prev_item = item, item++)
	{		
		Metric dest = item==d->items.begin()? 0 : (prev_item->position + prev_item->height + d->spacing);
		Metric pos = item->position;
		Metric speed = item->speed;
		Metric accel = d->acceleration;
		
		Metric new_pos = pos + item->speed * dt;
		
		if (fabs(pos-dest)<0.1 || (dest-pos)*(new_pos-dest)>=0) // no need to move or has arrived
		{
			if (fabs(item->position - dest)>1e-3) // moved, though slightly
			{
				item->position = dest;
				item->speed = 0;
				emit updated(item->id);
			}
			continue;
		}

		need_actions = true;
		if (sgn(speed)!=sgn(dest-pos))
			speed -= sgn(speed)*accel*dt; // reverse
		else 
		{
			if (fabs(dest-pos)*2*accel<speed*speed)
				speed -= sgn(speed)*accel*dt; // deccel
			else
				speed += sgn(speed)*accel*dt; // accel
		}
		item->position = new_pos;
		item->speed = speed;
		
		emit updated(item->id);
	}
	if (!need_actions)
		d->updateTimer.stop();
}

void StackManager::animate()
{
	d->timeDiff.start();
	if (!d->updateTimer.isActive())
		d->updateTimer.start();
}
