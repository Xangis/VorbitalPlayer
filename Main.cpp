#include <QApplication>
#include "VorbitalDlg.h"
#include "mpg123.h"

int main( int argc, char *argv[])
{
    // We want to make this a singleton application so multiple instances can be started
    // and multiple files being sent to the app are handled properly.
    //
    // This may help: https://github.com/itay-grudev/SingleApplication
    QApplication app(argc, argv);
    app.setApplicationName("Vorbital Player");
    QStringList arguments = app.arguments();
    mpg123_init();
    VorbitalDlg* dlg = new VorbitalDlg();
    if( arguments.length() > 1)
    {
        for(int i = 1; i < arguments.length(); i++)
        {
            dlg->LoadFile(arguments[i]);
        }
    }
    dlg->show();
    return app.exec();
}
