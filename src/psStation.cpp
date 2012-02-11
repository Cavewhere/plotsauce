#include "psStation.h"

int psStation::LastId = 0;

psStation::psStation() {
    Id = GenerateNewId();
}

int psStation::GenerateNewId() {
    LastId++;
    return LastId;
}
