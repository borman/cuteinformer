#include "notify_admin.h"
#include "notification_widget.h"

#include <QFormLayout>
#include <QPushButton>

NotifyAdmin::NotifyAdmin(QWidget *parent)
	: QWidget(parent), stack(this),
		w_title(this), w_icon(this), w_body(this), w_timeout(this), w_urgency(this)
{
	QFormLayout *layout = new QFormLayout(this);
	
	QPushButton *addButton = new QPushButton(tr("Show!"), this);
	
	w_urgency.addItems(QStringList() << "Normal" << "Low" << "High");
	w_timeout.setRange(0, 60000);
	w_timeout.setSingleStep(1000);
	
	layout->addRow(tr("Title"), &w_title);
	layout->addRow(tr("Icon"), &w_icon);
	layout->addRow(tr("Body"), &w_body);
	layout->addRow(tr("Timeout"), &w_timeout);
	layout->addRow(tr("Urgency"), &w_urgency);
	layout->addRow(addButton);
	
	w_title.setText("Title");
	w_body.setText("Body");
	
	connect(addButton, SIGNAL(clicked()), SLOT(commitNotification()));
}

void NotifyAdmin::commitNotification()
{
	NotificationWidget::Urgency us[3] = {NotificationWidget::Normal, NotificationWidget::Low, NotificationWidget::Critical};
	NotificationWidget *w = new NotificationWidget(us[w_urgency.currentIndex()]);
	w->setTitle(w_title.text());
	w->setIcon(w_icon.text().isEmpty()?QPixmap():QPixmap(w_icon.text()));
	w->setBody(w_body.toPlainText());
	w->setTimeout(w_timeout.value()); 
	w->resize(w->sizeHint());
	stack.push(w);
}
