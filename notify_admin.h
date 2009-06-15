#ifndef NOTIFY_ADMIN_H
#define NOTIFY_ADMIN_H

#include <QWidget>

#include "widgetstack.h"

class NotifyAdmin: public QWidget
{
	Q_OBJECT
	public:
		NotifyAdmin(QWidget *parent = NULL);
	private slots:
		void commitNotification();
	private:
		WidgetStack stack;
};

#endif // NOTIFY_ADMIN_H
