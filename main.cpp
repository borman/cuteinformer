#include "FreedesktopNotifications.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	// FIXME: this will be removed as soon as settings are implemented
	QDir::setSearchPaths("theme", QStringList("./theme")); 
	
	QFile qss("theme:style.qss");
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
