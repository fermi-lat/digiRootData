//
// The Event class is the top level class for the ASCII to ROOT
// conversion. It contains all the information about a single event.
//

#include "digiRootData/EventSummaryData.h"
#include <iostream>
#include "eventSummary.h"

using namespace std;

ClassImp(EventSummaryData)

EventSummaryData::EventSummaryData() {
    Clear();
}

EventSummaryData::~EventSummaryData() {
    Clear();
}

void EventSummaryData::initialize(UInt_t summary) {
    m_summary = summary;
}

void EventSummaryData::Clear(Option_t *option) {

    m_summary = 0;
}

void EventSummaryData::Print(Option_t *option) const {
    using namespace std;
    TObject::Print(option);
    cout.precision(2);
}

UInt_t EventSummaryData::calStrobe() {return EventSummary::calStrobe(m_summary); }

UInt_t EventSummaryData::tag() { return EventSummary::tag(m_summary); }

UInt_t EventSummaryData::TACK() { return EventSummary::TACK(m_summary); }

UInt_t EventSummaryData::readout4() { return EventSummary::readout4(m_summary); }

UInt_t EventSummaryData::zeroSuppress() { return EventSummary::zeroSuppress(m_summary); }

UInt_t EventSummaryData::marker() { return EventSummary::marker(m_summary); }

UInt_t EventSummaryData::error() { return EventSummary::error(m_summary); }

UInt_t EventSummaryData::diagnostic() { return EventSummary::diagnostic(m_summary); }

UInt_t EventSummaryData::eventNumber() { return EventSummary::eventNumber(m_summary); }

UInt_t EventSummaryData::trgParityError() { return EventSummary::trgParityError(m_summary); }

