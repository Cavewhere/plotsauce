#ifndef PSSTATION_H
#define PSSTATION_H

//Qt includes
#include <QString>
#include <QVector3D>

class psStation
{
public:
    psStation();

    int id();

    void setName(QString name);
    QString name() const;

    void setPosition(QVector3D position);
    QVector3D position() const;


private:
    int Id;
    QString Name;
    QVector3D Position;

    static int LastId;

    static int GenerateNewId();
};

inline int psStation::id() {
    return Id;
}

inline void psStation::setName(QString name) {
    Name = name;
}

inline QString psStation::name() const {
    return Name;
}

inline void psStation::setPosition(QVector3D position) {
    Position = position;
}

inline QVector3D psStation::position() const {
    return Position;
}

#endif // PSSTATION_H
