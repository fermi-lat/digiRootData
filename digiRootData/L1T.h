#ifndef ROOT_L1T_H
#define ROOT_L1T_H

#include "TObject.h"

/** @class L1T
 * @brief Store the Level One Trigger information
 *
 * $Header$
*/

class L1T : public TObject {
public:
    
    enum  {
        // definition of  trigger bits        
        b_ACDL =     1,  //  set if cover or side veto, low threshold
        b_ACDH =     2,   //  cover or side veto, high threshold
        b_Track=     4,   //  3 consecutive x-y layers hit
        b_LO_CAL=    8,  //  single log above low threshold
        b_HI_CAL=   16,   //  3 cal layers in a row above high threshold
        number_of_trigger_bits = 5
    };
            
    L1T();
    L1T(UInt_t trigger);
    L1T(const L1T& level1);
    virtual ~L1T();

    void initialize(UInt_t trigger);

    void Clear(Option_t *option ="");

    void Print(Option_t *option="") const;

    UInt_t getTriggerWord() const { return m_trigger; };

    /// kTRUE indicates that ACD LOW occurred
    bool getAcdLow() const { return m_trigger & b_ACDL;};
    /// kTRUE indicates that ACD HIGH occurred
    bool getAcdHigh() const { return m_trigger & b_ACDH;};
    /// kTRUE indicates that 3-in-a-row occurred in the TKR
    bool getTkr3InARow() const { return m_trigger & b_Track;};
    /// kTRUE indicates that CAL LOW occurred
    bool getCalLow() const { return m_trigger & b_LO_CAL; };
    /// kTRUE indicates that CAL HIGH occurred
    bool getCalHigh() const { return m_trigger & b_HI_CAL; };

private:
    /// packed word containing trigger bits
    UInt_t    m_trigger;    

    ClassDef(L1T,4) // Level 1 Trigger information
};

#endif
