#ifndef DBUS_INTERFACE_H
#define DBUS_INTERFACE_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QString>
#include <QStringList>

#include "widgetstack.h"

class FreedesktopNotifications: public QObject
{
	Q_OBJECT
	Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
	public:
		FreedesktopNotifications(QObject *parent = NULL);
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
		
		/* void org.freedesktop.Notifications.GetServerInformation (out STRING name, out STRING vendor, out STRING version); */
		
	private:
		WidgetStack stack;
		quint32 counter;
};

#endif // DBUS_INTERFACE_H
