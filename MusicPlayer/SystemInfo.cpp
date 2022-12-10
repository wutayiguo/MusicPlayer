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
    int i=0;
    if(isOk)
    {
        QByteArray array ;
        QString str;
        while(!file.atEnd()) //没有到结尾则进入循环
        {
            QByteArray temp = file.readLine();
            str = temp.data();
            array += temp ;
            if(str.startsWith("num:"))
            {
                str.replace("user:","");
            }

        }
    }
    else
    {
        qDebug()<<"文件打开失败";
    }
    file.close();
//    ui->tableWidget->setRowCount(MapInfo.count());//根据账户个数设置表单大小
//    for (int i=0;i<MapInfo.count();i++)
//    {
//        QTableWidgetItem *item = new QTableWidgetItem(MapInfo[i].info);
//        ui->tableWidget->setItem(i,0,item);
//    }
}
