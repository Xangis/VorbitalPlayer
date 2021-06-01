#include "AboutDlg.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

AboutDlg::AboutDlg( )
{
}

AboutDlg::~AboutDlg()
{
}

void AboutDlg::OnButtonOkClick()
{
    close();
}

void AboutDlg::OnButtonCancelClick()
{
    close();
}

AboutDlg::AboutDlg( QDialog* parent )
{
    Create(parent);
}

bool AboutDlg::Create( QDialog* )
{
    _btnOk = nullptr;
    _btnCancel = nullptr;
    CreateControls();
    _icon = new QIcon("vorbital.ico");
    setWindowIcon(*_icon);
    return true;
}

void AboutDlg::CreateControls()
{
    QFont f( "Calibri", 10, QFont::Bold);

    this->setWindowTitle("Vorbital Player 4.44");

    QVBoxLayout* itemBoxSizer1 = new QVBoxLayout();

    QHBoxLayout* itemBoxSizer2 = new QHBoxLayout();

    QLabel* description = new QLabel(this);
    description->setFont(f);
#ifdef WIN32
    description->setText("Vorbital Player 4.44\nCopyright 2006-2020 Jason Champion.\nDeveloped by Jason Champion.\nThe Vorbital Player is free software and may be distributed freely under the terms of the MIT license.\n\nhttps://zetacentauri.com/software_vorbital.htm\n\nVorbital uses the Qt 5.8, libogg 1.3.2, libvorbis 1.3.7, wavpack 5.3.0, mpg123 1.26.3, and libsndfile 1.0.28 libraries.");
#else
    description->setText("Vorbital Player 4.44\nCopyright 2006-2020 Jason Champion.\nDeveloped by Jason Champion.\nThe Vorbital Player is free software and may be distributed freely under the terms of the MIT license.\n\nhttps://zetacentauri.com/software_vorbital.htm\n\nVorbital uses the Qt, libogg, libvorbis, wavpack, mpg123, and libsndfile libraries.");
#endif
    itemBoxSizer2->addWidget(description);
    itemBoxSizer1->addLayout(itemBoxSizer2);

    QHBoxLayout* itemBoxSizer3 = new QHBoxLayout();

    itemBoxSizer3->addSpacing(2);

    _btnOk = new QPushButton( "OK", this );
    _btnOk->setToolTip("Accept settings.");
    itemBoxSizer3->addWidget(_btnOk);

    itemBoxSizer3->addSpacing(6);

    _btnCancel = new QPushButton( "Cancel", this );
    _btnOk->setToolTip("Ignore changes.");
    itemBoxSizer3->addWidget(_btnCancel);

    itemBoxSizer3->addSpacing(6);

    itemBoxSizer1->addLayout(itemBoxSizer3);

    this->setLayout(itemBoxSizer1);

    connect(_btnOk, SIGNAL(released()), this, SLOT(onButtonOkClick()));
    connect(_btnCancel, SIGNAL(released()), this, SLOT(onButtonCancelClick()));
}
