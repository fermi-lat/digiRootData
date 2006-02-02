#ifndef ROOT_TIME_H
#define ROOT_TIME_H 1

#include <iostream>

#include "LsfTimeTone.h"
#include "LsfTimeHack.h"

/** @class Time
*
* $Header$
*/


class Time : public TObject {
  
public:
  
  Time( const TimeTone& current, const TimeTone& previous,
	const TimeHack& timeHack, UInt_t timeTicks)
    :m_current(current),m_previous(previous),
     m_timeHack(timeHack),m_timeTicks(timeTicks){
  }
  
  Time()
    :m_current(),m_previous(),
     m_timeHack(),m_timeTicks(0){
  }
  
  Time( const Time& other )
    :TObject(other),
     m_current(other.current()),m_previous(other.previous()),
     m_timeHack(other.timeHack()),m_timeTicks(other.timeTicks()){
  }
  
  virtual ~Time(){
  }
    
  /// Assignement operator
  inline Time& operator=( const Time& other ) {
    initialize(other.current(),other.previous(),
	       other.timeHack(),other.timeTicks());
    return *this;
  }
  
  /// The TimeTone right before the "active" one at event capture time
  inline const TimeTone& current() const { return m_current; } 
  
  /// The TimeTone that was "active" at event capture time
  inline const TimeTone& previous() const { return m_previous; }
  
  /// The TimeHack at event capture time
  inline const TimeHack& timeHack() const { return m_timeHack; } 
  
  /// The number of 50ns ticks since last the last time hack
  inline UInt_t timeTicks() const { return m_timeTicks; }
  
  /// set everything at once
  inline void initialize(const TimeTone& current, const TimeTone& previous,
			 const TimeHack& timeHack, UInt_t timeTicks) {
    m_current = current;
    m_previous = previous;      
    m_timeHack = timeHack; 
    m_timeTicks = timeTicks;
  }
  
  // set the individual data members
  inline void setCurrent( const TimeTone& val) { m_current = val; }; 
  inline void setPrevious( const TimeTone& val) { m_previous = val; };
  inline void setTimeHack( const TimeHack& val) { m_timeHack = val; }; 
  inline void setTimeTicks( UInt_t val) { m_timeTicks = val; };

  /// Reset function
  void Clear(Option_t* /* option="" */) {
    m_current.Clear("");
    m_previous.Clear("");
    m_timeHack.Clear("");      
    m_timeTicks = 0;
  }

  /// ROOT print function
  void Print(Option_t* /* option="" */) const;

  /// Create a fake for tests
  void Fake( Int_t ievent, UInt_t rank, Float_t randNum ); 

  /// Compare to another in tests
  Bool_t CompareInRange( const Time &, const std::string & name = "" ) const ; // for tests
  
private:
  
  /// 
  TimeTone m_current;
  TimeTone m_previous;
  TimeHack m_timeHack;
  UInt_t m_timeTicks;
  
  ClassDef(Time,1) ;
  
};

#endif    // ROOT_TIME_H