#include "KNotify.h"
#include "FreedesktopNotifications.h"

#include <QByteArray>
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariant>

  KNotify::KNotify(QObject *parent)
: QObject(parent)
{
  proxy = qApp->findChild<FreedesktopNotifications *>();
}

KNotify::~KNotify()
{
  // destructor
}

void KNotify::closeNotification(int id)
{
  // handle method call org.kde.KNotify.closeNotification
  proxy->CloseNotification(id);
}

int KNotify::event(const QString &event, const QString &fromApp, const QVariantList &contexts, const QString &title, const QString &text, const QByteArray &pixmap, const QStringList &actions, qlonglong winId)
{
  // handle method call org.kde.KNotify.event
  if (!proxy)
    return 0;

  qDebug() << "org.kde.KNotify.event:" << event << fromApp << contexts << title << text << actions << winId;

  return proxy->Notify(fromApp, 0, QString(), title, text, actions, QVariantMap(), -1);
}

void KNotify::reconfigure()
{
  // handle method call org.kde.KNotify.reconfigure
}

void KNotify::reemit(int id, const QVariantList &contexts)
{
  // handle method call org.kde.KNotify.reemit
}

void KNotify::update(int id, const QString &title, const QString &text, const QByteArray &pixmap, const QStringList &actions)
{
  // handle method call org.kde.KNotify.update
}

