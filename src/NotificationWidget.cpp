#include "NotificationWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

NotificationWidget::NotificationWidget(NotificationWidget::Urgency urgency, const QString &category,
												const QString &title, const QString &body, const QPixmap &icon, int timeout)
	: AbstractNotificationWidget(),
		m_urgency(urgency), m_category(category), m_title(title),
		m_body(body), m_icon(icon), m_timeout(timeout),
		m_contents_code(""),
		w_title(this), w_icon(this), w_body(this)
{
	setObjectName("Notification");

	w_title.setObjectName("Title");
	w_title.setTextFormat(Qt::PlainText);

	w_icon.setObjectName("Icon");

	w_body.setObjectName("Body");
	w_body.setWordWrap(true);
	w_body.setTextFormat(Qt::RichText); // FIXME: Well, this is not totally correct though it's simple

	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(&w_icon);
	QVBoxLayout *bodyLayout = new QVBoxLayout;
	bodyLayout->addWidget(&w_title);
	bodyLayout->addWidget(&w_body);
	bodyLayout->addStretch(); // push body up to touch title
	mainLayout->addLayout(bodyLayout);

	// Remove spacing: leave it to Style Sheet
	mainLayout->setContentsMargins(0, 0, 0, 0);
	bodyLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);
	bodyLayout->setSpacing(0);

	if (m_icon.isNull())
		w_icon.hide();
	else
	{
		w_icon.setPixmap(m_icon);
		m_contents_code += 'i';
	}

	if (m_title.isEmpty())
		w_title.hide();
	else
	{
		w_title.setText(m_title);
		m_contents_code += 't';
	}

	if (m_body.isEmpty())
		w_body.hide();
	else
	{
		w_body.setText(m_body);
		m_contents_code += 'b';
	}

	setIconAlignment("Center");
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

QString NotificationWidget::urgencyString() const
{
	switch (m_urgency)
	{
		case Low:
			return "Low";
		default:
		case Normal:
			return "Normal";
		case Critical:
			return "Critical";
	}
}

void NotificationWidget::setIconAlignment(QString v)
{
	v = v.trimmed().toLower();
	qDebug() << "Alignment" << v;

	Qt::AlignmentFlag q_v;
	if (v == "top")
		q_v = Qt::AlignTop;
	else if (v == "center")
		q_v = Qt::AlignVCenter;
	else if (v == "bottom")
		q_v = Qt::AlignBottom;
	else
	{
		qWarning() << tr("Invalid iconAlignment:") << v;
		return;
	}

	w_icon.setAlignment(Qt::AlignLeft | q_v);
	m_icon_alignment = v;
}

