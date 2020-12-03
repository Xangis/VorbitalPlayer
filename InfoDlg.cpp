#include "InfoDlg.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

InfoDlg::InfoDlg( )
{
}

InfoDlg::~InfoDlg()
{
}

void InfoDlg::OnButtonOkClick()
{
    close();
}

void InfoDlg::OnButtonCancelClick()
{
    close();
}

InfoDlg::InfoDlg( QDialog* parent )
{
    Create(parent);
}

bool InfoDlg::Create( QDialog* )
{
    _btnOk = nullptr;
    _btnCancel = nullptr;
    CreateControls();
    _icon = new QIcon("vorbital.ico");
    setWindowIcon(*_icon);
    return true;
}

void InfoDlg::CreateControls()
{
    InfoDlg* itemDialog1 = this;

    QVBoxLayout* itemBoxSizer2 = new QVBoxLayout();

    QHBoxLayout* itemBoxSizer3 = new QHBoxLayout();
    itemBoxSizer2->addLayout(itemBoxSizer3);

    itemBoxSizer3->addSpacing(2);

    _btnOk = new QPushButton( "OK", itemDialog1 );
    _btnOk->setToolTip("Accept settings.");
    itemBoxSizer3->addWidget(_btnOk);

    itemBoxSizer3->addSpacing(6);

    _btnCancel = new QPushButton( "Cancel", itemDialog1 );
    _btnOk->setToolTip("Ignore changes.");
    itemBoxSizer3->addWidget(_btnCancel);

    itemBoxSizer3->addSpacing(6);

    itemDialog1->setLayout(itemBoxSizer2);

    connect(_btnOk, SIGNAL(released()), this, SLOT(onButtonOkClick()));
    connect(_btnCancel, SIGNAL(released()), this, SLOT(onButtonCancelClick()));
}
