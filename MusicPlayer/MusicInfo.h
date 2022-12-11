#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QString>
#include <QStringList>
#include <QDebug>

class MusicInfo
{
public:
    int num;
    QString name;
    QString localFilePath;
    QString singer;
    int playCount;
    int PlayScends;//播放秒数
    MusicInfo(QString name,QString localFileName,QString singer,int playCount)
    {
        this->name = name;
        this->localFilePath = localFileName;
        this->singer= singer;
        this->playCount = playCount;
    }
    MusicInfo(QString str)
    {
        QStringList strlist= str.split('|');
        this->num = strlist[0].mid(5).toInt();
        this->PlayScends = timesTransition(strlist[1].mid(6));
        this->playCount = strlist[2].mid(6).toInt();
        this->localFilePath = strlist[3].mid(6);
        QStringList strlistNameAndSinger = getMusicNameAndSinger(localFilePath).split('-');
        this->name =strlistNameAndSinger[0];
        this->singer = strlistNameAndSinger[1];
    }
    MusicInfo(){}

    void read()
    {

    }
    int timesTransition(QString str)
    {
        QStringList strlist= str.split(':');
        return strlist[0].toInt()*60 + strlist[1].toInt();
    }
    QString getMusicNameAndSinger(QString path)
    {
        QStringList strlist=path.split('.');
        int num =strlist[strlist.count()-1].count();
        path = path.left(path.count()-num-1);
        QStringList strlist1 = path.split('/');
        path = strlist1[strlist1.count()-1];
        return path;
    }
};
#endif // MUSICINFO_H
