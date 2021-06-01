#include "SettingsDlg.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

SettingsDlg::SettingsDlg( )
{
}

SettingsDlg::~SettingsDlg()
{
}

void SettingsDlg::OnButtonOkClick()
{
	close();
}

void SettingsDlg::OnButtonCancelClick()
{
	close();
}

SettingsDlg::SettingsDlg( QDialog* parent )
{
    Create(parent);
}

bool SettingsDlg::Create( QDialog* )
{
    _btnOk = NULL;
	_btnCancel = NULL;
    CreateControls();
    _icon = new QIcon("vorbital.ico");
    setWindowIcon(*_icon);
    return true;
}

void SettingsDlg::CreateControls()
{
    QVBoxLayout* itemBoxSizer2 = new QVBoxLayout();

    QHBoxLayout* itemBoxSizer3 = new QHBoxLayout();
    itemBoxSizer2->addLayout(itemBoxSizer3);

    itemBoxSizer3->addSpacing(2);

    _btnOk = new QPushButton( "OK", this );
	_btnOk->setToolTip("Accept settings.");
    itemBoxSizer3->addWidget(_btnOk);

    itemBoxSizer3->addSpacing(6);

    _btnCancel = new QPushButton( "Cancel", this );
	_btnOk->setToolTip("Ignore changes.");
    itemBoxSizer3->addWidget(_btnCancel);

    itemBoxSizer3->addSpacing(6);

    this->setLayout(itemBoxSizer2);

    connect(_btnOk, SIGNAL(released()), this, SLOT(onButtonOkClick()));
    connect(_btnCancel, SIGNAL(released()), this, SLOT(onButtonCancelClick()));
}
