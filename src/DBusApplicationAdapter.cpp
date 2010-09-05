#include "DBusApplicationAdapter.h"
#include "Settings.h"

#include <QApplication>
#include <QtDebug>

DBusApplicationAdapter::DBusApplicationAdapter()
	: QDBusAbstractAdaptor(qApp)
{
}

void DBusApplicationAdapter::Quit()
{
	qDebug() << "Exit requested";
	qApp->quit();
}

void DBusApplicationAdapter::ShowSettingsDialog()
{
	qDebug() << "Requested to show settings dialog";
	Settings::instance()->showDialog();
}

void DBusApplicationAdapter::ReloadSettings()
{
	qDebug() << "Requested to reload settings";
	Settings::instance()->reload();
}
