
#ifndef Event_H
#define Event_H

#include "TObject.h"
#include "L1T.h"
//#include "Tagger.h"
#include "TClonesArray.h"
#include "TObjArray.h"

#include "AcdHeader.h"
#include "CalHeader.h"
#include "TkrHeader.h"

#include "ACDTile.h"
#include "CalHit.h"
#include "TkrLayer.h"

/*! \class Event
\brief This is the top-level event class to store the
raw (digi) data.
 Jun 2001 Heather Kelly - revised to use TClonesArray
 Jan 2000 Daniel Flath - ROOT HTML comments added
 Dec 1999 Daniel Flath - Rewritten for GLAST
 Oct 25,1999 Richard Dubois - Clone from LCD version
 */


class Event: public TObject {
private:
    /// Run number
    UInt_t m_run;  
    /// Event Number 
    UInt_t m_eventId;  
    
    /// Store Level 1 trigger
    L1T m_L1T;

    //Tagger *m_Tagger;       // Tagger object

    /// data members to store ACD data
    TClonesArray *m_AcdData;  //-> 
    Int_t m_numTiles;
    static TClonesArray *m_staticAcdData;
    AcdHeader m_AcdHeader;

    /// data members to store CAL data
    TClonesArray *m_CalData;  //->
    Int_t m_numLogs;
    static TClonesArray *m_staticCalData;
    CalHeader m_CalHeader;

    /// data members to store TKR data
    static TObjArray *m_staticTkrData;
    TObjArray* m_TkrData;       //-> List of Tracker layers
    Int_t m_numLayers;
    TkrHeader m_TkrHeader;


public:

    Event();
    virtual ~Event();

    void Clean(Option_t *option="");
    

    /// Access the Event number
    inline void setEventId(UInt_t id) { m_eventId = id; };
    inline Int_t getEventId() { return m_eventId; };

    /// Access the run number
    inline void setRun(UInt_t run) { m_run = run; };
    inline Int_t getRun() { return m_run; };

    /// Access ACD data
    AcdHeader* getAcdHeader() { return &m_AcdHeader; };
    TClonesArray* getAcdData() { return m_AcdData; };
    /// Add a new ACDTile entry into the ACD data array
    ACDTile* AddTile(UShort_t id);

    /// Access CAL data
    CalHeader* getCalHeader() { return &m_CalHeader; };
    TClonesArray* getCalData() { return m_CalData; };
    /// Add a new CalHit entry into the CAL data array
    CalHit* AddLog();

    /// Access TKR data
    TkrHeader* getTkrHeader() { return &m_TkrHeader; };
    TObjArray* getTkrData() { return m_TkrData; };
    /// Add a TkrLayer entry into the TKR data array
    void AddLayer(TkrLayer *layer);

    /// Access Level 1 Trigger data
    inline L1T* getL1T() { return &m_L1T; };

    // inline void setTagger(Tagger *TaggerVal) { m_Tagger = TaggerVal; };
    //inline Tagger *getTagger() const { return m_Tagger; };
    
    ClassDef(Event,3)       // Storage for per-event and subsystem data
}; 

#endif





