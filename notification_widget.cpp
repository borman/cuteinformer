#include "notification_widget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

NotificationWidget::NotificationWidget(QWidget *parent)
	: AbstractNotificationWidget(parent),
		w_title(this), w_underTitle(this), w_icon(this), w_body(this)
{	
	setObjectName("Notification");
	
	w_title.setObjectName("Title");
	
	w_underTitle.setObjectName("UnderTitle");
	w_underTitle.setFrameStyle(QFrame::HLine);
	
	w_icon.setObjectName("Icon");
	
	w_body.setObjectName("Body");
	w_body.setWordWrap(true);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(&w_title);
	mainLayout->addWidget(&w_underTitle);
	QHBoxLayout *bodyLayout = new QHBoxLayout;
	bodyLayout->addWidget(&w_icon);
	bodyLayout->addStretch();
	bodyLayout->addWidget(&w_body);
	mainLayout->addLayout(bodyLayout);
	
	setTitle(QString::null);
	setBody(QString::null);
	setIcon(QPixmap());
	setUrgency(Normal);
	setTimeout(0);
}

void NotificationWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button()==Qt::LeftButton || event->button()==Qt::RightButton)
		close();
}

void NotificationWidget::setTitle(const QString &str)
{
	m_title = str;
	if (m_title.isEmpty())
	{
		w_title.hide();
		w_underTitle.hide();
	}
	else
	{
		w_title.setText(m_title);
		w_title.show();
		w_underTitle.show();
	}
}
		
void NotificationWidget::setBody(const QString &str)
{
	m_body = str;
	if (m_body.isEmpty())
		w_body.hide();
	else
	{
		w_body.setText(m_body);
		w_body.show();
	}
}

void NotificationWidget::setIcon(const QPixmap &icon)
{
	m_icon = icon;
	if (m_icon.isNull())
		w_icon.hide();
	else
	{
		w_icon.setPixmap(m_icon);
		w_icon.show();
	}
}

void NotificationWidget::setUrgency(Urgency u)
{
	m_urgency = u;
}

void NotificationWidget::setTimeout(int timeout)
{
	m_timeout = timeout;
	showTimer.setInterval(m_timeout);
}
