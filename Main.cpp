#include <QApplication>
#include "VorbitalDlg.h"
#include "mpg123.h"

int main( int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Vorbital Player");
    mpg123_init();
    VorbitalDlg* dlg = new VorbitalDlg();
    dlg->show();
    return app.exec();
}
