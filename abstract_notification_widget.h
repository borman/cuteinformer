#ifndef ABSTRACT_NOTIFICATION_WIDGET_H
#define ABSTRACT_NOTIFICATION_WIDGET_H

#include <QFrame>

/**
	Abstract notification widget. It is not intended for actual use,
	though it defines some common interface and behaviour.
**/
class AbstractNotificationWidget: public QFrame
{
	Q_OBJECT
	public:
		AbstractNotificationWidget(QWidget *parent = NULL);
	signals:
		void popFromStack(AbstractNotificationWidget *);
	public slots:
		/**
			Place the notification at specified position relative to anchor
			**/
		void setPosition(int position);
		/**
			Use this rather than QWidget::show() to show the notification
			with proper look-and-feel and callbacks
			**/
		void showNotification();
		/**
			Use this rather than QWidget::close() to close the notification
			with proper look-and-feel and callbacks
			**/
		void closeNotification();
	protected:
		void closeEvent(QCloseEvent *);
		void showEvent(QShowEvent *);
		
		/** 
			Reimplement this in a subclass to do something when the notification
			is shown and ready (e.g. show animation has ended)
			**/
		virtual void notificationShown() {};
		/** 
			Reimplement it in a subclass to do something before closing is started
			**/
		virtual void notificationClosing() {};
};

#endif // ABSTRACT_NOTIFICATION_WIDGET_H

