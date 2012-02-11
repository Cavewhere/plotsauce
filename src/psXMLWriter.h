#ifndef PSXMLWRITER_H
#define PSXMLWRITER_H

//Qt includes
#include <QList>
#include <QDomElement>

//Our includes
class psLine;
class psStation;

class psXMLWriter
{
public:
    psXMLWriter();

    void setLines(QList<psLine*> lines);
    void setStations(QList<psStation*> stations);

    void write(QString outputFile);

private:
    QList<psLine*> Lines;
    QList<psStation*> Stations;

    QDomDocument Document;

    QDomElement createXMLForStations();
    QDomElement createXMLForStation(psStation* station);

    QDomElement createXMLForLines();
    QDomElement createXMLForLine(psLine* line);
};

/**
  \brief Set's the lines for the writer
  */
inline void psXMLWriter::setLines(QList<psLine*> lines) {
    Lines = lines;
}

/**
  \brief Set's the stations for the writer
  */
inline void psXMLWriter::setStations(QList<psStation*> stations) {
    Stations = stations;
}



#endif // PSXMLWRITER_H
