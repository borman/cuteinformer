#include "simple_notification_widget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

SimpleNotificationWidget::SimpleNotificationWidget(QWidget *parent)
	: AbstractNotificationWidget(parent)
{		
	QHBoxLayout *layout = new QHBoxLayout(this);
	QLabel *label = new QLabel("Notification", this);
	QPushButton *button = new QPushButton("X", this);
	button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
	layout->addWidget(label);
	layout->addWidget(button);
	connect(button, SIGNAL(clicked()), SLOT(close()));
}

void SimpleNotificationWidget::paintEvent(QPaintEvent *ev)
{
	QPainter p(this);
	p.fillRect(rect(), palette().background());
	AbstractNotificationWidget::paintEvent(ev);
}
