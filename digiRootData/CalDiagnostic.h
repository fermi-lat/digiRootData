#ifndef ROOT_CalDiagnostic_H
#define ROOT_CalDiagnostic_H

#include "TObject.h"

/** @class CalDiagnostic
 * @brief Store the EM CalDiagnostic trigger primitives
 *
 * $Header$
*/

class CalDiagnostic : public TObject {
public:
            
    CalDiagnostic();
    CalDiagnostic(UInt_t datum, const Char_t *label, Short_t gccc, Short_t layer);
    virtual ~CalDiagnostic();

    void initialize(UInt_t datum, const Char_t *label, Short_t gccc, Short_t layer);

    void Clear(Option_t *option ="");

    void Print(Option_t *option="") const;

    const Char_t* getLabel() const { return m_label; };
    UShort_t getGccc() const { return m_gccc; };
    UShort_t getLayer() const { return m_layer; };

    UInt_t getDataWord() const { return m_datum; };

    UInt_t getCalHigh(UInt_t end=0) const
     { // end == 0 for positive end, 1 for negative
            return (m_datum >> (13 + (end<<4))) & 0x001;
      }

    UInt_t getCalLow(UInt_t end) const
        {
            return (m_datum >> (12 + (end<<4))) & 0x001;
        }

     UInt_t getCalLogAccepts(UInt_t end) const
        {
            // end == 0 is positive, 1 is negative
            return (m_datum >> (end<<4)) & 0xfff;
        }


private:
    /// packed word containing trigger primitives for this set of logs
    UInt_t m_datum;
    Char_t m_label[3];
    UShort_t m_gccc;
    UShort_t m_layer;

    ClassDef(CalDiagnostic,1) // EM CalDiagnostic information
};

#endif
