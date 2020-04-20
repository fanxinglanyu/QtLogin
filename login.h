#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "inifile.h"
#include <QCoreApplication>
#include <QMediaPlayer>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pCheckBox_clicked();

    void on_lButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    //背景音乐
    QMediaPlayer *music;

    //记住的用户名
    QStringList m_userNameList;
    int isrembered;//是否记住账户
    QString username;
    QString password;

    void writeUsernameList(QStringList&);//写入用户名
public slots:
    void initUsernameList();//初始化用户名
    void palyMusic();
signals:
    void mainwidgetShow();
};

#endif // LOGIN_H
