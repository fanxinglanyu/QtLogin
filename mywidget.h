#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyWidget *ui;
signals:
    void logoutdialogShow();
    void accountShow();
    void onMusic();
};
#endif // MYWIDGET_H
