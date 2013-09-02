#ifndef _SETTINGSDLG_H_
#define _SETTINGSDLG_H_

#include <QDialog>
#include <QPushButton>
#include <QIcon>

#define SYMBOL_SETTINGSDLG_TITLE _("Vorbital Player Settings")
#define SYMBOL_SETTINGSDLG_SIZE QSize(480, 320)

class SettingsDlg : public QDialog
{
public:
    SettingsDlg( );
    ~SettingsDlg( );
    SettingsDlg( QDialog* parent );
    bool Create( QDialog* parent );
    void CreateControls();
	void OnButtonOkClick();
    void OnButtonCancelClick();
private:
	QPushButton* _btnOk;
	QPushButton* _btnCancel;
	QIcon* _icon;
};

#endif
