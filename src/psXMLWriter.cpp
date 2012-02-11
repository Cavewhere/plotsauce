#include "psXMLWriter.h"

//Qt includes
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QVector3D>

//Our includes
#include <psStation.h>
#include <psLine.h>

//zlib includes
#include <zlib.h>

psXMLWriter::psXMLWriter()
{
}


/**
  \brief Writes the lines and station data to
  */
void psXMLWriter::write(QString outputFile) {
    Document.clear();
    QDomElement root = Document.createElement("PlotSauceDocument");
    Document.appendChild(root);

    QDomElement stationsNode = createXMLForStations();
    QDomElement linesNode = createXMLForLines();

    root.appendChild(stationsNode);
    root.appendChild(linesNode);

    QByteArray fullDocumentAsXML = Document.toByteArray();

    gzFile zippedFile = gzopen(outputFile.toAscii(), "w"); //Write with level 9 huffman
    gzwrite(zippedFile, fullDocumentAsXML.constData(), fullDocumentAsXML.length());
    gzclose(zippedFile);

//    QFile file(outputFile);
//    bool succes = file.open(QFile::WriteOnly);
//    if(succes) {
//        file.write(fullDocumentAsXML);
//    } else {
//        qDebug() << "Couldn't write xml to " << fullDocumentAsXML;
//    }
}

/**
  Creates the xml nodes for a station
  */
QDomElement psXMLWriter::createXMLForStations() {
    QDomElement rootStationNode = Document.createElement("Stations");
    foreach(psStation* station, Stations) {
        QDomElement stationNode = createXMLForStation(station);
        rootStationNode.appendChild(stationNode);
    }

    return rootStationNode;
}

/**
  Creates the xml node for a single station
  */
QDomElement psXMLWriter::createXMLForStation(psStation* station) {
    QDomElement stationNode = Document.createElement("Station");

    QDomElement uniqueIdNode = Document.createElement("Id");
    QDomText idTextElement = Document.createTextNode(QString("%1").arg(station->id()));
    uniqueIdNode.appendChild(idTextElement);

    QDomElement nameNode = Document.createElement("Name");
    QDomText nameTextElement = Document.createTextNode(station->name());
    nameNode.appendChild(nameTextElement);

    QDomElement positionNode = Document.createElement("Position");

    QVector3D position = station->position();
    QDomElement xNode = Document.createElement("X");
    QDomText xNodeValue = Document.createTextNode(QString("%1").arg(position.x()));
    xNode.appendChild(xNodeValue);

    QDomElement yNode = Document.createElement("Y");
    QDomText yNodeValue = Document.createTextNode(QString("%1").arg(position.y()));
    yNode.appendChild(yNodeValue);

    QDomElement zNode = Document.createElement("Z");
    QDomText zNodeValue = Document.createTextNode(QString("%1").arg(position.z()));
    zNode.appendChild(zNodeValue);

    positionNode.appendChild(xNode);
    positionNode.appendChild(yNode);
    positionNode.appendChild(zNode);

    stationNode.appendChild(uniqueIdNode);
    stationNode.appendChild(nameNode);
    stationNode.appendChild(positionNode);

    return stationNode;
}

/**
  Creates the xml node for all the lines
  */
QDomElement psXMLWriter::createXMLForLines() {
    QDomElement rootLineNode = Document.createElement("Lines");
    foreach(psLine* line, Lines) {
        QDomElement lineNode = createXMLForLine(line);
        rootLineNode.appendChild(lineNode);
    }
    return rootLineNode;
}

/**
  Creates the xml node for a line
  */
QDomElement psXMLWriter::createXMLForLine(psLine* line) {
    QDomElement lineNode = Document.createElement("Line");

    psStation* station1 = line->station1();
    QDomElement station1Node = Document.createElement("Station1ID");
    QDomText station1TextNode = Document.createTextNode(QString("%1").arg(station1->id()));
    station1Node.appendChild(station1TextNode);

    psStation* station2 = line->station2();
    QDomElement station2Node = Document.createElement("Station2ID");
    QDomText station2TextNode = Document.createTextNode(QString("%2").arg(station2->id()));
    station2Node.appendChild(station2TextNode);

    lineNode.appendChild(station1Node);
    lineNode.appendChild(station2Node);

    return lineNode;
}
