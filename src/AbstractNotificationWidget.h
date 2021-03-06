#ifndef ABSTRACT_NOTIFICATION_WIDGET_H
#define ABSTRACT_NOTIFICATION_WIDGET_H

#include <QFrame>
#include <QTimeLine>

/**
	Abstract notification widget. It is not intended for actual use,
	though it defines some common interface and behaviour.
	
	\todo Separate notification interface from animation engine
**/
class AbstractNotificationWidget: public QFrame
{
	Q_OBJECT
	public:
		AbstractNotificationWidget();
	signals:
		void popFromStack(AbstractNotificationWidget *);
		void closed(int reason_code);
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
			Also, reports close reason \a reason_code through closed() signal
			**/
		void closeNotification(int reason_code);
	private slots:
		void sliding(qreal);
		void slideFinished();
	protected:
		/** 
			Reimplement this in a subclass to do something when the notification
			is shown and ready (e.g. show animation has ended)
			**/
		virtual void notificationShown() {};
		/** 
			Reimplement it in a subclass to do something before closing is started
			**/
		virtual void notificationClosing() {};
	private:
		bool is_showing;
		int m_position;
		QTimeLine slide;
};

#endif // ABSTRACT_NOTIFICATION_WIDGET_H

