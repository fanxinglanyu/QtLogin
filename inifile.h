#ifndef INIFILE_H
#define INIFILE_H

#include<QSettings>
#include <QString>
#include <QStringList>
#include <QDebug>

class IniFile
{
public:
    IniFile():iniSetting(nullptr),isCoverWrite(false),isInsertDeduplication(false),isValueDeduplication(false){}
    IniFile(QString fileName);
    ~IniFile(){delete  iniSetting;}

    //获得值
    //返回group的key下的value
    QStringList getValue(const QString&,const  QString&) const;
    //返回所有key
    QStringList getAllKey() const;
    //返回group的所有key
    QStringList getKey(const QString&) const;
    //返回所有group
    QStringList getGroup() const;
    //返回当前ini文件的路径
    QString getFilePath() const;
    //在group的key下写入value
    void saveValue(const QString& , const QString& , const  QStringList&);

    //打印信息
    //打印所有组
    void printAllGroup() const;
    //打印所有key
    void printAllKey() const;
    //打印group下的所有key
    void printKey(const QString&) const;
    //打印group的key下的所有value
    void printAllValue(const QString&,const QString&) const;
    //打印所有group的全部信息
    void printAllInfo() const;


    //删除操作
    //删除所有group
    void clear();
    //移除group下的key
    void remove(const QString&, const QString&);
    //移除group
    void remove(const QString&);

    //判断当前group下是否有key
    bool hasKey(const QString&,const QString&) const;
    bool hasGroup(const QString&) const;
    bool hasValue(const QString&, const QString&, const QString&) const;

    //打开或关闭写入和原值不重复的value
    void onInsertDeduplication();
    void offInsertDeduplication();
    //打开或关闭对即将写的value去重
    void onValueDeduplication();
    void offValueDeduplication();
    //打开或关闭覆盖写入value
    void onCoverWrite();
    void offCoverWrite();

private:
    QSettings* iniSetting;//指向QSettings对象的指针
    bool isCoverWrite;//是否覆盖写入value
    bool isInsertDeduplication;//是否插入重复的value
    bool isValueDeduplication;//对即将插入的值去重复
    //不允许复制操作
    IniFile(const IniFile&);//复制操作符函数
    IniFile& operator=(const IniFile&);//赋值操作符函数
};

#endif // INIFILE_H
