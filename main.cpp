#include "stackmanager.h"
#include "stackview.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	StackView view;
	view.setGeometry(1000, 40, 280, 700);
	view.show();
	
	return app.exec();
}
