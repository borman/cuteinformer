#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "ThemeManager.h"

class SettingsDialog;
class Settings: public QObject
{
	Q_OBJECT
	public:
		Settings(QObject *parent = NULL);
		virtual ~Settings();
	public slots:
		void reload();
		void showDialog();
	private:
		ThemeManager tman;
		SettingsDialog *dialog;
};

#endif // SETTINGS_H
