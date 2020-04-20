#include "login.h"
#include "ui_login.h"

#include "connection.h"
#include <QMessageBox>
#include <QDebug>
#include <QWidget>
#include <QStackedWidget>
#include <QSqlError>
#include <QPixmap>

#include<QMediaPlayer>
#include <QMediaPlaylist>
#include <QSettings>
#include <QMovie>

#include <QPainter>
#include <QBitmap>

Login::Login(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->pLineEdit->setEchoMode(QLineEdit::Password);

//    QPalette palette;
//    //palette.setColor(QPalette::Background,QColor("red"));
//    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/img1.png").scaled(this->size())));
//    this->setPalette(palette);
    QPixmap plx;
    plx.load(":/img/logn4.png");
    QPixmap* imgPointer = &plx;
    imgPointer->scaled(ui->aLabel->size(), Qt::IgnoreAspectRatio);
    ui->aLabel->setScaledContents(true);
    ui->aLabel->setPixmap(plx);
    ui->aComboBox->setStyleSheet("background-color: rgba(255, 255, 255, 20%)");
    ui->aLabel->show();

    plx.load(":/img/logn6.png");
    imgPointer->scaled(ui->pLabel->size(), Qt::IgnoreAspectRatio);
    ui->pLabel->setScaledContents(true);
    ui->pLabel->setPixmap(plx);
    //;border:1px solid #
    ui->pLineEdit->setStyleSheet("background-color: rgba(255, 255, 255, 20%)");
    ui->pLabel->show();

    ui->lButton->setStyleSheet("background-color: rgba(255, 128, 64, 50%;border:none)");
    ui->lButton->setFlat(true);
    ui->lButton->colorCount();

    ui->pushButton->setStyleSheet("background-color: rgba(255, 255, 255, 20%;border:none)");

    //设置背景图片
    //this->setStyleSheet("QDialog{border-image: url(:/img/img2.jpg);}");
    QMovie *iconShow = new QMovie(":/img/yasuo.gif");
    ui->label->setMovie(iconShow);

    iconShow->start();
//    this->setStyleSheet("QDialog{border-image: url(:/img/img2.jpg);}");


    this->setWindowTitle("登陆测试");
    //下拉框
    ui->aComboBox->setEditable(true);//可以编辑
    ui->aComboBox->lineEdit()->setMaxLength(10);//输入的长度
    //使用 QStringLiteral 宏可以在编译期把代码里的常量字符串 str
    //直接构造为 QString 对象，于是运行时就不再需要额外的构造开销了。
    ui->aComboBox->lineEdit()->setPlaceholderText(QStringLiteral("请输入用户名"));
    ui->pLineEdit->setPlaceholderText(QStringLiteral("请输入密码"));

    initUsernameList();//初始化下拉账号

    //边框圆角化
       QBitmap bmp(this->size());
        bmp.fill();
        QPainter p(&bmp);
        p.setPen(Qt::NoPen);
        p.setBrush(Qt::black);
        p.setPen(Qt::transparent);//表示RGBA值为(0,0,0,0)的透明色。
        p.setRenderHint(QPainter::Antialiasing); // 反锯齿;
        p.drawRoundedRect(bmp.rect(), 20, 20);
        setMask(bmp);

    //this->setStyleSheet("border-top-left-radius:15 px;border-top-right-radius: 15 px;"
      //                  "border-bottom-left-radius:15 px;border-bottom-right-radius:15 px");
    //ui->label->setStyleSheet("border-radius: 15px, 50px");

    //循环播放音乐
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/LOL.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
    //music->stop();
//    QMediaPlayer* player = new QMediaPlayer;
//        player->setMedia(QUrl::fromLocalFile("/Users/macbookpro/Qt/loginTest/LOL.mp3"));
////        player->setVolume(50);
//        player->play();

//    loadcfg();

//    m_userNameList.clear();
//    m_isremberList.clear();



}

Login::~Login()
{
    delete ui;
}


void Login::initUsernameList()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/test.ini";
    IniFile iniUsername(fileName);
    m_userNameList = iniUsername.getValue(QString("config"),QString("username"));
    ui->aComboBox->addItems(m_userNameList);

    if(m_userNameList.size()>0){
        username = m_userNameList.at(0);
        qDebug() <<"m_userNameList.at(0)" << m_userNameList.at(0);
    }

    if(isrembered == 1)
    {
        ui->pCheckBox->setChecked(true);
        ui->aComboBox->setCurrentText(username);
    }
}

void Login::palyMusic()
{
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/LOL.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}

void Login::writeUsernameList(QStringList& values)
{
    QString fileName = QCoreApplication::applicationDirPath() + "/test.ini";
    IniFile iniUsername(fileName);
    iniUsername.offCoverWrite();
    iniUsername.onValueDeduplication();
    iniUsername.onInsertDeduplication();
    iniUsername.saveValue(QString("config"),QString("username"), values);
}



void Login::on_pCheckBox_clicked()
{
    if(ui->pCheckBox->isChecked()){
          isrembered = 1;
          qDebug() << "isrembered = true";
      }else{
          isrembered = 0;
          qDebug() << "isrembered = false";
      }

}

void Login::on_lButton_clicked()
{
    username = ui->aComboBox->currentText() ;
    password = ui->pLineEdit->text();

    //qDebug() << "username" <<username<< endl;
    //qDebug() << "password" << password <<endl;

    if(username.isEmpty()){
        QMessageBox::information(this, tr("请输入账号"),tr("请先输入账号再登陆，谢谢！"),
                                 QMessageBox::Ok);
        ui->aComboBox->setFocus();
    }else if(password.isEmpty()){
        QMessageBox::information(this, tr("请输入密码"),tr("请先输入密码再登陆，谢谢！"),
                                 QMessageBox::Ok);
        ui->pLineEdit->setFocus();
    }else{
    if(!createConnection()){
        QMessageBox::information(this, tr("提示"),tr("请先连接网络，谢谢！"),
                                 QMessageBox::Ok);
    }else{
    QSqlDatabase db = QSqlDatabase::database("connection1");
    QSqlQuery query(db);

    QString str = QString("select * from user where account = '%0' and password = '%1'").arg(username).arg(password);
    query.exec(str);
    int record = query.size();
    qDebug() << "record:" << record<< endl;

    //未连接上数据库返回-1，连接上查询失败返回0，查到返回1
    if(record == -1 || record == 0){
         QMessageBox::information(this,tr("提示"),tr("用户名或密码错误！"),QMessageBox::Ok);
         ui->pLineEdit->clear();
         ui->pLineEdit->setFocus();
    }else{
        QMessageBox::information(this,tr("提示"),tr("登陆成功！"),QMessageBox::Ok);
        //QDialog::accept();

        if(isrembered == 1){
            qDebug() << " m_userNameList.push_front(username)"<<endl;
            m_userNameList.push_front(username);
            writeUsernameList(m_userNameList);

        }
        emit mainwidgetShow();
        ui->aComboBox->clear();
        music->stop();
        this->close();
    }
   }
  }
}

void Login::on_pushButton_clicked()
{
    exit(0);
}
