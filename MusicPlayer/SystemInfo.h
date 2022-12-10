#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QDir>
#include <QString>


class SystemInfo
{
    QString listInfoPath;
    SystemInfo()
    {
        listInfoPath = QDir::currentPath() +"/listInfo.txt";
        readFileInfo();
    }
    void readFileInfo();
};

#endif // SYSTEMINFO_H
