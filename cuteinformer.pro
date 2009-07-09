TEMPLATE = app
TARGET = cuteinformer
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += silent
QT += dbus

# Store generated files in subfolders
MOC_DIR = .moc
OBJECTS_DIR = .obj

# All source files
HEADERS += \
	StackManager.h \
	WidgetStack.h \
	AbstractNotificationWidget.h \
	NotificationWidget.h \
	FreedesktopNotifications.h \
	ThemeManager.h \
	Settings.h \
	DBusApplicationAdapter.h
	
SOURCES += \
	main.cpp \
	StackManager.cpp \
	WidgetStack.cpp \
	AbstractNotificationWidget.cpp \
	NotificationWidget.cpp \
	FreedesktopNotifications.cpp \
	ThemeManager.cpp \
	Settings.cpp \
	DBusApplicationAdapter.cpp
