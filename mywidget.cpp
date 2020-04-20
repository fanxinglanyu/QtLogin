#include "mywidget.h"
#include "ui_mywidget.h"



MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);


}

MyWidget::~MyWidget()
{
    delete ui;
}



void MyWidget::on_pushButton_clicked()
{
    emit logoutdialogShow();
    emit accountShow();
    emit onMusic();
    this->close();
}
