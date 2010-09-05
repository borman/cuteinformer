#include "FreedesktopNotifications.h"
#include "KNotify.h"
#include "Settings.h"
#include "DBusApplicationAdapter.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusError>
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
	cout << QObject::tr("--help           Show this information") << '\n';
	cout << QObject::tr("--debug          Allow debugging output") << '\n';
	cout << QObject::tr("--settings       Show settings dialog. If the daemon is running, ask it "
																				"or start a new instance otherwise") << '\n';
}


static QtMsgHandler default_msg_handler = NULL;
void no_debug_msg_handler(QtMsgType t, const char *msg) // This handler is used to suppress debug garbage
{
	if (default_msg_handler!=NULL && t!=QtDebugMsg)
		default_msg_handler(t, msg);
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName("cuteinformer");
	QCoreApplication::setOrganizationName("cuteinformer");
	
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
			qDebug() << "Asking to show settings via D-Bus...";
			QDBusInterface iface("org.cuteinformer", "/Application", "org.cuteinformer.Application");
			QDBusReply<void> reply = iface.call("ShowSettingsDialog");
			if (reply.isValid())
				return 0;
			else
				die(QObject::tr("Error %1: \"%2\"")
						.arg(reply.error().name())
						.arg(reply.error().message()));
		}
		else			
			die(QObject::tr("CuteInformer is already running with pid %1")
				.arg(iface->servicePid("org.cuteinformer")));
	}
	
	//============================
	// Everything ok, start server
	
	qDebug() << "Starting server.";
	
	qDebug() << "Registering application service...";
	if (!QDBusConnection::sessionBus().registerService("org.cuteinformer"))
		die(QObject::tr("Unable to register application service"));
	
	qDebug() << "Registering Freedesktop notifications service...";
	if (!QDBusConnection::sessionBus().registerService("org.freedesktop.Notifications"))
		die(QObject::tr("Unable to register Freedesktop notifications service"));

  qDebug() << "Registering KDE notifications service...";
	if (!QDBusConnection::sessionBus().registerService("org.kde.knotify"))
		die(QObject::tr("Unable to register KDE notifications service"));

	
	qDebug() << "Starting application adapter...";
	new DBusApplicationAdapter;
	if (!QDBusConnection::sessionBus().registerObject("/Application", qApp))
		die(QObject::tr("Unable to register application interface"));
	
	qDebug() << "Loading settings...";
	Settings::instance(); // Load settings
	if (showSettings)
		Settings::instance()->showDialog();

	// Listen for D-Bus calls
	qDebug() << "Starting Freedesktop notifications interface...";
	FreedesktopNotifications freedesktop_notify(qApp);
	if (!QDBusConnection::sessionBus().registerObject("/org/freedesktop/Notifications", 
        &freedesktop_notify, 
        QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals))
		die(QObject::tr("Unable to register Freedesktop notifications interface"));

  qDebug() << "Starting KDE notifications interface...";
  KNotify kde_notify(qApp);
  if (!QDBusConnection::sessionBus().registerObject("/Notify", 
        &kde_notify, 
        QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals))
		die(QObject::tr("Unable to register KDE notifications interface"));

	
	qDebug() << "Server started!";
	
	app.setQuitOnLastWindowClosed(false);
	int ret = app.exec();
	qDebug() << "Event loop ended";
	
	// BUG: something weird happening at this point as everything hangs
	
	return ret;
}
