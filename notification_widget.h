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
	
	// Selector properties
	Q_PROPERTY(Urgency urgency READ urgency)
	Q_PROPERTY(QString category READ category)
	
	// Data properties
	Q_PROPERTY(QString title READ title WRITE setTitle)
	Q_PROPERTY(QString body READ body WRITE setBody)
	Q_PROPERTY(QPixmap icon READ icon WRITE setIcon)
	Q_PROPERTY(int timeout READ timeout WRITE setTimeout)
	public:
		enum Urgency
		{
			Low,
			Normal,
			Critical
		};
		
		/**
			Urgency and category are properties that specify notification's class,
			so they may be used as selectors in style sheet and they must be provided to constructor.
			Other properties' data is ard to classify, so they are supplied later.
			**/
		NotificationWidget(Urgency urgency = Normal, const QString &category = QString::null);
		
		/**
			Notification urgency
			**/
		Urgency urgency() const { return m_urgency; }
		
		/**
			Notification category
			**/
		QString category() const { return m_category; }
		
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
			Hide timeout in milliseconds
			**/
		int timeout() const { return m_timeout; }
		void setTimeout(int timeout);
	protected:
		void mousePressEvent(QMouseEvent *event);
		void notificationShown();
	private:
		Urgency m_urgency;
		QString m_category;
		
		QString m_title;
		QString m_body;
		QPixmap m_icon;
		int m_timeout;
		
		QLabel w_title;
		QLabel w_icon;
		QLabel w_body;
};

#endif // NOTIFICATION_WIDGET_H
