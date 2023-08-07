//#include "ccmainwindow.h"
#include "UserLogin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*CCMainWindow w;
    w.show();*/
    UserLogin* userLogin = new UserLogin;
    userLogin->show();
    return a.exec();
}
