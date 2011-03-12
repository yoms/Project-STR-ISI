#include "FeuStation.h"

FeuStation::FeuStation()
{
}

bool FeuStation::indiquerPassage() {
    return this->m_station->indiquerPassage();
}

void FeuStation::addStation(Station* s){
    m_station = s;
}
