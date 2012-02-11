#include "psLine.h"

psLine::psLine() :
    Station1(NULL),
    Station2(NULL)
{

}

psLine::psLine(psStation* s1, psStation* s2) {
    Station1 = s1;
    Station2 = s2;
}

/**
  Checks to see if the psLine is valid
  */
bool psLine::isValid() {
    if(Station1 != Station2 && Station1 != NULL && Station2 != NULL) {
        return true;
    }
    return false;
}
