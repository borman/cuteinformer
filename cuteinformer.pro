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
  src/StackManager.h \
  src/WidgetStack.h \
  src/AbstractNotificationWidget.h \
  src/NotificationWidget.h \
  src/FreedesktopNotifications.h \
  src/ThemeManager.h \
  src/Settings.h \
  src/DBusApplicationAdapter.h \
  src/KNotify.h
SOURCES += \
  src/main.cpp \
  src/StackManager.cpp \
  src/WidgetStack.cpp \
  src/AbstractNotificationWidget.cpp \
  src/NotificationWidget.cpp \
  src/FreedesktopNotifications.cpp \
  src/ThemeManager.cpp \
  src/Settings.cpp \
  src/DBusApplicationAdapter.cpp \
  src/KNotify.cpp
