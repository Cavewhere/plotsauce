//Qt includes
#include <QtCore/QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>

//Our includes
#include <psSurvex3DParser.h>
#include <psXMLWriter.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList args = a.arguments();
    if(args.isEmpty() || args.size() != 3) {
        qDebug() << "How to run: \n./plotsauce [Input File (survex .3d)] [Output XML file] ";
        return 1;
    }

    QList<psStation*> stations;
    QList<psLine*> lines;

    QString inputFilename = args[1]; //.first();
    QString outputFilename = args[2];

    QFileInfo fileinfo(inputFilename);

    if(fileinfo.exists()) {
        if(fileinfo.suffix().compare("3d", Qt::CaseInsensitive) == 0) {
            //We found a survex file
            psSurvex3DParser survexParser;
            survexParser.parse(inputFilename);

            stations = survexParser.stations();
            lines = survexParser.lines();

        } else {
            qDebug() << "Plot sauces doesn't know how to handle " << fileinfo.suffix() << "files";
            return 1;
        }
    } else {
        qDebug() << inputFilename << "doesn't exist!";
        return 1;
    }

    //Write data to the file
    psXMLWriter writer;
    writer.setLines(lines);
    writer.setStations(stations);
    writer.write(outputFilename);

    return 0;

}
