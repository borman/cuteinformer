#include "FreedesktopNotifications.h"
#include "ThemeManager.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QtDebug>

#include <cstring>
#include <cstdlib>

// Print a message and exit with code 1
void die(const QString &reason)
{
	QTextStream cout(stdout);
	cout << reason << '\n';
	cout.flush();
	exit(1);
}

void print_usage()
{
	QTextStream cout(stdout);
	cout << QObject::tr("--help    \t\tShow this information") << '\n';
	cout << QObject::tr("--debug   \t\tAllow debugging output") << '\n';
	cout << QObject::tr("--settings\t\tAsk a running instance to show settings dialog if it is running"
															"or show it and run a new instance otherwise") << '\n';
}


static QtMsgHandler default_msg_handler = NULL;
void no_debug_msg_handler(QtMsgType t, const char *msg) // This handler is used to suppress debug garbage
{
	if (!default_msg_handler)
		return;
	if (t!=QtDebugMsg)
		default_msg_handler(t, msg);
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	// Parse command line
	bool showSettings = false;
	bool noDebug = true;
	for (int i=1; i<argc; i++)
	{
		if (i==1 && !strcmp(argv[i], "--help"))
		{
			print_usage();
			return 0;
		}
		else if (!strcmp(argv[i], "--settings"))
			showSettings = true;
		else if (!strcmp(argv[i], "--debug"))
			noDebug = false;
		else die(QObject::tr("Invalid command line: type `%1 --help' for usage information").arg(argv[0]));
	}
	
	if (noDebug) // Suppress messages from qDebug()
		default_msg_handler = qInstallMsgHandler(no_debug_msg_handler);
	
	QDBusConnectionInterface *iface = QDBusConnection::sessionBus().interface();
	if (iface->isServiceRegistered("org.cuteinformer").value()) // Is another instance running?
	{
		if (showSettings) 
		{ // Ok, let that instance show settings dialog
			
		}
		else			
			die(QObject::tr("CuteInformer is already running with pid %1")
				.arg(iface->servicePid("org.cuteinformer")));
	}

	// Load a theme
	// TODO: theme must not be harcoded
	ThemeManager tman;
	QString comment;
	if (!tman.load("theme/index.theme", comment))
		qDebug() << "Theme load error:" << comment;
	else
		qDebug() << "Theme loaded ok";
	
	// Listen for D-Bus calls
	FreedesktopNotifications noti;
	Q_UNUSED(noti);
	app.setQuitOnLastWindowClosed(false);
	
	qDebug() << "cuteinformer started!";
	return app.exec();
}
