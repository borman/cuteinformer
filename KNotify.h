#ifndef KNOTIFY_H_1256995486
#define KNOTIFY_H_1256995486

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

class FreedesktopNotifications;

/*
 * Adaptor class for interface org.kde.KNotify
 */
class KNotify: public QObject
{
  Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.KNotify")
    Q_CLASSINFO("D-Bus Introspection", ""
        "  <interface name=\"org.kde.KNotify\">\n"
        "    <signal name=\"notificationClosed\">\n"
        "      <arg direction=\"out\" type=\"i\" name=\"id\"/>\n"
        "    </signal>\n"
        "    <signal name=\"notificationActivated\">\n"
        "      <arg direction=\"out\" type=\"i\" name=\"id\"/>\n"
        "      <arg direction=\"out\" type=\"i\" name=\"action\"/>\n"
        "    </signal>\n"
        "    <method name=\"reconfigure\"/>\n"
        "    <method name=\"closeNotification\">\n"
        "      <arg direction=\"in\" type=\"i\" name=\"id\"/>\n"
        "    </method>\n"
        "    <method name=\"event\">\n"
        "      <arg direction=\"out\" type=\"i\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"event\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"fromApp\"/>\n"
        "      <arg direction=\"in\" type=\"av\" name=\"contexts\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"title\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"text\"/>\n"
        "      <arg direction=\"in\" type=\"ay\" name=\"pixmap\"/>\n"
        "      <arg direction=\"in\" type=\"as\" name=\"actions\"/>\n"
        "      <arg direction=\"in\" type=\"x\" name=\"winId\"/>\n"
        "    </method>\n"
        "    <method name=\"update\">\n"
        "      <arg direction=\"in\" type=\"i\" name=\"id\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"title\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"text\"/>\n"
        "      <arg direction=\"in\" type=\"ay\" name=\"pixmap\"/>\n"
        "      <arg direction=\"in\" type=\"as\" name=\"actions\"/>\n"
        "    </method>\n"
        "    <method name=\"reemit\">\n"
        "      <arg direction=\"in\" type=\"i\" name=\"id\"/>\n"
        "      <arg direction=\"in\" type=\"av\" name=\"contexts\"/>\n"
        "    </method>\n"
        "  </interface>\n"
        "")
  public:
        KNotify(QObject *parent);
        virtual ~KNotify();

        public slots: 
          void closeNotification(int id);
        int event(const QString &event, const QString &fromApp, const QVariantList &contexts, const QString &title, const QString &text, const QByteArray &pixmap, const QStringList &actions, qlonglong winId);
        void reconfigure();
        void reemit(int id, const QVariantList &contexts);
        void update(int id, const QString &title, const QString &text, const QByteArray &pixmap, const QStringList &actions);
signals: 
        void notificationActivated(int id, int action);
        void notificationClosed(int id);

private:
        FreedesktopNotifications *proxy;
};

#endif
