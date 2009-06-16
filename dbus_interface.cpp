#include "dbus_interface.h"

#include "notification_widget.h"

#include <QtDBus>
#include <QDebug>

FreedesktopNotifications::FreedesktopNotifications(QObject *parent)
	: QObject(parent),
		stack(this), counter(0)
{
	QDBusConnection connection = QDBusConnection::sessionBus();
	connection.registerObject("/org/freedesktop/Notifications", this, QDBusConnection::ExportAllSlots);
	connection.registerService("org.cuteinformer");
	connection.registerService("org.freedesktop.Notifications");
}

QStringList FreedesktopNotifications::GetCapabilities()
{
	return QStringList() << "body" << "body-hyperlinks" << "body-markup";
}

quint32 FreedesktopNotifications::Notify(const QString &app_name, quint32 replaces_id, 
								const QString &app_icon, const QString &summary,
								const QString &body, const QStringList &actions,
								const QVariantMap &hints, qint32 expire_timeout)
{
	qDebug() << "Notify request:" 
		<< app_name << replaces_id 
		<< app_icon << summary 
		<< body << actions 
		<< hints << expire_timeout;
		
	NotificationWidget::Urgency urgency = NotificationWidget::Normal;
	if (hints.contains("urgency"))
	{
		QVariant v_urg = hints["urgency"];
		if (v_urg.type()==QVariant::Int)
			switch (v_urg.toInt())
			{
				case 0:
					urgency = NotificationWidget::Low;
					break;
				case 2:
					urgency = NotificationWidget::Critical;
					break;	
			}
	}
	NotificationWidget *w = new NotificationWidget(urgency);
	w->setTitle(summary);
	w->setBody(body);
	w->setIcon(QPixmap(app_icon));
	w->setTimeout(expire_timeout);
	w->resize(w->sizeHint());
	stack.push(w);
		
	return ++counter;
}

void FreedesktopNotifications::CloseNotification(quint32 id)
{
}
