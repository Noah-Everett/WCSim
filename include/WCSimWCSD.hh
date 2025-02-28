#ifndef WCSimWCSD_h
#define WCSimWCSD_h 1

#include "G4VSensitiveDetector.hh"
#include "WCSimWCHit.hh"
#include "WCSimDetectorConstruction.hh"

class G4Step;
class G4HCofThisEvent;

class WCSimWCSD : public G4VSensitiveDetector
{
 public:
  WCSimWCSD(G4String,G4String,WCSimDetectorConstruction*, G4String);
  ~WCSimWCSD();
  
  void   Initialize(G4HCofThisEvent*);

  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void   EndOfEvent(G4HCofThisEvent*);
 
  void   ReadInPMTWiseQE();  
 
 private:

  G4int HCID;
  WCSimDetectorConstruction* fdet;
  WCSimWCHitsCollection* hitsCollection;
  G4String detectorElement;
  std::map<int,int> PMTHitMap;   // Whether a PMT was hit already

  std::vector<double> vector_pmtqe;	//Individual PMT tuning factors


};

#endif

