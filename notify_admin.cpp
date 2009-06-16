#include "notify_admin.h"
#include "notification_widget.h"

#include <QFormLayout>
#include <QPushButton>

NotifyAdmin::NotifyAdmin(QWidget *parent)
	: QWidget(parent), stack(this),
		w_title(this), w_icon(this), w_body(this)
{
	QFormLayout *layout = new QFormLayout(this);
	
	QPushButton *addButton = new QPushButton(tr("Show!"), this);
	
	layout->addRow(tr("Title"), &w_title);
	layout->addRow(tr("Icon"), &w_icon);
	layout->addRow(tr("Body"), &w_body);
	layout->addRow(addButton);
	
	connect(addButton, SIGNAL(clicked()), SLOT(commitNotification()));
}

void NotifyAdmin::commitNotification()
{
	NotificationWidget *w = new NotificationWidget();
	w->setTitle(w_title.text());
	w->setIcon(w_icon.text().isEmpty()?QPixmap():QPixmap(w_icon.text()));
	w->setBody(w_body.toPlainText());
	w->setFixedSize(w->sizeHint());
	stack.push(w);
}
