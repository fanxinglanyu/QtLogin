#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

static bool createConnection(){


    //连接第一个数据库
    //QMYSQL
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QMYSQL", "connection1");
    db2.setHostName("127.0.0.1");
    db2.setUserName("root");
    db2.setPassword("root");
    db2.setPort(8889);
    //test_majiang.db
    db2.setDatabaseName("test_majiang");

    if (!db2.open()) {
        //critical(QWidget *parent, const QString &title,
        //const QString &text,
        //QMessageBox::StandardButtons buttons = Ok,
        //QMessageBox::StandardButton defaultButton = NoButton)
           QMessageBox::critical(0, "Cannot open database",
                                 "Unable to establish a database connection", QMessageBox::Cancel);
           return false;
       }

    return true;
}

#endif // CONNECTION_H
