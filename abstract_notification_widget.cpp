#include "abstract_notification_widget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>

AbstractNotificationWidget::AbstractNotificationWidget()
	: QFrame(),
		m_position(0), slide(100, this)
{
	setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setAttribute(Qt::WA_X11NetWmWindowTypeNotification, true);
	
	setFocusPolicy(Qt::NoFocus);
	
	slide.setCurveShape(QTimeLine::EaseOutCurve);
	slide.setUpdateInterval(1000/50);
	connect(&slide, SIGNAL(valueChanged(qreal)), SLOT(sliding(qreal)));
	connect(&slide, SIGNAL(finished()), SLOT(slideFinished()));
}

void AbstractNotificationWidget::closeEvent(QCloseEvent *)
{
	emit popFromStack(this);
}

void AbstractNotificationWidget::closeNotification()
{
	notificationClosing();
	is_showing = false;
	slide.setDirection(QTimeLine::Backward);
	slide.start();
}

void AbstractNotificationWidget::showNotification()
{
	show();
	is_showing = true;
	slide.setDirection(QTimeLine::Forward);
	slide.start();
}

void AbstractNotificationWidget::setPosition(int position)
{
	m_position = position;
	QPoint dest = QApplication::desktop()->availableGeometry(this).bottomRight()
						   +QPoint(-width()*slide.currentValue() +1, -height()-position);
	move(dest);
}

void AbstractNotificationWidget::sliding(qreal value)
{
	setPosition(m_position);
}

void AbstractNotificationWidget::slideFinished()
{
	if (is_showing)
	{
		is_showing = false;
		notificationShown();
	}
	else
		close();
}
