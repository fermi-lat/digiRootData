
#ifndef ACDTile_H
#define ACDTile_H

#include "TileID.h"
#include "TObject.h"

/*! \class ACDTile
\brief 
 Jun 2001 Heather Kelly - Remove pointer to TileID
 Feb 2000 Daniel Flath - Rewrite to facilitate standardization of
			 code & interface across all classes.
 Jan 2000 Daniel Flath - ROOT HTML comments added
 Dec 1999 Daniel Flath - Rewritten for GLAST
 Oct 25,1999 Richard Dubois Clone from LCD version
*/

class ACDTile: public TObject {
private:
    /*!
    ACDTile tag word layout
    (defined in following enum):
     _______________________________________________
    |15|  |  |12|11|  |  |  |  |  |  |	|  |  |  |00|
    |__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|
    |Hit Status |	      PHA Value 	    |
    |___________|___________________________________| 

    */

    enum {
	ACD_K_PMT = 12,
	ACD_V_PMT = 0,
	ACD_M_PMT = ((1 << ACD_K_PMT) - 1),
	ACD_K_HIT = 4,
	ACD_V_HIT = (ACD_K_PMT + ACD_V_PMT),
	ACD_M_HIT = ((1 << ACD_K_HIT) - 1)
    };
    UShort_t m_tag;	// Packed word containing tile data
    TileID m_tileID;   // Tile identity info class
public:
    ACDTile();
   // ACDTile(TileID& id);
    ACDTile(UShort_t id);
    virtual ~ACDTile();
    TileID* getID() { return &m_tileID; };
    UShort_t getPHA();
    UChar_t getHit();
    Bool_t setPHA(UShort_t pmtVal);
    Bool_t setHit(UChar_t hitVal);

    /// Root >= 3.0 is now const correct for the Compare function
    Int_t Compare(const TObject *obj) const; 
    Bool_t IsSortable() const;

    ClassDef(ACDTile,3) 	// Information on a single ACD Tile
};

#endif
