#include "Settings.h"

#include <QDialog>
#include <QSettings>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QStyle>
#include <QtDebug>

#ifndef INSTALL_PREFIX
#define INSTALL_PREFIX "/usr"
#endif

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
};

SettingsDialog::SettingsDialog()
	: QDialog()
{
	setWindowTitle(tr("CuteInformer configuration"));
	
	QFormLayout *layout = new QFormLayout(this);
	buttonBox = new QDialogButtonBox(
		QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel,
		Qt::Horizontal, this);

	QWidget *fileSelector = new QWidget(this);
	filePath = new QLineEdit(fileSelector);
	filePath->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
	QPushButton *fileButton = new QPushButton(tr("Select..."), fileSelector);
	QHBoxLayout *selectorLayout = new QHBoxLayout(fileSelector);
	selectorLayout->setContentsMargins(0, 0, 0, 0);
	selectorLayout->addWidget(filePath);
	selectorLayout->addWidget(fileButton);
			
	layout->addRow(tr("Theme"), fileSelector);
	layout->addRow(buttonBox);
	
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setNameFilter(tr("Themes (*.theme)"));
	fileDialog->setWindowModality(Qt::WindowModal);
	
	connect(fileButton, SIGNAL(clicked()), fileDialog, SLOT(show()));
	connect(fileDialog, SIGNAL(fileSelected(QString)), filePath, SLOT(setText(QString)));
	
	connect(filePath, SIGNAL(textChanged(QString)), SLOT(pathEdited(QString)));
	
	connect(buttonBox, SIGNAL(accepted()), SLOT(accept()));
	connect(buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), SLOT(saveSettings()));
	connect(buttonBox, SIGNAL(rejected()), SLOT(reject()));
	
	connect(this, SIGNAL(accepted()), SLOT(saveSettings()));
}

void SettingsDialog::showEvent(QShowEvent *)
{
	QSettings settings;
	filePath->setText(settings.value("Theme").toString());
	//buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
}

void SettingsDialog::saveSettings()
{
	qDebug() << "save settings";
	//buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
	
	QSettings settings;
	settings.setValue("Theme", filePath->text().trimmed());
	emit settingsChanged();
}

void SettingsDialog::pathEdited(const QString &)
{
	buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}

//--------

Settings::Settings(QObject *parent)
	: QObject(parent), tman(this), dialog(new SettingsDialog())
{
	reload();
	connect(dialog, SIGNAL(settingsChanged()), SLOT(reload()));
}

Settings::~Settings()
{
	delete dialog;
}

void Settings::reload()
{
	QSettings settings;
	QString theme = settings.value("Theme", 
		QVariant(INSTALL_PREFIX "/share/cuteinformer/themes/default/index.theme")).toString(); // Should always be present
	settings.setValue("Theme", theme);
	QString comment;
	if (!tman.load(theme, comment))
		qDebug() << "Theme load error:" << comment;
	else
		qDebug() << "Theme loaded ok";
	settings.sync();
}

void Settings::showDialog()
{
	dialog->show();
}

#include "Settings.moc"
