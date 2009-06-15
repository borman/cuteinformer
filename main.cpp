#include "notify_admin.h"

#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	NotifyAdmin admin;
	admin.show();
	
	return app.exec();
}
