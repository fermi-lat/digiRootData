#include "digiRootData/AcdHeader.h"


ClassImp(AcdHeader)


AcdHeader::AcdHeader() {
    m_eventId = 0;
    m_timerWord = 0;
    m_TREQ_VETO_status = 0;
    m_deadtime_and_cause = 0;
}

AcdHeader::~AcdHeader() {
}


void AcdHeader::Clean(Option_t *option) {
    m_eventId = 0;
    m_timerWord = 0;
    m_TREQ_VETO_status = 0;
    m_deadtime_and_cause = 0;
}

