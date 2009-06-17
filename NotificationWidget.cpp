#include "NotificationWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

NotificationWidget::NotificationWidget(NotificationWidget::Urgency urgency, const QString &category)
	: AbstractNotificationWidget(),
		m_urgency(urgency), m_category(category),
		w_title(this), w_icon(this), w_body(this)
{	
	qDebug() << "Notification(" << urgency << category << ")";
	
	setObjectName("Notification");
	
	w_title.setObjectName("Title");
	
	w_icon.setObjectName("Icon");
	
	w_body.setObjectName("Body");
	w_body.setWordWrap(true);
	
#if 0
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(&w_title);
	QHBoxLayout *bodyLayout = new QHBoxLayout;
	bodyLayout->addWidget(&w_icon);
	bodyLayout->addWidget(&w_body);
	mainLayout->addLayout(bodyLayout);
#else
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(&w_icon);
	QVBoxLayout *bodyLayout = new QVBoxLayout;
	bodyLayout->addWidget(&w_title);
	bodyLayout->addWidget(&w_body);
	mainLayout->addLayout(bodyLayout);
#endif
	
	setTitle(QString::null);
	setBody(QString::null);
	setIcon(QPixmap());
	setTimeout(0);
}

void NotificationWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button()==Qt::LeftButton || event->button()==Qt::RightButton)
		closeNotification(UserAction);
}

void NotificationWidget::notificationShown()
{
	if (m_timeout>0)
		QTimer::singleShot(m_timeout, this, SLOT(expired()));
}

void NotificationWidget::expired()
{
	closeNotification(Timeout);
}

void NotificationWidget::setTitle(const QString &str)
{
	m_title = str;
	if (m_title.isEmpty())
		w_title.hide();
	else
	{
		w_title.setText(m_title);
		w_title.show();
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

void NotificationWidget::setTimeout(int timeout)
{
	m_timeout = timeout;
}
