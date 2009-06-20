#include "ThemeManager.h"

#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QtDebug>

ThemeManager::ThemeManager(QObject *parent)
	: QObject(parent)
{
}

bool ThemeManager::load(const QString &file, QString &comment)
{
	qDebug() << "Loading theme" << file;
	QSettings config(file, QSettings::IniFormat, this);
	if (config.status()!=QSettings::NoError)
	{
		comment = tr("Cannot read theme index");
		return false;
	}
	
	QDir dir = QFileInfo(file).absolutePath(); // Theme config directory
	
	QString themeRoot = config.value("ThemeRoot", ".").toString();
	if (QDir(themeRoot).isRelative())
		themeRoot = dir.absoluteFilePath(themeRoot); // Make absolute path
	if (!QDir(themeRoot).exists())
	{
		comment = tr("ThemeRoot does not exist");
		return false;
	}
		
	QString themeStyle = config.value("Style", QVariant(QString::null)).toString();	
	if (themeStyle.isEmpty())
	{
		comment = tr("No style specified in theme index");
		return false; 
	}
	if (QDir(themeStyle).isRelative())
		themeStyle = dir.absoluteFilePath(themeStyle);
		
	QFile qss(themeStyle);
	qss.open(QIODevice::ReadOnly);
	if (qss.error()!=QFile::NoError)
	{
		comment = tr("Cannot open theme style");
		return false;
	}
	
	// Everything ok, read theme
	QDir::setSearchPaths("theme", QStringList(themeRoot));
	QTextStream ts(&qss);
	qApp->setStyleSheet(ts.readAll());
	qss.close();
	
	comment = QString::null;
	return true;
}
