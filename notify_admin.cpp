#include "notify_admin.h"
#include "simple_notification_widget.h"

#include <QFormLayout>
#include <QPushButton>

NotifyAdmin::NotifyAdmin(QWidget *parent)
	: QWidget(parent), stack(this)
{
	QFormLayout *layout = new QFormLayout(this);
	
	QPushButton *addButton = new QPushButton(tr("Show!"), this);
	
	layout->addRow(addButton);
	
	connect(addButton, SIGNAL(clicked()), SLOT(commitNotification()));
}

void NotifyAdmin::commitNotification()
{
	SimpleNotificationWidget *w = new SimpleNotificationWidget();
	w->setFixedSize(w->sizeHint());
	stack.pushWidget(w);
}
