#include "digiRootData/CalDigi.h"
ClassImp(CalDigi)

/*!
//------------------------------------------------------------------------------
//
// \class   CalDigi        
//  
// \brief Digitizations for Cal                                
//              
// Author:  J. Eric Grove, 23 Feb 2001
//
//------------------------------------------------------------------------------
*/


CalDigi::CalDigi() {}


CalDigi::~CalDigi() { }


/// Retrieve readout mode
const CalXtalId::CalTrigMode CalDigi::getMode() const { return m_mode; };
void CalDigi::setMode(CalXtalId::CalTrigMode m) { m_mode = m; };

/// Retrieve log identifier
const CalXtalId CalDigi::getPackedId() const { return m_xtalId; };
void CalDigi::setPackedId(CalXtalId id) { m_xtalId = id; };

void CalDigi::addReadout(CalXtalReadout r) 
{ m_readout.push_back(r); } 

/// Retrieve energy range for selected face and readout
Char_t CalDigi::getRange(short readoutIndex, CalXtalId::XtalFace face) const
{
    return (readoutIndex < m_readout.size()) ? ((m_readout[readoutIndex])).getRange(face) : (Char_t)-1;
}

/// Retrieve pulse height for selected face and readout
Short_t CalDigi::getAdc(Short_t readoutIndex, CalXtalId::XtalFace face) const
{
    return (readoutIndex < m_readout.size()) ? ((m_readout[readoutIndex])).getAdc(face) : (Short_t)-1;
}

/// Retrieve ranges and pulse heights from both ends of selected readout
const CalXtalReadout* CalDigi::getLogReadout(Short_t readoutIndex)
{
    if ( readoutIndex < m_readout.size() )
        return &(m_readout[readoutIndex]);
    else
        return 0;
    
}

/// Retrieve pulse height from selected range
Short_t CalDigi::getAdcSelectedRange(Char_t range, CalXtalId::XtalFace face) const
{
    Char_t nRanges = (Char_t)m_readout.size();
    if (nRanges == 1)
        return (range == ((m_readout[0])).getRange(face)) ? ((m_readout[0])).getAdc(face) : (Short_t)-1;
    else
        return ((m_readout[(nRanges + range - ((m_readout[0])).getRange(face)) % nRanges])).getAdc(face);
}
