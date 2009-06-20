#ifndef NOTIFICATION_WIDGET_H
#define NOTIFICATION_WIDGET_H

#include "AbstractNotificationWidget.h"

#include <QPixmap>
#include <QTimer>
#include <QFrame>
#include <QLabel>

/**
	Actual notification widget
	For description on properties see Notification specs at 
	http://www.galago-project.org/specs/notification/0.9/index.html
	
	\todo Do something with word-wrapping in body (though it's strange to have very long words)
	
	\todo Think about hover behaviour: Ubuntu Notify-OSD guidelines advice to make a notification
	more transparent and click-through on hover, while some other implementations freeze timeout timer
	for all notifications shown until mouse pointer is moved away
**/
class NotificationWidget: public AbstractNotificationWidget
{
	Q_OBJECT
	Q_ENUMS(Urgency)
	
	// Selector properties
	Q_PROPERTY(Urgency urgency READ urgency)
	Q_PROPERTY(QString urgencyString READ urgencyString) // For StyleSheet convenience (enums seem to be broken there)
	Q_PROPERTY(QString category READ category)
	Q_PROPERTY(QString contents READ contents)
	
	// Data properties
	Q_PROPERTY(QString title READ title)
	Q_PROPERTY(QString body READ body)
	Q_PROPERTY(QPixmap icon READ icon)
	Q_PROPERTY(int timeout READ timeout)
	public:
		enum Urgency
		{
			Low,
			Normal,
			Critical
		};
		enum CloseReason
		{
			Timeout,
			UserAction,
			ByMessage
		};
		
		/**
			Urgency and category are properties that specify notification's class,
			so they may be used as selectors in style sheet and they must be provided to constructor.
			Other properties' data is ard to classify, so they are supplied later.
			**/
		NotificationWidget(Urgency urgency = Normal, const QString &category = QString::null,
												const QString &title = QString::null, const QString &body = QString::null,
												const QPixmap &icon = QPixmap(), int timeout = 0);
		
		Urgency urgency() const { return m_urgency; }
		QString urgencyString() const;
		QString category() const { return m_category; }
		QString title() const { return m_title; }
		QString body() const { return m_body; }
		QPixmap icon() const {return m_icon; }
		/**
			Timeout in milliseconds before hiding
			**/
		int timeout() const { return m_timeout; }
		
		/**
			Notification contents state. It is in form "[i][t][b]", where "i" is for icon,
			"t" is for title and "b" is for body, e.g. "i" means that only an icon is present
			and "it" means an icon and a title without a body
			**/
		QString contents() const {return m_contents_code; }
	signals:
		void closed(NotificationWidget *);
	private slots:
		void expired();
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
		
		QString m_contents_code;
		
		QLabel w_title;
		QLabel w_icon;
		QLabel w_body;
};

#endif // NOTIFICATION_WIDGET_H
