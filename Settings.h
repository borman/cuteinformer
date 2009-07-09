#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "ThemeManager.h"

class SettingsDialog;
class Settings: public QObject
{
	Q_OBJECT
	public:
		static Settings *instance();
	public slots:
		void reload();
		void showDialog();
	protected:
		Settings(QObject *parent = NULL);
		virtual ~Settings();
	private:
		ThemeManager tman;
		SettingsDialog *dialog;
};

#endif // SETTINGS_H
