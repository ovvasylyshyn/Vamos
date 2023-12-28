#include "mainwindow.h"
#include "signup.h"
#include"signin.h"
#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow st;
    st.show();
    return a.exec();
}
