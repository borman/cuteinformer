#include "dbus_interface.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	QFile qss("style.qss");
	if (qss.exists())
	{
		qss.open(QIODevice::ReadOnly);
		QTextStream ts(&qss);
		app.setStyleSheet(ts.readAll());
		qss.close();
	}
	
	FreedesktopNotifications noti;
	Q_UNUSED(noti);
	app.setQuitOnLastWindowClosed(false);
	
	qDebug() << argv[0] << "started!";
	return app.exec();
}
