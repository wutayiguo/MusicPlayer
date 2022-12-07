#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QString>


class MusciInfo
{
    QString name;
    QString localFileName;
    QString singer;
    int playCount;
    MusciInfo(QString name,QString localFileName,QString singer,int playCount)
    {
        this->name=name;
        this->localFileName = localFileName;
        this->singer = singer;
        this->playCount = playCount;
    }
};
#endif // MUSICINFO_H
