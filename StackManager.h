#ifndef STACKMANAGER_H
#define STACKMANAGER_H

#include <QObject>

struct StackManagerPrivate;

/**
	A class that manages an animated stack of items. Each item has its own height and all items 
	are placed with fixed distance between them. After any item is removed, other items are moved
	to their desired places smoothly.
	
	\todo Add bouncing feedback to animation.
	**/
class StackManager: public QObject
{
	Q_OBJECT
	public:
		typedef quint32 Item;
		typedef qreal Metric;
	
		StackManager(QObject *parent = NULL);
		virtual ~StackManager();
		
		/**
			Item's acceleration when animating. Unit is pixel/sec^2. 
			Default value is 3000 as it seems to be good enough.
			**/
		Metric acceleration() const;
		/**
			Set item's acceleration.
			**/
		void setAcceleration(Metric value);
		
		/**
			Items are placed at distance \a spacing between each other.
			**/
		Metric spacing() const;
		/**
			Set items' spacing
			**/
		void setSpacing(Metric value);
		
		/**
			Get bottom coordinate of item \a i. Top coordinate is <pre>bottom+height</pre>
			**/
		Metric bottom(Item i) const;
		
		/**
			Get height for item \a i
			**/
		Metric height(Item i) const;
		/** 
			Get total stack height
			*/		
		Metric totalHeight() const;
		
		/**
			Add an item with height \a h to top.
			\return new item's index
			**/
		Item push(Metric h);
		/**
			Remove item \a item
			**/
		void pop(Item item);
	signals:
		/**
			Emitted whenever item's position is updated
			**/
		void updated(StackManager::Item i);
		
	protected:
		void timerEvent(QTimerEvent *);
	private:
		/**
			\internal
			Start animation if not running.
			**/
		void animate();
		/**
			\internal
			Stop animation if running
			**/
		void stopAnimation();
		
	private:
	StackManagerPrivate *d;
};

#endif // STACKMANAGER_H
