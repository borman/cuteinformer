#include "abstract_notification_widget.h"

AbstractNotificationWidget::AbstractNotificationWidget(QWidget *parent)
	: QFrame(parent)
{
	setFrameStyle(QFrame::Raised | QFrame::StyledPanel);
	
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
