#include "digiRootData/LsfTime.h"
#include <iostream>

ClassImp(Time) ;

void Time::Print(Option_t* /*option*/) const {
  /// FIXME
  using namespace std;
  cout << "Time FIXME" << endl; 
}

void Time::Fake( Int_t /* ievent */, UInt_t /* rank */, Float_t /* randNum */ ) {
  /// FIXME
}

Bool_t Time::CompareInRange( const Time& /* other */, const std::string & /* name = "" */ ) const {
  /// FIXME
  return kTRUE;
}