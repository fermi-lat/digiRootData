
#ifndef ROOT_AcdDigi_H
#define ROOT_AcdDigi_H

#include "commonRootData/idents/AcdId.h"
#include "TObject.h"
#include "TString.h"
#include "commonRootData/idents/VolumeIdentifier.h"

/** @class AcdDigi
 * @brief The digitization data for a single ACD entity (tile or ribbon).  
 * 
 * This digitization could represent a 
 * tile or a ribbon.  Each ACD entity has two PMTs (A and B) associated with 
 * it.  Each PMT contains:
 * - PHA (pulse height)
 * - range (low or high)
 * - odd parity bit associated with each PMT read out
 * - header parity bit stored in the AEM header
 * - Three Discriminators:  
 *   -# low(accept map bit)
 *   -# veto (hit map bit)
 *   -# high (cno) - only for use with MC data
 * The PMT values are stored in a packed word.
 * Details concerning the ACD detector data can be found in:
 * ACD ICD document LAT-SS-00363-08
 * and in the AEM description:  
 * http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/AEM.pdf
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
    |15|14  |13   |12    |11|  |  |  |  |  |  |  |  |  |  |  |
    |__|____|_____|_____ |__|__|__|__|__|__|__|__|__|__|__|__|
    |  |High|Veto |Low   |      PHA Value 	             |
    |  |CNO |Hit  |Accept|                                   | 
    |__|___|______|______|___________________________________| 
    @endverbatim


    ldf packed word contains header parity, range, odd parity error information
    @verbatim
     ____________________________________________________
    | | | | | |  |  |  |  |  |  |  |  | 2    | 1   | 0   |
    |_|_|_|_|_|__|__|__|__|__|__|__|__|_    _|_____|_____|
    | | | | | |  |  |  |  |  |  |  |  |Header|Range|Odd  |
    | | | | | |  |  |  |  |  |  |  |  | Error|     |Parity|
    |_|_| |_|________________________________|_____|_____| 
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
  
    enum {
        ERROR_WIDTH = 1,
        ERROR_SHIFT = 0,
        RANGE_WIDTH = 1,
        RANGE_SHIFT = (ERROR_WIDTH + ERROR_SHIFT),
        HEADERPARITY_WIDTH = 1,
        HEADERPARITY_SHIFT = (RANGE_SHIFT + HEADERPARITY_WIDTH)
    };

public:
	/** @defgroup AcdDigiGroup AcdDigi End-User Interface */
	/*@{*/
    /// Identifies PMT as either A or B
    typedef enum {
        A = 0,
        B = 1
    } PmtId;

    typedef enum {
        LOW = 0,
        HIGH = 1
    } Range;

    typedef enum {
        NOERROR = 0,
        ERROR = 1
    } ParityError;
	/*@}*/

    
    AcdDigi();

    AcdDigi(const AcdId& id);
    
    AcdDigi(const AcdId& id, const VolumeIdentifier& volId, Float_t energy, 
        UShort_t *pha, Bool_t *veto,
        Bool_t *low, Bool_t *high);
    
    virtual ~AcdDigi() { };

    void initLdfParameters(const char *tileName, int tileNumber, Range *rangeCol, ParityError *oddParityCol, ParityError *headerParityCol);

    void initGem(Bool_t ninja, Bool_t gem) {
        m_ninja = ninja;
        m_gem = gem;
    }

    void Clear(Option_t *option ="");

    void Print(Option_t *option="") const;

    /** @ingroup AcdDigiGroup */
    /*@{*/
    /// Returns the Monte Carlo energy deposited in this ACD detector
    Float_t getEnergy() const { return m_energy; };

    /// Returns the proper AcdId corresponding to the official numbering scheme
    const AcdId& getId() const { return m_id; };

    /// VolId for the detector
    const VolumeIdentifier& getVolId() const { return m_volId; };

    /// Returns the PHA value for the PMT requested
    UShort_t getPulseHeight (AcdDigi::PmtId pmt) const;
    /// Returns True/False denoting whether this ACD Tile's veto (hit map) bit is on.
    /// deprecated method name, see getHitMapBit
    Bool_t getVeto(AcdDigi::PmtId pmt) const;
    /// Returns True/False denoting whether this ACD Tile's veto (hit map) bit is on.
    Bool_t getHitMapBit(AcdDigi::PmtId pmt) const { return getVeto(pmt); };

    /// Returns true/false denoting if this Acd PMT accept bit is on/off
    /// deprecated method name, see getAcceptMapBit
    Bool_t getLowDiscrim(AcdDigi::PmtId pmt) const;
    /// Returns true/false denoting if this Acd PMT accept bit is on/off
    Bool_t getAcceptMapBit(AcdDigi::PmtId pmt) const { return getLowDiscrim(pmt); };
    /// Returns true/false denoting if this ACD Tile's high discriminator bit is on (CNO).
    /// deprecated method for real data - ultimately CNO will only be available 
    /// through GEM.  Only has meaning for MC data
    Bool_t getHighDiscrim(AcdDigi::PmtId pmt) const;
    /// deprecated method for real data - Returns true/false denoting if this 
    /// ACD Tile's high discriminator (CNO) bit is on. 
    /// Only has meaning for MC data
    Bool_t getCno(AcdDigi::PmtId pmt) const { return getHighDiscrim(pmt); };

    /// Returns the tile number as reported by LDF - may not correspond
    /// to ACD id conventions - use getId or getTileName instead
    Int_t getTileNumber() const { return m_tileNumber; };

    /// Returns the string associated with this tile, as reported by LDF
    /// Conforms to proper ACD detector id numbering scheme
    const char* getTileName() const { return m_tileName.Data(); };

    /// Returns the range of this PMT (low or high) (currently real data only)
    /// WARNING: many versions ROOT always draw this as '0' b/c they don't handle
    /// enums correctly in the Draw() function
    Range getRange(AcdDigi::PmtId pmt) const;

    /// Returns the odd parity bit for the requested PMT (real data only)
    ParityError getOddParityError(AcdDigi::PmtId pmt) const;

    /// Returns Header parity bit aka CMD/Data error from AEM header (real data only)
    ParityError getHeaderParityError(AcdDigi::PmtId pmt) const;
    /*@}*/

    /// Returns True if pmt was read out in low range
    Bool_t isLowRange(AcdDigi::PmtId pmt) const { return getRange(pmt) == LOW; }

    /// Returns True if this AcdDigi was created solely due to GEM bit in TileList
    Bool_t isNinja() const { return m_ninja; }

    /// Returns True if GEM bit in TileList is set for this detector
    Bool_t getGemFlag() const { return m_gem; }

    /// Root >= 3.0 is now const correct for the Compare function
    Int_t Compare(const TObject *obj) const; 
    Bool_t IsSortable() const;

private:

    void initPackedWord(PmtId pmt, UShort_t pha, Bool_t veto, Bool_t low, Bool_t high);

    void initPackedLdfWord(PmtId pmt, Range range, ParityError error, ParityError headerParity);

    /// Energy deposited in MeV - provided as a check on MC
    Float_t m_energy;
    /// packed word containing ACD digi data
    UShort_t m_packed[2];	
    /// ACD Id - contains methods to retrieve proper ACD id
    AcdId m_id; 
    /// Volume id for geometry
    VolumeIdentifier m_volId;

    // New data members for version 3 
    UShort_t m_packedLdf[2];
    /// Tile number as reported by LDF, may not conform to proper id conventions
    Int_t m_tileNumber;
    /// String returned from LDF, which does conform to proper id conventions
    TString m_tileName;

    Bool_t m_ninja;  // Set if this AcdDigi was created solely due to GEM bit
    Bool_t m_gem;     // Set if the GEM bit in the TileList is set for this detector

    ClassDef(AcdDigi,4) // Digitization for a single ACD entity
};

#endif
