#ifndef _InfoDlg_H_
#define _InfoDlg_H_

#include <QDialog>
#include <QPushButton>
#include <QIcon>

class InfoDlg : public QDialog
{
public:
    InfoDlg( );
    ~InfoDlg( );
    InfoDlg( QDialog* parent );
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
