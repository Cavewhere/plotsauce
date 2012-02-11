#ifndef PSSTATIONLOOKUP_H
#define PSSTATIONLOOKUP_H

//Our includes
class psStation;

//Qt includes
#include <QVector3D>
#include <QString>
#include <QMap>

class psStationLookup
{
public:
    psStationLookup();

    psStation* findStation(QVector3D station);
    psStation* findStation(QString fullStationName);

    void addStation(psStation* station);

    QList<psStation*> allStations();

private:

    QMultiMap<float, psStation*> XLookup;  //Lookup for just the x axis

    QMap<QString, psStation*> NameLookup;

};

#endif // PSSTATIONLOOKUP_H
