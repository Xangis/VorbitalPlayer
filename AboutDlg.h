#ifndef _AboutDlg_H_
#define _AboutDlg_H_

#include <QDialog>
#include <QPushButton>
#include <QIcon>

class AboutDlg : public QDialog
{
public:
    AboutDlg( );
    ~AboutDlg( );
    AboutDlg( QDialog* parent );
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
