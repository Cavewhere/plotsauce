#ifndef PSLINE_H
#define PSLINE_H

//Our includes
#include <psStation.h>

class psLine {
public:
    psLine();
    psLine(psStation* s1, psStation* s2);

    bool isValid();

    psStation* station1();
    psStation* station2();

private:
    psStation* Station1;
    psStation* Station2;
};

/**
  Gets the first station that makes up the line
  */
inline psStation* psLine::station1() {
    return Station1;
}

/**
  Gets the second station that makes up the line
  */
inline psStation* psLine::station2() {
    return Station2;
}

#endif // PSLINE_H
