#ifndef ROOT_DigiEvent_H
#define ROOT_DigiEvent_H

#include "TObject.h"
#include "L1T.h"
#include "TClonesArray.h"
#include "TObjArray.h"

#include "AcdDigi.h"
#include "CalDigi.h"
#include "TkrDigi.h"

#include "TkrDiagnostic.h"
#include "CalDiagnostic.h"
#include "EventSummaryData.h"

/** @class DigiEvent
 * @brief This is the top-level event class to store the Digi data.
 *
 * The DigiEvent branch contains:
 * - Run Id
 * - Event Id
 * - Time stamp
 * - Flag denoting if this data was simulated or not
 * - Level One Trigger
 * - Collection of AcdDigi objects
 * - Collection of CalDigi objects
 * - Collection of TkrDigi objects
 * - EM CAL Diagnostic trigger primitives
 * - EM TKR Diagnostic trigger primitives
 * - EM Event Summary
 *
 * @li Jun 2001 Heather Kelly - revised to use TClonesArray
 * @li Jan 2000 Daniel Flath - ROOT HTML comments added
 * @li Dec 1999 Daniel Flath - Rewritten for GLAST
 * @li Oct 25,1999 Richard Dubois - Clone from LCD version
 * $Header$
 */

class DigiEvent: public TObject {


public:

    DigiEvent();
    virtual ~DigiEvent();

    void initialize(UInt_t eventId, UInt_t runId, Double_t time, 
        const L1T& level1, const EventSummaryData &summary, Bool_t fromMc=true);

    void setEbfTime(UInt_t timeSec, UInt_t timeNanoSec, 
                    UInt_t upperPpcTimeBase, UInt_t lowerPpcTimeBase) {
        m_ebfTimeSec = timeSec;
        m_ebfTimeNanoSec = timeNanoSec;
        m_ebfUpperPpcTimeBase = upperPpcTimeBase;
        m_ebfLowerPpcTimeBase = lowerPpcTimeBase;
    }

    void Clear(Option_t *option="");
 
    void Print(Option_t *option="") const;

    inline Double_t getTimeStamp() { return m_timeStamp; };

    inline UInt_t getEbfTimeSec() { return m_ebfTimeSec; };
    inline UInt_t getEbfTimeNanoSec() { return m_ebfTimeNanoSec; };
    inline UInt_t getEbfUpperPpcTimeBase() { return m_ebfUpperPpcTimeBase; };
    inline UInt_t getEbfLowerPpcTimeBase() { return m_ebfLowerPpcTimeBase; };

    /// Access the DigiEvent number
    inline UInt_t getEventId() { return m_eventId; };

    /// Access the run number
    inline UInt_t getRunId() { return m_runId; };

    inline Bool_t getFromMc() { return m_fromMc; };

    /// retrieve the whole TClonesArray of Acd Digi data
    const TClonesArray* getAcdDigiCol() const { return m_acdDigiCol; };
    /// Add a new AcdDigi entry into the ACD digi array
    AcdDigi* addAcdDigi(const AcdId& id, const VolumeIdentifier& volId, 
        Float_t energy, UShort_t *pha, Bool_t *veto, Bool_t *low, Bool_t *high);

    /// retrieve a specific AcdDigi, based upon the layer, face, row, col, if not found returns null
    const AcdDigi* getAcdDigi(UShort_t l, UShort_t f, UShort_t r, UShort_t c) const;

    /// retrieve a specific AcdTile, based upon a valid AcdId, if not found returns null
    const AcdDigi* getAcdDigi(const AcdId &id) const;

    /// retrieve the CalDigi object
    const TClonesArray* getCalDigiCol();
    CalDigi* addCalDigi();
    const CalDigi* getCalDigi(UInt_t i) const;


    /// retrieve the whole TObjArray of TkrDigi Data
    const TObjArray* getTkrDigiCol() const { return m_tkrDigiCol; };
    /// Add a TkrDigi into the TKR data collection
    void addTkrDigi(TkrDigi *digi);
    /// retrieve a TkrDigi from the collection, using the index into the array
    const TkrDigi* getTkrDigi(UInt_t i) const;

    /// Access Level 1 Trigger data
    inline const L1T& getL1T() const { return m_levelOneTrigger; };    

    inline const EventSummaryData& getEventSummaryData() const { return m_summary; };
    inline EventSummaryData& getEventSummaryData() { return m_summary; };

    const TClonesArray *getCalDiagnosticCol() { return m_calDiagnosticCloneCol;};
    CalDiagnosticData* addCalDiagnostic();
    const CalDiagnosticData* getCalDiagnostic(UInt_t i) const;

    const TClonesArray *getTkrDiagnosticCol() { return m_tkrDiagnosticCloneCol;};
    TkrDiagnosticData* addTkrDiagnostic();
    const TkrDiagnosticData* getTkrDiagnostic(UInt_t i) const;


private:
    /// Time in seconds
    Double_t m_timeStamp;

    /// Run number
    UInt_t m_runId;  
    /// Event Number 
    UInt_t m_eventId;  
    
    /// Denote whether or not this data was simulated
    Bool_t m_fromMc;

    /// Store Level 1 trigger
    L1T m_levelOneTrigger;

    /// data members to store ACD data
    TClonesArray *m_acdDigiCol;  //-> 
    Int_t m_numAcdDigis;
    static TClonesArray *s_acdDigiStaticCol; //!

    /// data members to store CAL data
    // Avoid re-use of m_calDigiCol name that used to be a TObjArray*
    TObjArray *m_calDigiCol; 
    TClonesArray *m_calDigiCloneCol; //->
    Int_t m_numCalDigis;
    static TClonesArray *s_calDigiStaticCol; //! Collection of Cal Digi objects

    /// data members to store TKR data
    static TObjArray *s_staticTkrDigiCol;
    TObjArray* m_tkrDigiCol; //-> List of Tracker layers


    EventSummaryData m_summary;

    TClonesArray *m_tkrDiagnosticCloneCol; //->
    Int_t m_numTkrDiagnostics;
    static TClonesArray *s_tkrDiagnosticStaticCol; //! Collection of TKR diagnostic for EM

    TClonesArray *m_calDiagnosticCloneCol; //->
    Int_t m_numCalDiagnostics;
    static TClonesArray *s_calDiagnosticStaticCol; //! Collection of CAL dianostics for EM

    UInt_t m_ebfTimeSec;
    UInt_t m_ebfTimeNanoSec;


    /// These two words represent the contents of 2 32-bit PPC registers
    /// Concatenate these two words into one 64 bit word divide by 16 MHz
    /// and get an approximate time to be used to determine the sequence of 
    /// events
    UInt_t m_ebfUpperPpcTimeBase;
    UInt_t m_ebfLowerPpcTimeBase;

    ClassDef(DigiEvent,10) // Storage for Raw(Digi) event and subsystem data
}; 

#endif





