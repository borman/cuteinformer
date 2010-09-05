#ifndef SETTINGS_P_H
#define SETTINGS_P_H

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFileDialog>

class SettingsDialog: public QDialog
{
	Q_OBJECT
	public:
		SettingsDialog();
	signals:
		void settingsChanged();
	private slots:
		void saveSettings();
		void pathEdited(const QString &);
	protected:
		void showEvent(QShowEvent *);
	private:
		QLineEdit *filePath;
		QDialogButtonBox *buttonBox;
		QFileDialog *fileDialog;
};

#endif // SETTINGS_P_H
