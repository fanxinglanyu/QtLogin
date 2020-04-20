#include "inifile.h"
#include <QVariant>
#include <QDebug>
//#include <QFileInfo>
IniFile::IniFile(QString fileName)
{
    isInsertDeduplication = false;
    isValueDeduplication = false;
    isCoverWrite = true;
    iniSetting = new QSettings(fileName,QSettings::IniFormat);
}

QStringList IniFile::getValue(const QString& group,const QString& key) const
{
    QVariant variant = iniSetting->value(QString(group +"/" + key));
    QStringList value = variant.value<QStringList>();
    qDebug()<<"value:"<<value;
    return  value;
}

QStringList IniFile::getAllKey() const
{
    return  iniSetting->allKeys();
}

QStringList IniFile::getKey(const QString &group) const
{
    iniSetting->beginGroup(group);
    QStringList keyList = iniSetting->childKeys();
    iniSetting->endGroup();
    return  keyList;
}

QStringList IniFile::getGroup() const
{
     QStringList groupList = iniSetting->childGroups();
     return  groupList;
}

void IniFile::saveValue(const QString& group, const QString& key, const QStringList& values)
{
    //结构
    /*
     *                {isValue:1
             isCover->
                     {noValue:2
    //Cover->
                              [isInsert:3
                    {isValue->
                              [noInsert:4
             noCover->
                           [isInsert:5
                   {noValue
                          [noInsert:6
    */
    /// \brief resVariant
    QVariant resVariant;
    iniSetting->beginGroup(group);
    if(isCoverWrite){//如果覆盖写入，则直接写入
        if(isValueDeduplication){//即将插入的值去重
            QStringList resValues;//新建QStringList去重
                for(int i = 0; i < values.size() ;i++){
                     if(resValues.indexOf(values.at(i)) == -1){
                            resValues.push_back(values.at(i));
                      }
                 }
             resVariant.setValue(resValues);
             //qDebug()<<"test1";
        }else{//即将插入的值不去重复
            resVariant.setValue(values);
            //qDebug()<<"test2";
        }
    }else{//不覆盖写入
        QVariant variant = iniSetting->value(key);
        QStringList originalValue = variant.value<QStringList>();
        if(isValueDeduplication){//即将插入的值去重
            if(isInsertDeduplication){//即将插入和原有值不同的值
                foreach(QString tempValue, values){
                  if(originalValue.indexOf(tempValue) == -1){
                      originalValue.push_back(tempValue);
                  }
                }
                qDebug()<<"test3";
            }else{//即将插入的值和原有值的值可以相同
                QStringList resValues;//新建QStringList对即将插入的值去重
                 for(int i = 0; i < values.size() ;i++){
                      if(resValues.indexOf(values.at(i)) == -1){
                                resValues.push_back(values.at(i));
                       }
                  }
                 foreach(QString tempValue, resValues){
                   originalValue.push_back(tempValue);
                 }
            }
            qDebug()<<"test4";
        }else{//即将插入的值不去重
            if(isInsertDeduplication){//即将插入和原有值不同的值
                QStringList resValues;
                foreach(QString tempValue, values){
                  if(originalValue.indexOf(tempValue) == -1){
                      resValues.push_back(tempValue);
                  }
                }
                foreach(QString tempValue, resValues){
                  originalValue.push_back(tempValue);
                }
                qDebug()<<"test5";
            }else{//即将插入的值和原有值可以相同
                foreach(QString tempValue, values){
                  originalValue.push_back(tempValue);
                }
                qDebug()<<"test6";
            }
        }
        resVariant.setValue(originalValue);
    }
    iniSetting->setValue(key, resVariant);
    iniSetting->endGroup();

    //在原有的基础上进行去重复
//    for(int i = 0; i < values.size() ;i++){
//        for(int j = i + 1; j < values.size(); j++){
//            int indexFind = values.indexOf(values.at(i), j);
//            if(indexFind != -1){
//                values.removeAt(indexFind);
//            }
//        }
//    }

}

void IniFile::printAllGroup() const
{
    QStringList groupList = iniSetting->childGroups();
    foreach (QString group, groupList) {
        qDebug()<< "group:" << group ;
    }
}

void IniFile::printAllKey() const
{
    qDebug()<< iniSetting->allKeys();
}

void IniFile::printKey(const QString& group) const
{
    iniSetting->beginGroup(group);
    QStringList keyList = iniSetting->childKeys();
    qDebug() <<"allKeys : " << keyList << endl;
    iniSetting->endGroup();
}

void IniFile::printAllValue(const QString& group, const QString& key) const
{
    iniSetting->beginGroup(group);
    QVariant variant = iniSetting->value(key);
    QStringList valueList = variant.value<QStringList>();
    qDebug() << "values size:" <<valueList.size();
    qDebug() <<"allValues:" << valueList;
    iniSetting->endGroup();
}

void IniFile::printAllInfo() const
{
     QStringList groupList = iniSetting->childGroups();
     foreach(QString group, groupList){
         qDebug() <<"group:" << group <<endl;
         iniSetting->beginGroup(group);
         QStringList keys = iniSetting->childKeys();
         qDebug() <<"Keys : " << keys << endl;
          foreach(QString key, keys)
          {
              QVariant variant = iniSetting->value(key);
              QStringList values = variant.value<QStringList>();
              qDebug() << "values size:" <<values.size() << endl;
              qDebug() <<"allValues:" << values<< endl;
          }
         iniSetting->endGroup();
     }
}

void IniFile::clear()
{
    iniSetting->clear();
}

QString IniFile::getFilePath() const
{
    return iniSetting->fileName();
}

void IniFile::onInsertDeduplication()
{
    isInsertDeduplication = true;
}

void IniFile::offInsertDeduplication()
{
    isInsertDeduplication = false;
}

void IniFile::onCoverWrite()
{
    isCoverWrite = true;
}

void IniFile::offCoverWrite()
{
    isCoverWrite = false;
}

void IniFile::remove(const QString& group, const QString& key)
{
    iniSetting->beginGroup(group);
    iniSetting->remove(key);
    iniSetting->endGroup();
}

void IniFile::remove(const QString& group)
{
    iniSetting->beginGroup(group);
    iniSetting->remove("");
    iniSetting->endGroup();
}

bool IniFile::hasKey(const QString &group, const QString &key) const
{
    bool res;
    iniSetting->beginGroup(group);
    res =  iniSetting->contains(key);
    iniSetting->endGroup();
    return res;
}

bool IniFile::hasGroup(const QString& group) const
{
    QStringList groupList = iniSetting->childGroups();
//    qDebug()<<"groupList:"<<groupList;
    if(groupList.indexOf(group) == -1){
        return false;
    }else{
        return  true;
    }
}

bool IniFile::hasValue(const QString& group, const QString& key,  const QString& value) const
{
    bool res;
    iniSetting->beginGroup(group);
    QVariant variant = iniSetting->value(key);
    QStringList valueList = variant.value<QStringList>();
    if(valueList.indexOf(value) == -1){
        res = false;
    }else{
        res = true;
    }
    iniSetting->endGroup();
    return  res;
}

void IniFile::onValueDeduplication()
{
    isValueDeduplication = true;
}

void IniFile::offValueDeduplication()
{
    isValueDeduplication = false;
}






