#ifndef ROOT_TkrDiagnostic_H
#define ROOT_TkrDiagnostic_H

#include "TObject.h"

/** @class TkrDiagnostic
 * @brief Store the EM TkrDiagnostic trigger primitives
 *
 * $Header$
*/

class TkrDiagnostic : public TObject {
public:
            
    TkrDiagnostic() : m_datum(0), m_gtcc(0) {};
    TkrDiagnostic(UInt_t datum, UShort_t gtcc) : m_datum(datum), m_gtcc(gtcc) {}
    virtual ~TkrDiagnostic() {}

    UInt_t getTriggerRequest() const { return m_datum; };
    Bool_t getTriggerRequest(UShort_t gtrc)const { return ((m_datum & (1 << gtrc)) ? true : false); };
    Short_t getGtcc() const { return m_gtcc; };

    void initialize(UInt_t datum, UShort_t gtcc);

    void Clear(Option_t *option ="");

    void Print(Option_t *option="") const;

private:
    /// packed word containing trigger primitive for these TKR layers
    UInt_t m_datum;    
    UShort_t m_gtcc;

    ClassDef(TkrDiagnostic,1) // EM TkrDiagnostic information
};

#endif
