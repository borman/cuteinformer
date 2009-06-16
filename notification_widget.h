#ifndef NOTIFICATION_WIDGET_H
#define NOTIFICATION_WIDGET_H

#include "abstract_notification_widget.h"

#include <QPixmap>
#include <QTimer>
#include <QFrame>
#include <QLabel>

/**
	Actual notification widget
	For description on properties see Notification specs at 
	http://www.galago-project.org/specs/notification/0.9/index.html
**/
class NotificationWidget: public AbstractNotificationWidget
{
	Q_OBJECT
	Q_ENUMS(Urgency)
	Q_PROPERTY(QString title READ title WRITE setTitle)
	Q_PROPERTY(QString body READ body WRITE setBody)
	Q_PROPERTY(QPixmap icon READ icon WRITE setIcon)
	Q_PROPERTY(Urgency urgency READ urgency)
	Q_PROPERTY(int timeout READ timeout WRITE setTimeout)
	public:
		enum Urgency
		{
			Low,
			Normal,
			Critical
		};
		
		NotificationWidget(Urgency u = Normal);
		
		/**
			Notification title
			**/
		QString title() const { return m_title; }
		void setTitle(const QString &str);
		
		/**
			Notification body
			**/
		QString body() const { return m_body; }
		void setBody(const QString &str);
		
		/**
			Notification icon
			**/
		QPixmap icon() const {return m_icon; }
		void setIcon(const QPixmap &icon);
		
		/**
			Notification urgency
			**/
		Urgency urgency() const { return m_urgency; }
		
		/**
			Hide timeout in milliseconds
			**/
		int timeout() const { return m_timeout; }
		void setTimeout(int timeout);
	protected:
		void mousePressEvent(QMouseEvent *event);
		void notificationShown();
	private:
		QString m_title;
		QString m_body;
		QPixmap m_icon;
		Urgency m_urgency;
		int m_timeout;
		QTimer showTimer;
		
		QLabel w_title;
		QFrame w_underTitle;
		QLabel w_icon;
		QLabel w_body;
};

#endif // NOTIFICATION_WIDGET_H
