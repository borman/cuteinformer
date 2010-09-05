#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <QObject>

class ThemeManager: public QObject
{
	Q_OBJECT
	public:
		ThemeManager(QObject *parent = NULL);
		bool load(const QString &file, QString &comment);
};

#endif // THEME_MANAGER_H
