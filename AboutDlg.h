#ifndef _AboutDlg_H_
#define _AboutDlg_H_

#include <QDialog>
#include <QPushButton>
#include <QIcon>
#include <QLabel>

class AboutDlg : public QDialog
{
public:
    AboutDlg( );
    ~AboutDlg( );
    AboutDlg( QDialog* parent );
    bool Create( QDialog* parent );
    void CreateControls();
private:
    QPushButton* _btnOk;
    QPushButton* _btnCancel;
    QIcon* _icon;
};

#endif
