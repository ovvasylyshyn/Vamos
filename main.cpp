#include "mainwindow.h"
#include "signup.h"
#include"signin.h"
#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    SignUp s;
//    s.show();
//    SignIn i;
//    i.show();
    StartWindow st;
    st.show();
    return a.exec();
}
