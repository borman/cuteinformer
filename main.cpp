#include "notify_admin.h"
#include "dbus_interface.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

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
	
	NotifyAdmin admin;
	admin.show();
	
	FreedesktopNotifications noti;
	Q_UNUSED(noti);
	
	return app.exec();
}
