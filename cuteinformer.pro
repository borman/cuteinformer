TEMPLATE = app
TARGET = cuteinformer
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += silent debug

# Store generated files in subfolders
MOC_DIR = .moc
OBJECTS_DIR = .obj

# These sources are only for testing purposes, they should be removed in release
HEADERS_TEST = notify_admin.h
SOURCES_TEST = notify_admin.cpp

# All source files
HEADERS += $$HEADERS_TEST \
	stackmanager.h \
	widgetstack.h \
	abstract_notification_widget.h \
	notification_widget.h 
	
SOURCES +=  $$SOURCES_TEST \
	main.cpp \
	stackmanager.cpp \
	widgetstack.cpp \
	abstract_notification_widget.cpp \
	notification_widget.cpp 
