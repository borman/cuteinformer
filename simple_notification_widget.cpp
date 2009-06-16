#include "simple_notification_widget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

SimpleNotificationWidget::SimpleNotificationWidget(QWidget *parent)
	: AbstractNotificationWidget(parent)
{		
	QHBoxLayout *layout = new QHBoxLayout(this);
	QLabel *label = new QLabel("Notification", this);
	layout->addWidget(label);
}

void SimpleNotificationWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button()==Qt::LeftButton || event->button()==Qt::RightButton)
		close();
}
