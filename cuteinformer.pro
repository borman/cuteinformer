TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += \
	stackmanager.h \
	widgetstack.h \
	abstract_notification_widget.h \
	simple_notification_widget.h \
	notify_admin.h
	
SOURCES +=  \
	main.cpp \
	stackmanager.cpp \
	widgetstack.cpp \
	abstract_notification_widget.cpp \
	simple_notification_widget.cpp \
	notify_admin.cpp
