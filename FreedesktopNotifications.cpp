#include "FreedesktopNotifications.h"

#include "NotificationWidget.h"

#include <QtDBus>
#include <QDebug>

FreedesktopNotifications::FreedesktopNotifications(QObject *parent)
	: QObject(parent),
		stack(this), counter(0)
{
	QDBusConnection connection = QDBusConnection::sessionBus();
	connection.registerObject("/org/freedesktop/Notifications", this, 
														 QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals);
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
	if (hints.contains("urgency") && hints["urgency"].canConvert(QVariant::Int))
		switch (hints["urgency"].toInt())
		{
			case 0:
				urgency = NotificationWidget::Low;
				break;
			case 2:
				urgency = NotificationWidget::Critical;
				break;	
		}
	
	QString category = QString::null;
	if (hints.contains("category") && hints["category"].type()==QVariant::String)
		category = hints["category"].toString();
		
	
	if (expire_timeout<0)
	{
		switch (urgency)
		{
			case NotificationWidget::Low:
				expire_timeout = 2000;
				break;
			case NotificationWidget::Normal:
				expire_timeout = 10000;
				break;
			case NotificationWidget::Critical:
				expire_timeout = 120000;
				break;
		}
	}
	
	NotificationWidget *w = new NotificationWidget(urgency, category, summary, body, app_icon, expire_timeout);
	w->resize(w->sizeHint());
	stack.push(w);
	
	quint32 id = ++counter;
	map[id] = w;
	rmap[w] = id;
	connect(w, SIGNAL(closed(int)), SLOT(closed(int)));
	connect(w, SIGNAL(destroyed(QObject *)), SLOT(destroyed(QObject *)));
		
	return id;
}

void FreedesktopNotifications::CloseNotification(quint32 id)
{
	NotificationWidget *w = qobject_cast<NotificationWidget *>(map[id]);
	if (!w)
		return;
	w->closeNotification(NotificationWidget::ByMessage);
}

void FreedesktopNotifications::GetServerInformation(QString &name, QString &vendor, QString &version)
{
	name = "cuteinformer";
	vendor = "borman";
	version = "0.1";
}

//-------------- Internal methods

void FreedesktopNotifications::closed(int reason_code)
{
	NotificationWidget *w = qobject_cast<NotificationWidget *>(sender());
	if (!w)
		return;
	quint32 id = rmap[w];
	quint32 reason = 4; // Undefined
	switch (reason_code)
	{
		case NotificationWidget::Timeout:
			reason = 1;
			break;
		case NotificationWidget::UserAction:
			reason = 2;
			break;
		case NotificationWidget::ByMessage:
			reason = 3;
			break;
	}
	map.remove(id);
	rmap.remove(w);
	emit NotificationClosed(id, reason);
}

void FreedesktopNotifications::destroyed(QObject *o)
{
	NotificationWidget *w = qobject_cast<NotificationWidget *>(o);
	if (w && rmap.contains(w))
	{
		map.remove(rmap[w]);
		rmap.remove(w);
	}
}
