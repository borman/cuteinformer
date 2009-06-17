#include "FreedesktopNotifications.h"
#include "ThemeManager.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	ThemeManager tman;
	QString comment;
	if (!tman.load("theme/index.theme", comment))
		qDebug() << "Theme load error:" << comment;
	else
		qDebug() << "Theme loaded ok";
	
	FreedesktopNotifications noti;
	Q_UNUSED(noti);
	app.setQuitOnLastWindowClosed(false);
	
	qDebug() << argv[0] << "started!";
	return app.exec();
}
