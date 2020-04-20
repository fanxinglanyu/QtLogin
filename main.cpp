#include "mywidget.h"

#include <QApplication>

#include "login.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MyWidget w;

//    Login dlg;
//    if (dlg.exec() == QDialog::Accepted) {
//        w.show();
//        return a.exec();
//    } else {
//        return 0;
//    }

    Login  dlg;
    MyWidget w;



    //登陆到主界面
    QObject::connect(&dlg, &Login::mainwidgetShow,
                       &w, &MyWidget::show);
    //主界面到登陆
    QObject::connect(&w, &MyWidget::logoutdialogShow,
                      &dlg, &Login::show);

    QObject::connect(&w, &MyWidget::accountShow,
                     &dlg, &Login::initUsernameList);

    QObject::connect(&w, &MyWidget::onMusic,
                     &dlg, &Login::palyMusic);

    dlg.exec();
    return a.exec();
}
