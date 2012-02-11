//Our includes
#include "psStationLookup.h"
#include "psStation.h"

//Qt includes
#include <QDebug>

psStationLookup::psStationLookup()
{
}

/**
  This will find the station by it's position
  */
psStation* psStationLookup::findStation(QVector3D position) {
    QList<psStation*> stations = XLookup.values(position.x());
    foreach(psStation* currentStation, stations) {
        if(currentStation->position() == position) {
            return currentStation;
        }
    }

    return NULL;
}

/**
  This will find the station by it's name
  */
psStation* psStationLookup::findStation(QString fullStationName) {
    return NameLookup.value(fullStationName, NULL);
}

/**
  \brief Gets all stations from the lookup
  */
QList<psStation*> psStationLookup::allStations() {

    if(XLookup.size() != NameLookup.size()) {
        qDebug() << "The xLookup doesn't equal the nameLookup" << XLookup.size() << NameLookup.size();
    }

    return NameLookup.values();
}

/**
  \brief Adds a station to the lookup

  This will not add the station twice into the lookup
  */
void psStationLookup::addStation(psStation* station) {

    psStation* positionLookup = findStation(station->position());
    psStation* nameLookup = findStation(station->name());

    if(positionLookup == NULL) {
        XLookup.insertMulti(station->position().x(), station);
    }

    if(nameLookup == NULL) {
        NameLookup.insert(station->name(), station);
    }
}
