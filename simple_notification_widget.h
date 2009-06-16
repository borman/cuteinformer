#ifndef SIMPLE_NOTIFICATION_WIDGET_H
#define SIMPLE_NOTIFICATION_WIDGET_H

#include "abstract_notification_widget.h"

class SimpleNotificationWidget: public AbstractNotificationWidget
{
	Q_OBJECT
	public:
		SimpleNotificationWidget(QWidget *parent = NULL);
	protected:
		void mousePressEvent(QMouseEvent *event);
};

#endif // SIMPLE_NOTIFICATION_WIDGET_H
