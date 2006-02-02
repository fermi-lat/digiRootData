#ifndef ROOT_RUNINFO_H
#define ROOT_RUNINFO_H 1

#include <iostream>
#include "TObject.h"
#include "enums/Lsf.h"

/** @class RunInfo
* @brief encapsulate the run id parts of the event context
*
* 
*
* $Header$
*/

class RunInfo : public TObject {
    
public:
  
  RunInfo( )
    : m_platform(enums::Lsf::NoPlatform), m_origin(enums::Lsf::NoOrigin), m_id(0), m_startTime(0) {
  }
  
  RunInfo( enums::Lsf::Platform p, enums::Lsf::DataOrigin d, UInt_t id, UInt_t startTime )
    : m_platform(p), m_origin(d), m_id(id), m_startTime(startTime) {
  }
  
  RunInfo( const RunInfo& other )
    : TObject(other), 
      m_platform(other.platform()), m_origin(other.dataOrigin()), 
      m_id(other.id()), m_startTime(other.startTime()) {
  }
  
  ~RunInfo() {
  }
  
  /// Assignement operator
  inline RunInfo& operator=( const RunInfo& other ) {
    initialize(other.platform(),other.dataOrigin(),
	       other.id(),other.startTime());
    return *this;
  }
  
  /// The platform this run was taken on
  inline enums::Lsf::Platform platform() const { 
    return m_platform;
  }
  
  /// The type of data from this run (Orbit, MC or ground) data
  inline enums::Lsf::DataOrigin dataOrigin() const {
    return m_origin;
  }
    
  /// The ground based ID of this run
  /// This is usually defined on the ground, but if the LAT DAQ reboots on-orbit, the 
  /// Ground ID can be reset
  inline UInt_t id() const {
    return m_id;
  }
  
  /// The start time of this run
  /// This is the number of seconds since GLAST epoch start when the run started
  /// FIXME (is this latched when the trigger was enabled?)
  inline UInt_t startTime() const {
    return m_startTime;
  }
  
  /// set everything at once
  inline void initialize(enums::Lsf::Platform p, enums::Lsf::DataOrigin d, 
			 UInt_t id, UInt_t startTime ) {
    m_platform = p;
    m_origin = d;
    m_id = id;
    m_startTime = startTime;
  }
  
  // set the individual data members
  inline void setPlatform(enums::Lsf::Platform val) { m_platform = val; }
  inline void setDataOrigin(enums::Lsf::DataOrigin val) { m_origin = val; }
  inline void setId ( UInt_t val ) { m_id = val; }
  inline void setStartTime ( UInt_t val ) { m_startTime = val; }
  
  /// this is a helper function for formated printing
  void printString(std::ostream& s) const {
    static const char* Platforms[3] = {"Lat","Testbed","Host"};
    static const char* DataOrigins[3] = {"Orbit","MC","Ground"};
    if ( m_platform == enums::Lsf::NoPlatform ) {
      s << "None_";
    } else {
      s << Platforms[m_platform] << '_' ;
    }
    if ( m_origin == enums::Lsf::NoOrigin ) {
      s << "None_";
    } else {
      s << DataOrigins[m_origin] << '_';     
    }
    s << m_id << '_' << m_startTime;
  }

  /// Reset function
  void Clear(Option_t* /* option="" */) {
    m_platform = enums::Lsf::NoPlatform;
    m_origin = enums::Lsf::NoOrigin;
    m_id = 0;
    m_startTime = 0;
  }

  /// ROOT print function
  void Print(Option_t* /* option="" */) const;

  /// Create a fake for tests
  void Fake( Int_t ievent, UInt_t rank, Float_t randNum ); 

  /// Compare to another in tests
  Bool_t CompareInRange( const RunInfo&, const std::string & name = "" ) const ; // for tests

  /// For sorting, override TObject::Compare()
  virtual Int_t Compare(const TObject *obj) const; 
  
  /// Specify that this class is sortable
  virtual Bool_t IsSortable() const { return kTRUE; };
  
private:
  
  ///
  enums::Lsf::Platform m_platform;
  
  /// 
  enums::Lsf::DataOrigin m_origin;
  
  ///
  UInt_t m_id;
  
  ///
  UInt_t m_startTime;

  ClassDef(RunInfo,1) ;

};


#endif    // EVENT_RUNINFO_H
