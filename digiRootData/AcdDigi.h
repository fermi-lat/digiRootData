
#ifndef ROOT_AcdDigi_H
#define ROOT_AcdDigi_H

#include "AcdId.h"
#include "TObject.h"

/** @class AcdDigi
 * @brief 
 * The digitization for a single ACD entity.  This could be a 
 * tile or a fiber.  Each ACD entity has 2 PMTs associated with 
 * it.  Each PMT produces a pulse height and 3 discriminator
 * bits:  low, veto, high.  The PMT values are stored in a packed
 * word.
 * 
 * $Header$
*/

class AcdDigi: public TObject {

private:
    /**
    AcdDigi packed word layout
    (defined in following enum):
    
    @verbatim
     ____________________________________________________
    |15|14  |13  |12 |11|  |  |  |  |  |  |  |  |  |  |  |
    |__|____|____|___|__|__|__|__|__|__|__|__|__|__|__|__|
    |  |High|Veto|Low|	      PHA Value 	         |
    |__|____|____|___|___________________________________| 
    @endverbatim

    */

    enum {
	PMT_WIDTH = 12,  // width of field
	PMT_SHIFT = 0,   // shift from right
	PMT_MAX = ((1 << PMT_WIDTH) - 1), // word representing bits in this field
        LOW_WIDTH = 1,
	LOW_SHIFT = (PMT_WIDTH + PMT_SHIFT),
        VETO_WIDTH = 1,
	VETO_SHIFT = (LOW_WIDTH + LOW_SHIFT),
        HIGH_WIDTH = 1,
        HIGH_SHIFT = (VETO_WIDTH + VETO_SHIFT),
    };

public:

    typedef enum {
        A = 0,
        B = 1
    } PmtId;

    
    AcdDigi();

    AcdDigi(const AcdId& id);
    
    AcdDigi(const AcdId& id, Float_t energy, UShort_t *pha, Bool_t *veto,
        Bool_t *low, Bool_t *high);
    
    virtual ~AcdDigi() { };

    void Clear(Option_t *option ="");

    void Print(Option_t *option="") const;

    Float_t getEnergy() { return m_energy; };

    const AcdId& getId() const { return m_id; };

    /// Returns the PHA value for the PMT requested
    UShort_t getPulseHeight (AcdDigi::PmtId pmt) const;
    /// Returns 1/0 denoting whether this ACD Tile's veto threshold bit is on.
    Bool_t getVeto(AcdDigi::PmtId pmt) const;
    /// Returns true/false denoting if this Acd PMT high discrim is on/off
    Bool_t getLowDiscrim(AcdDigi::PmtId pmt) const;
    /// Returns 1/0 denoting if this ACD Tile's high discriminator bit is on (CNO).
    Bool_t getHighDiscrim(AcdDigi::PmtId pmt) const;

    /// Root >= 3.0 is now const correct for the Compare function
    Int_t Compare(const TObject *obj) const; 
    Bool_t IsSortable() const;

private:

    void initPackedWord(PmtId pmt, UShort_t pha, Bool_t veto, Bool_t low, Bool_t high);

    /// Energy deposited in MeV - provided as a check
    Float_t m_energy;
    /// packed word containing ACD digi data
    UShort_t m_packed[2];	
    /// ACD Id
    AcdId m_id; 

    ClassDef(AcdDigi,2) // Digitization for a single ACD entity
};

#endif
