#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H
#include "MusicInfo.h"

#include <QDir>
#include <QString>

class SystemInfo
{
public:
    QString listInfoPath;
    SystemInfo()
    {
        listInfoPath = QDir::currentPath() +"/listInfo.txt";
        readFileInfo();
        currentPlayingOrder = 0;                                            //默认第一首
    }
    void readFileInfo();
    void add(QString);
    QVector<MusicInfo>musicVector;
    int currentPlayingOrder;
};

#endif // SYSTEMINFO_H
