#ifndef PSSURVEX3DPARSER_H
#define PSSURVEX3DPARSER_H

//Our includes
class psStation;
class psLine;

//Qt includes
#include <QString>
#include <QMap>
#include <QVector3D>

class psSurvex3DParser
{
public:
    psSurvex3DParser();

    void parse(QString filename);

    QList<psLine*> lines() const;
    QList<psStation*> stations() const;

private:
    QList<psLine*> Lines;
    QList<psStation*> Stations;

};

inline QList<psLine*> psSurvex3DParser::lines() const {
    return Lines;
}

inline QList<psStation*> psSurvex3DParser::stations() const {
    return Stations;
}

#endif // PSSURVEX3DPARSER_H
