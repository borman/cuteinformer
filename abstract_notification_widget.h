#ifndef ABSTRACT_NOTIFICATION_WIDGET_H
#define ABSTRACT_NOTIFICATION_WIDGET_H

#include <QFrame>

class AbstractNotificationWidget: public QFrame
{
	Q_OBJECT
	public:
		AbstractNotificationWidget(QWidget *parent = NULL);
	signals:
		void popFromStack(QWidget *);
	protected:
		void closeEvent(QCloseEvent *);
};

#endif // ABSTRACT_NOTIFICATION_WIDGET_H

