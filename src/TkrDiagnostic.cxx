//                                                                       
// The TkrDiagnostic class contains the information about the Level 1 Trigger count
// for an event.  
//                                                                       

#include "digiRootData/TkrDiagnostic.h"
#include <iostream>

ClassImp(TkrDiagnostic)

void TkrDiagnostic::initialize(UInt_t datum, UShort_t gtcc)
{
    m_datum = datum;
    m_gtcc = gtcc;
}

void TkrDiagnostic::Clear(Option_t *option) {
    m_datum = 0;
    m_gtcc = 0;
}

void TkrDiagnostic::Print(Option_t *option) const {
    using namespace std;
    TObject::Print(option);
    cout.precision(2);
    cout << "GTCC " << m_gtcc << "  Full data word " << m_datum << endl;
}
