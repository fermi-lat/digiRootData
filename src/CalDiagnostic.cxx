//                                                                       
// The CalDiagnostic class contains the EM diagnostic CAL trigger primitives 
//                                                                       

#include "digiRootData/CalDiagnostic.h"
#include <iostream>

ClassImp(CalDiagnostic)

CalDiagnostic::CalDiagnostic() : m_datum(0), m_gccc(0), m_layer(0)
{
}

CalDiagnostic::CalDiagnostic(UInt_t datum, const Char_t *label, Short_t gccc, Short_t layer)
: m_datum(datum), m_gccc(gccc), m_layer(layer)
{
    strcpy(m_label, label);
}

CalDiagnostic::~CalDiagnostic() {

}

void CalDiagnostic::initialize(UInt_t datum, const Char_t *label, Short_t gccc, Short_t layer)
{
    m_datum=datum;
    m_gccc=gccc;
    m_layer=layer;
    strcpy(m_label, label);
}

void CalDiagnostic::Clear(Option_t *option) {
    m_datum = 0;
    m_gccc = 0;
    m_layer = 0;
}

void CalDiagnostic::Print(Option_t *option) const {
    using namespace std;
    TObject::Print(option);
    cout.precision(2);
    cout << "GCCC: " << m_gccc << " Layer " << m_layer << "  Data Word: " << m_datum << endl;
}
