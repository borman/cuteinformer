#include "abstract_notification_widget.h"

#include <QApplication>
#include <QDesktopWidget>

AbstractNotificationWidget::AbstractNotificationWidget(QWidget *parent)
	: QFrame(parent)
{
	setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setAttribute(Qt::WA_X11NetWmWindowTypeNotification, true);
	
	setFocusPolicy(Qt::NoFocus);
}

void AbstractNotificationWidget::closeEvent(QCloseEvent *)
{
	emit popFromStack(this);
}

void AbstractNotificationWidget::showEvent(QShowEvent *)
{
	notificationShown();
}

void AbstractNotificationWidget::closeNotification()
{
	notificationClosing();
	close();
}

void AbstractNotificationWidget::showNotification()
{
	show();
}

void AbstractNotificationWidget::setPosition(int position)
{
	QPoint dest = QApplication::desktop()->availableGeometry(this).bottomRight()
						   +QPoint(-width()+1, -height()-position);
	move(dest);
}
