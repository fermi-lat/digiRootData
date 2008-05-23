// File and Version Information:
//      $Header$
//
// Description:
//  Implement the LpaFilterStatus class for storing to root the output of the LPA Event Handlers
//                                                
// Author:  Heather Kelly                   

#include "digiRootData/LpaHandler.h"
#include "Riostream.h"

ClassImp(ILpaHandler)


void ILpaHandler::initialize(UInt_t masterKey, UInt_t cfgKey, UInt_t cfgId, enums::Lsf::RsdState state,
        enums::Lsf::LeakedPrescaler prescaler, UInt_t version, enums::Lsf::HandlerId id,
        Bool_t has) {
            m_masterKey = masterKey;
            m_cfgKey = cfgKey;
            m_cfgId = cfgId;
            m_state = state;
            m_prescaler = prescaler;
            m_version = version;
            m_id = id;
            m_has = has;
        }

 void ILpaHandler::Clear(Option_t *option) {
     m_type = enums::Lsf::Unknown;
     m_masterKey = 0xFFFFFFFF;
     m_cfgKey = 0xFFFFFFFF; 
     m_cfgId = 0xFFFFFFFF;
     m_state = enums::Lsf::INVALID;
     m_prescaler = enums::Lsf::UNSUPPORTED;
     m_version = 0;
     m_id = enums::Lsf::MaxHandlerIds;
     m_has = kFALSE;
 }

 void ILpaHandler::Print(Option_t* option) const 
{
    TObject::Print(option);

    std::cout << "ILpaHandler:" << std::endl;
    return;
}


ClassImp(LpaHandler)

LpaHandler::LpaHandler() 
{
    initialize();
}

LpaHandler::~LpaHandler() 
{    
	Clear();
}

void LpaHandler::initialize() 
{
    m_lpaHandlerCol.Clear();
    m_lpaHandlerCol.AddAt(0,enums::Lsf::PASS_THRU);
    m_lpaHandlerCol.AddAt(0,enums::Lsf::GAMMA);
    m_lpaHandlerCol.AddAt(0,enums::Lsf::ASC);
    m_lpaHandlerCol.AddAt(0,enums::Lsf::MIP);
    m_lpaHandlerCol.AddAt(0,enums::Lsf::HIP);
    m_lpaHandlerCol.AddAt(0,enums::Lsf::DGN);

    return;
}


LpaHandler& LpaHandler::operator =(const LpaHandler& rhs)
{
    TObjArrayIter myIt(&rhs.m_lpaHandlerCol);
    TObject *curHandler;
    while ((curHandler = (myIt.Next()))) {
        m_lpaHandlerCol.Add(curHandler);
    }
    m_lpaHandlerCol.SetOwner(kTRUE);
    return *this;
}

void LpaHandler::Clear(Option_t *) 
{
    initialize();
    return;
}

// dummy data, just for tests
void LpaHandler::Fake( Int_t /*ievent*/, UInt_t rank, Float_t randNum ) {

    Clear() ;
}

//#define COMPARE_IN_RANGE(att) rootdatautil::CompareInRange(get ## att(),ref.get ## att(),#att)

Bool_t LpaHandler::CompareInRange( const LpaHandler & ref, const std::string & name ) const {

    Bool_t result = true ;
   
    return result ;

}

void LpaHandler::Print(Option_t* option) const 
{
    TIter it(&m_lpaHandlerCol);
    ILpaHandler *curHandler;
    while ( (curHandler = (ILpaHandler*)(it.Next()))) {
        curHandler->Print(option);
    }
}

// Add results method
void LpaHandler::addHandler(const enums::Lsf::HandlerId &id, TObject* status)
{
    m_lpaHandlerCol.AddAt(status, id);
    return;
}

// Return results method
const ILpaHandler* LpaHandler::getHandler(const enums::Lsf::HandlerId &id) const
{
    TObject *obj = m_lpaHandlerCol[id];
    if (obj)
        return ((ILpaHandler*)obj);
    else 
        return 0;
}

// Implement the LpaGammaFilter class here

ClassImp(LpaGammaFilter)

// root Clear...
void LpaGammaFilter::Clear(Option_t *option)
{
    m_status = 0;
    return;
}

// root print...
void LpaGammaFilter::Print(Option_t* option) const 
{
    TObject::Print(option);

    std::cout << "GAMMA Filter status:" << std::hex << m_status << std::dec << std::endl;
    return;
}

// Implement the LpaHipFilter class here

ClassImp(LpaHipFilter)

// root Clear...
void LpaHipFilter::Clear(Option_t *option)
{
    m_status = 0;
    return;
}

// root print...
void LpaHipFilter::Print(Option_t* option) const 
{
    TObject::Print(option);

    std::cout << "HIP status:" << std::hex << m_status << std::dec << std::endl;
    return;
}
// Implement the LpaMipFilter class here

ClassImp(LpaMipFilter)


// root Clear...
void LpaMipFilter::Clear(Option_t *option)
{
    m_status = 0;
    return;
}

// root print...
void LpaMipFilter::Print(Option_t* option) const 
{
    TObject::Print(option);

    std::cout << "MIP Filter status:" << std::hex << m_status << std::dec << std::endl;
    return;
}


// Implement the LpaDgnFilter class here

ClassImp(LpaDgnFilter)

// root Clear...
void LpaDgnFilter::Clear(Option_t *option)
{
    m_status = 0;
    return;
}

// root print...
void LpaDgnFilter::Print(Option_t* option) const 
{
    TObject::Print(option);

    std::cout << "DGN status:" << std::hex << m_status << std::dec << std::endl;
    return;
}


ClassImp(LpaPassthruFilter)

// root Clear...
void LpaPassthruFilter::Clear(Option_t *option)
{
    m_status = 0;
    return;
}

// root print...
void LpaPassthruFilter::Print(Option_t* option) const 
{
    TObject::Print(option);

    std::cout << "Passthru status:" << std::hex << m_status << std::dec << std::endl;
    return;
}

