#include "digiRootData/TimeTone.h"

ClassImp(TimeTone) ;

void TimeTone::Print(Option_t* /*option*/) const {
  /// FIXME
  using namespace std;
  cout << "TimeTone FIXME" << endl; 
}

std::ostream& TimeTone::fillStream( std::ostream& s ) const {
    return s;
}

void TimeTone::Fake( Int_t /* ievent */, UInt_t /* rank */, Float_t /* randNum */ ) {
  /// FIXME
}

Bool_t TimeTone::CompareInRange( const TimeTone& /* other */, const std::string & /* name = "" */ ) const {
  /// FIXME
  return kTRUE;
}
