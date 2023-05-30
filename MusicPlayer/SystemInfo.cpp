#include "MusicInfo.h"
#include "SystemInfo.h"

#include <QFile>
#include <QFileDialog>
#include <QDebug>

void SystemInfo::readFileInfo()
{
    bool exist = QFile::exists(listInfoPath);
    if(!exist)
    {
        qDebug()<<"文件不存在";
    }
    QFile file(listInfoPath);
    //打开文件，只读方式
    bool isOk = file.open(QIODevice::ReadOnly) ;
    if(isOk)
    {
        QString str;
        while(!file.atEnd()) //没有到结尾则进入循环
        {
            QByteArray temp = file.readLine();
            str = temp.data();
            if(str.startsWith("nums:"))
            {
                MusicInfo *musicInfo = new MusicInfo(str);
                musicVector.push_back(*musicInfo);
            }
        }
    }
    else
    {
        qDebug()<<"文件打开失败";
    }
    file.close();
}

void SystemInfo::add(QString str)
{
    MusicInfo *musicInfo = new MusicInfo();
    musicInfo->localFilePath=str;
    musicInfo->num=musicVector.count();
    QStringList strList = str.split('/');
    QStringList strList1 = strList[strList.count()-1].split('-');
    musicInfo->name = strList1[0];
    QString str1;
    if(strList1[1].endsWith(".mp3") || strList1[1].endsWith(".wav"))
    {
        str1=strList1[1].left(strList[1].size()-4);
    }
    qDebug()<<"singer = "+str1;
    musicInfo->singer = str1;
    musicInfo->playCount=0;
    musicInfo->PlayScends=0;
    musicVector.push_back(*musicInfo);

    QFile file(listInfoPath);
    QFileInfo fileinfo(listInfoPath);

    if(file.open(QIODevice::ReadWrite))
    {
        QByteArray array= file.readAll();
        file.seek(0);//写入位置设置为首端，保证覆盖
        QString addstr = "nums:" +QString::number(musicInfo->num)+"|"
                +"times:0:0"+"|"
                +"count:"+QString::number(musicInfo->playCount) +"|"
                +"local:"+musicInfo->localFilePath+"\r\n";
        qDebug()<<addstr;
        array += addstr;
        file.write(array);
    }
     else
    {
        qDebug()<<"文件打开失败";
    }
    file.close();
}
