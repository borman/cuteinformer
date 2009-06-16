#ifndef NOTIFY_ADMIN_H
#define NOTIFY_ADMIN_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

#include "widgetstack.h"

class NotifyAdmin: public QWidget
{
	Q_OBJECT
	public:
		NotifyAdmin(QWidget *parent = NULL);
	private slots:
		void commitNotification();
	private:
		WidgetStack stack;
		
		QLineEdit w_title;
		QLineEdit w_icon;
		QTextEdit w_body;
};

#endif // NOTIFY_ADMIN_H
