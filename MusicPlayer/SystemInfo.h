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
    }
    void readFileInfo();
    void add(QString);
    QVector<MusicInfo>musicVector;
};

#endif // SYSTEMINFO_H
