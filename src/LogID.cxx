///////////////////////////////////////////////////////////////////////////
//                                                                        
// The LogID class contains a log ID number (encoding of detector
// element position) as well as functions to obtain the location of
// log in question. LogID is used in the CalHit class.
//                                                                        
///////////////////////////////////////////////////////////////////////////

// access and set functions for binary calorimeter tags
// Version 1.0 21 Oct 1998 Richard creation
// Version 1.1 25 Oct 1999 R.Dubois Clone from LCD

#include "digiRootData/LogID.h"
#include "TClass.h"

ClassImp(LogID)

///________________________________________________________________________
LogID::LogID(){
    // Default constructor
    // All fields in tagword initialized to 0
    setTag(static_cast<UInt_t>(0));
}
///________________________________________________________________________
LogID::LogID(UInt_t tag=0) {
    // Create a LogID object with number tag
    setTag(tag);
}
///________________________________________________________________________
LogID::~LogID() {
    // Destructor
}
///________________________________________________________________________
UInt_t LogID::getTag() const { 
    // Returns the log number
    return m_tag;
}
///________________________________________________________________________
Bool_t LogID::isValidColumn(UInt_t columnVal) {
    // Check if given value is a valid Column number:

    return (
            ((columnVal <= BOUNDS_COLUMN) && !(columnVal & ~CAL_M_COLUMN)) ?
            kTRUE : kFALSE
           );
}
///________________________________________________________________________
Bool_t LogID::isValidPipeLine(UInt_t pipeVal) {
    // Check if given value is a valid pipe number:

    return (
            ((pipeVal <= BOUNDS_PIPE) && !(pipeVal & ~CAL_M_PIPE)) ?
            kTRUE : kFALSE
           );
}
///________________________________________________________________________
/*
Bool_t LogID::isValidID(UInt_t idVal) {
    // Check length of idVal:
    if (idVal & CAL_M_ID)
        return kFALSE;
    
    // Check Pipeline bin:
    if (!isValidPipeLine(getPipeLine(idVal))
        return kFALSE;
}
*/
///________________________________________________________________________
Bool_t LogID::fillGeomFromID(LogID::TAG_STRUCT *ts) {
    // fill Layer, Column fields from ID fields:
    
    if (!isValidPipeLine(ts->pipeline))
        return kFALSE;
    if (ts->sequence & ~CAL_M_SEQ)
        return kFALSE;
    if (ts->xy & ~CAL_M_XY)
        return kFALSE;
    if (ts->tower & ~CAL_M_TOWER)
        return kFALSE;

    // Calculation code copied from LogID::isValidTagWord, it should be therefore
    // moved to a single function called from both places...  (TODO)

    // seq_divisor is 1/2 the number of possible sequence values:
    UInt_t seq_divisor = 1 << (CAL_K_SEQ - 1);
    UInt_t layerVal = ((ts->sequence % seq_divisor) << CAL_K_XY) | ts->xy;
    UInt_t columnVal = ts->pipeline * 2 + (ts->sequence / seq_divisor);
    
    ts->layer = layerVal;
    ts->column = columnVal;

    // If we got this far, everything must be ok...
    return kTRUE;
}
///________________________________________________________________________
Bool_t LogID::fillIDFromGeom(LogID::TAG_STRUCT *ts) {
    // fill Pipeline, ADC Sequence, etc. from Geometry fields: 

    if (!isValidColumn(ts->column))
        return kFALSE;
    // strip off the first bit it's the XY bit in the tag word
    if ((ts->layer >> CAL_K_XY) & ~CAL_M_LAYER)
        return kFALSE;
    if (ts->tower & ~CAL_M_TOWER)
        return kFALSE;

    // Calculate XY, PIPELINE, ADC SEQUENCE from layer and column...
    UInt_t xyVal = ts->layer & CAL_M_XY;
    UInt_t pipeVal = ts->column / ((BOUNDS_COLUMN + 1) / (BOUNDS_PIPE + 1));
    UInt_t seqVal = (ts->column % 2) * (1 << (CAL_K_SEQ - 1)) + 
                    (ts->layer >> CAL_K_XY);

    ts->xy = xyVal;
    ts->pipeline = pipeVal;
    ts->sequence = seqVal;

    // If we got this far, everything must be ok...
    return kTRUE;
}
///________________________________________________________________________
Bool_t LogID::isValidTagStruct(TAG_STRUCT ts) {
    // Test the validity of a particular tag structure.
    // Ensures that fields which don't use all possible values are
    // within bounds.  Compares 'geometric' and 'electronic' position data
    // and ensure that they are equivalent.

    // Test fields that don't use all possible values for correct range...
    if ((!isValidColumn(ts.column))     ||
        (!isValidPipeLine(ts.pipeline))
       )
        return kFALSE;
    
    // Calculate the column and layer from the Pipeline, Sequence and XY
    // fields.  Then compare...

    // seq_divisor is 1/2 the number of possible sequence values:
    UInt_t seq_divisor = 1 << (CAL_K_SEQ - 1);

    UInt_t layerVal = ((ts.sequence % seq_divisor) << CAL_K_XY) | ts.xy;
    if (layerVal != ts.layer) 
        return kFALSE;

    UInt_t columnVal = ts.pipeline * 2 + (ts.sequence / seq_divisor);
    if (columnVal != ts.column)
        return kFALSE;

    // If we got this far, everything must be ok...
    return kTRUE;
}
///________________________________________________________________________
Bool_t LogID::isValidTagWord(UInt_t tagWord) {
    // In this function, we must ensure that the (Pipeline, Sequence, XY)
    // and (Layer, Column) data map to identical logs.  If this is not the
    // case, then the data encoded in the tagword is contradictory and 
    // should not be used.  This function also tests fields to ensure that 
    // values are within valid range.  It is important that this function 
    // is called on all tag words before they are stored or used!
    
    TAG_STRUCT ts;
    fillTagStruct(tagWord, &ts);
    
    return isValidTagStruct(ts);
}
///________________________________________________________________________
///
/// ACCESS FUNCTIONS for tagword fields:
///________________________________________________________________________
UInt_t LogID::getTower(UInt_t tagWord) {
    // Returns the GLAST tower this log belongs to.  In the '99/2000
    // beamtest, this value is always 0.

    return static_cast<UInt_t>((tagWord >> CAL_V_TOWER) & CAL_M_TOWER);
}
///________________________________________________________________________
UInt_t LogID::getColumn(UInt_t tagWord) {
    // Returns the column of the log in the calorimeter
    // Columns are numberd 0-9.  Looking at the positive X face of the cal
    // the log ends are numbered 0-9 from left to right.  Looking at the 
    // Positive Y face of the cal, the log ends are numbered 0-9 from right
    // to left.

    return static_cast<UInt_t>((tagWord >> CAL_V_COLUMN) & CAL_M_COLUMN);
}
///________________________________________________________________________
UInt_t LogID::getLayer(UInt_t tagWord) {
    // Returns the layer this log is in.  Layers are numbered from
    // 0: (closest to TKR) to 7: (furthest from TKR).

    UInt_t layerVal = (tagWord >> CAL_V_LAYER) & CAL_M_LAYER;
    layerVal <<= CAL_K_XY;
    layerVal |= getXY(tagWord);

    return layerVal;
}
///________________________________________________________________________
UInt_t LogID::getID(UInt_t tagWord) {
    // Returns the id of this log.  Each log in the calorimeter has a unique
    // id value based upon it's position in the cal.
    
    return static_cast<UInt_t>((tagWord >> CAL_V_ID) & CAL_M_ID);
}
///________________________________________________________________________
UInt_t LogID::getPipeline(UInt_t tagWord) {
    // Returns the electronics pipeline the log is read out through

    return static_cast<UInt_t>((tagWord >> CAL_V_PIPE) & CAL_M_PIPE);
}
///________________________________________________________________________
UInt_t LogID::getSequence(UInt_t tagWord) {
    // Returns the electronics ADC sequence the log is read out from

    return static_cast<UInt_t>((tagWord >> CAL_V_SEQ) & CAL_M_SEQ);
}
///________________________________________________________________________
UInt_t LogID::getXY(UInt_t tagWord) {
    // Returns whether the log is in an x or y plane of the cal.
    
    return static_cast<UInt_t>((tagWord >> CAL_V_XY) & CAL_M_XY);
}
///________________________________________________________________________
// Fill a TAG_STRUCT with data from tagVal.
// *** NOTE: There is no assertion that user supplied tagword contains
// valid fields!
void LogID::fillTagStruct(UInt_t tagVal, LogID::TAG_STRUCT *ts) {
    ts->column = getColumn(tagVal);
    ts->layer = getLayer(tagVal);
    ts->pipeline = getPipeline(tagVal);
    ts->sequence = getSequence(tagVal);
    ts->tower = getTower(tagVal);
    ts->xy = getXY(tagVal);
}
///________________________________________________________________________
// Fill a tagword from a tag structure:
// *** NOTE: There is no assertion that user supplied tag struct contains
// valid fields!
UInt_t LogID::fillTagWord(LogID::TAG_STRUCT *ts) {
    UInt_t tagWord = 0;
    tagWord += (ts->xy & CAL_M_XY) << CAL_V_XY;
    tagWord += (ts->sequence & CAL_M_SEQ) << CAL_V_SEQ;
    tagWord += (ts->pipeline & CAL_M_PIPE) << CAL_V_PIPE;
    // When setting layer bits, shed common XY bit from layer value...
    tagWord += ((ts->layer >> CAL_K_XY) & CAL_M_LAYER) << CAL_V_LAYER;
    tagWord += (ts->column & CAL_M_COLUMN) << CAL_V_COLUMN;
    tagWord += (ts->tower & CAL_M_TOWER) << CAL_V_TOWER;

    return tagWord;
}
///________________________________________________________________________
Bool_t LogID::setTag(UInt_t tagVal) { 
    // Set value of tag word to tagVal if taVal is valid

    if (isValidTagWord(tagVal)) {
        m_tag = tagVal;
        return kTRUE;
    }
    else return kFALSE;
}
///________________________________________________________________________
Bool_t LogID::setTag(TAG_STRUCT *ts) {
    // Fill tag word from values in a tag struct.

    if (isValidTagStruct(*ts)) {
        m_tag = fillTagWord(ts);
        return kTRUE;
    }
    else return kFALSE;
}
///________________________________________________________________________
UInt_t LogID::getColumn() const {
    // return column value from tag word:

    return getColumn(m_tag);
}
///_______________________________________________________________________
Bool_t LogID::setColumn(UInt_t columnVal) {
    // Sets the column field in the tag word

    if (!isValidColumn(columnVal)) 
        return kFALSE;

    m_tag &= ~(CAL_M_COLUMN << CAL_V_COLUMN);
    m_tag |= columnVal << CAL_V_COLUMN;

    return kTRUE;
}
///________________________________________________________________________
UInt_t LogID::getID() const {
    // Returns the unique id of this log

    return getID(m_tag);
}
///________________________________________________________________________
LogID::CALAxes LogID::getXY() const {
    // Returns whether this log is in an x (logs || x-axis) or y 
    // (logs || y-axis) layer

    return (CALAxes)getXY(m_tag);
}
///_______________________________________________________________________
Bool_t LogID::setXY(CALAxes xyVal) {
    // Sets the XY field in the tag word
    
    m_tag &= ~(CAL_M_XY << CAL_V_XY);
    m_tag |= xyVal << CAL_V_XY;

    return kTRUE;
}
///________________________________________________________________________
UInt_t LogID::getLayer() const {
    // return layer value from tag word:

    return getLayer(m_tag);
}
///________________________________________________________________________
UInt_t LogID::getPipeline() const {
    // return layer value from tag word:

    return getPipeline(m_tag);
}
///________________________________________________________________________
UInt_t LogID::getSequence() const {
    // return ADC sequence value from tag word:

    return getSequence(m_tag);
}
///________________________________________________________________________
Bool_t LogID::setLayer(UInt_t layerVal) {
    // Sets the layer field in the tag word

    // *** See note in header (in the private enum of tagword fields) 
    // *** as to why the following is done:
    // Strip off LSB, as it goes in the XY field...
    UInt_t xyVal = (layerVal & CAL_M_XY);
    // Now get the layer value minus the XY bit...
    UInt_t lVal = (layerVal >> CAL_K_XY);

    // Check if the remaining bits represent a valid layer value:
    if (lVal & ~CAL_M_LAYER)
        return kFALSE;

    // Set LAYER and XY fields...
    m_tag &= ~(CAL_M_LAYER << CAL_V_LAYER);
    m_tag |= lVal << CAL_V_LAYER;
    m_tag &= ~(CAL_M_XY << CAL_V_XY);
    m_tag |= xyVal << CAL_V_XY;

    return kTRUE;
}
///________________________________________________________________________
/*
Bool_t LogID::setID(UInt_t idVal) {
    if (!isValidID(idVal))
        return kFALSE;
    



    return kTRUE;
}
*/
///________________________________________________________________________
/// Implement the streamer ourselves for now...to take advantage
/// of schema evolution - and to allow our TBEvent class to handle
/// both old (<= Root v2.25) Root files, and new (>= Root v3.00) files
void LogID::Streamer(TBuffer &R__b)
{
   // Stream an object of class LogID.

   if (R__b.IsReading()) {
      UInt_t R__s, R__c;
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); 
      if (R__v > 1) 
      { 
          LogID::Class()->ReadBuffer(R__b, this, R__v, R__s, R__c);
          return;
      }
      /// Old Versions
      TObject::Streamer(R__b);
      R__b >> m_tag;
   } else {
       LogID::Class()->WriteBuffer(R__b, this);
   }
}
