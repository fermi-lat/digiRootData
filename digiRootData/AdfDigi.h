
#ifndef ROOT_AdfDigi_H
#define ROOT_AdfDigi_H

#include "TObject.h"
#include "TClonesArray.h"

#include "commonRootData/adf/TaggerHit.h"
#include "commonRootData/adf/ScalerHit.h"
#include "commonRootData/adf/QdcHit.h"

/** @class AdfDigi
 * @brief The digitization ancillary data for beamtest 2006  
 * 
 * $Header$
*/

class AdfDigi: public TObject {

public:
    
    AdfDigi();
    virtual ~AdfDigi();

    void Clear(Option_t *option ="");

    void Print(Option_t *option="") const;

    void setEventNumber(UInt_t evtNum) { m_eventNumber = evtNum;}
    void setSpillNumber(UInt_t spillNum) { m_spillNumber = spillNum; }

    UInt_t getEventNumber() const { return m_eventNumber; }
    UInt_t getSpillNumber() const { return m_spillNumber; }

    const TClonesArray* getTaggerHitCol() const { return m_taggerHitCol; }
    const commonRootData::TaggerHit* getTaggerHit(UInt_t ind) const;
    commonRootData::TaggerHit* addTaggerHit(UInt_t moduleId, UInt_t layerId, 
                                            UInt_t stripId, Double_t pulseHgt, 
                                            Double_t sigma, 
                                            Bool_t isPedSubtracted);


    const TClonesArray* getQdcHitCol() const { return m_qdcHitCol; }
    const commonRootData::QdcHit* getQdcHit(UInt_t ind) const;
    commonRootData::QdcHit* addQdcHit(UInt_t channel, Double_t pulseHgt, UInt_t module,Double_t sigma,  Bool_t isPedSub);

    const TClonesArray* getScalerHitCol() const { return m_scalerHitCol; }
    const commonRootData::ScalerHit* getScalerHit(UInt_t ind) const;
    commonRootData::ScalerHit* addScalerHit(UInt_t channel, UInt_t value);

    void Fake( Int_t ievent, Float_t randNum );
    Bool_t CompareInRange( const AdfDigi &, const std::string & name = "" )const;

private:

    UInt_t m_eventNumber;
    UInt_t m_spillNumber;

    Int_t m_numTaggerHit;
    Int_t m_numQdcHit;
    Int_t m_numScalerHit;

    TClonesArray *m_taggerHitCol;

    TClonesArray *m_qdcHitCol;

    TClonesArray *m_scalerHitCol;

    ClassDef(AdfDigi,1) // Digitization Ancillary data beamtest 2006
};

#endif
