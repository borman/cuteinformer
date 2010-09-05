#ifndef DBUS_APPLICATION_ADAPTER_H
#define DBUS_APPLICATION_ADAPTER_H

#include <QDBusAbstractAdaptor>

class DBusApplicationAdapter: public QDBusAbstractAdaptor
{
	Q_OBJECT
	Q_CLASSINFO("D-Bus Interface", "org.cuteinformer.Application")
	public:
		DBusApplicationAdapter();
	public slots:
		Q_NOREPLY void Quit();
		Q_NOREPLY void ShowSettingsDialog();
		Q_NOREPLY void ReloadSettings();
};

#endif // DBUS_APPLICATION_ADAPTER_H
