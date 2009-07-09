#ifndef FREEDESKTOP_NOTIFICATIONS_H
#define FREEDESKTOP_NOTIFICATIONS_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QString>
#include <QStringList>

#include "WidgetStack.h"

class NotificationWidget;
class FreedesktopNotifications: public QObject
{
	Q_OBJECT
	Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
	public:
		FreedesktopNotifications(QObject *parent = NULL);
	signals:
		/* org.freedesktop.Notifications.NotificationClosed (UINT32 id, UINT32 reason); */
		void NotificationClosed(quint32 id, quint32 reason);
	public slots:
		/* STRING_ARRAY org.freedesktop.Notifications.GetCapabilities (void); */
		QStringList GetCapabilities();
		
		/* UINT32 org.freedesktop.Notifications.Notify (
					STRING app_name, UINT32 replaces_id, 
					STRING app_icon, STRING summary, 
					STRING body, ARRAY actions, 
					DICT hints, INT32 expire_timeout);
					*/
		quint32 Notify(const QString &app_name, quint32 replaces_id, 
										const QString &app_icon, const QString &summary,
										const QString &body, const QStringList &actions,
										const QVariantMap &hints, qint32 expire_timeout);
		
		/* void org.freedesktop.Notifications.CloseNotification (UINT32 id); */
		void CloseNotification(quint32 id);
		
		/* void org.freedesktop.Notifications.GetServerInformation (out STRING name, out STRING vendor,
								out STRING version, out STRING spec_version); */
		// Though spec_version is not mentioned in specifications, notification-daemon supplies it
		// and some apps already rely on it
		void GetServerInformation(QString &name, QString &vendor, QString &version, QString &spec_version);
	private slots:
		void closed(int reason_code);
		void destroyed(QObject *o);
	private:
		WidgetStack stack;
		quint32 counter;
		QMap<quint32, NotificationWidget *> map;
		QMap<NotificationWidget *, quint32> rmap;
};

#endif // FREEDESKTOP_NOTIFICATIONS_H
