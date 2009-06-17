TEMPLATE = app
TARGET = cuteinformer
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += silent debug
QT += dbus

# Store generated files in subfolders
MOC_DIR = .moc
OBJECTS_DIR = .obj

# All source files
HEADERS += \
	stackmanager.h \
	widgetstack.h \
	abstract_notification_widget.h \
	notification_widget.h \
	dbus_interface.h
	
SOURCES += \
	main.cpp \
	stackmanager.cpp \
	widgetstack.cpp \
	abstract_notification_widget.cpp \
	notification_widget.cpp \
	dbus_interface.cpp
