#ifndef WCSimWCDigi_h
#define WCSimWCDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

#include <set>
#include <map>
#include <vector>
#include <exception>

// for sort, find, count_if
#include <algorithm>
//for less_equal, bind2nd,...
#include <functional>

// compose2 is not part of the C++ standard
#include <ext/functional>
using __gnu_cxx::compose2;



class WCSimWCDigi : public G4VDigi
{

public:
  
  WCSimWCDigi();
  ~WCSimWCDigi();
  WCSimWCDigi(const WCSimWCDigi&);
  const WCSimWCDigi& operator=(const WCSimWCDigi&);
  int operator==(const WCSimWCDigi&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:

  //PMT parameters
  G4int   tubeID;
  G4int   lappdID;
  G4RotationMatrix rot;
  G4ThreeVector    pos;
  G4LogicalVolume* pLogV;

  //'Gates' is a digit counter or specifies subevent
  //'TriggerTimes' specifies e.g. the subevent trigger time
  std::set<int> Gates; // list of gates that were hit  
  std::vector<float> TriggerTimes;

  //lists (meaning vector/map) of information for each hit/digit created on the PMT
  std::map<int,float> pe;   ///< Charge of each Digi
  std::map<int,float> time_presmear; ///< Time of each Digi, before smearing
  std::map<int,float> time; ///< Time of each Digi
  std::vector<G4float>  time_float; ///< Same information as "time" but stored in a vector for quick time sorting
  /** \brief IDs of the hits that make up this Digit (do not use for Hits)
   *
   * Stores the unique IDs of each photon making up a digit
   * Each digit can be made from multiple photons, therefore a vector is used
   * For example: 0:[3,4,6]; 1:[10,11,13,14]
   *  The first digit in the event is made of of photons 3,4,6;
   *  The second digit is made up of photons: 10,11,13,14
   */
  std::map<int, std::vector<int> > fDigiComp;
  std::map<int, G4int>    primaryParentID; ///< Primary parent ID of the Hit (do not use for Digits)
  std::map<int, G4int>    stripno;
  std::map<int, std::map<int,double>> neigh_strips_peaks;
  std::map<int, std::map<int,double>> neigh_strips_times;
  std::map<int, std::map<int,double>> neigh_strips_lefttimes;
  std::map<int, std::map<int,double>> neigh_strips_righttimes;
  

  //integrated hit/digit parameters
  G4int                 totalPe;

  //parameters not actually used?
  G4int                 totalPeInGate;
  G4double         edep;
  static G4int     maxPe;
  G4int            trackID;

public:
  void RemoveDigitizedGate(G4int gate);
  
  inline void SetTubeID(G4int tube) {tubeID = tube;};
  inline void SetLAPPDID(G4int lappd) {lappdID = lappd;};
  inline void AddGate(int g,float t) { Gates.insert(g); TriggerTimes.push_back(t);}
  inline void SetPe(G4int gate,  G4float Q)      {pe[gate]     = Q;};
  inline void SetTime(G4int gate, G4float T)    {time[gate]   = T;};
  inline void SetPreSmearTime(G4int gate, G4float T)    {time_presmear[gate]   = T;};
  inline void SetParentID(G4int gate, G4int parent) { primaryParentID[gate] = parent; };
  inline void SetStripNo(G4int gate, G4int strip){ stripno[gate] = strip; };
  inline void SetNeighStripNo(G4int gate, std::map<int,double> neighstrip ){ neigh_strips_peaks[gate]=neighstrip; };
  inline void SetNeighStripTime(G4int gate, std::map<int,double> neighstriptime ){ neigh_strips_times[gate]=neighstriptime; };
  inline void SetNeighStripLeftTime(G4int gate, std::map<int,double> neighstriplefttime ){ neigh_strips_lefttimes[gate]=neighstriplefttime; };
  inline void SetNeighStripRightTime(G4int gate, std::map<int,double> neighstriprighttime ){ neigh_strips_righttimes[gate]=neighstriprighttime; };

  // Add a digit number and unique photon number to fDigiComp
  inline void AddPhotonToDigiComposition(int digi_number, int photon_number){
    fDigiComp.at(digi_number).push_back(photon_number);
  }
  // Add a whole vector for one digit to fDigiComp. Clear input vector once added.
  void AddDigiCompositionInfo(std::vector<int> & digi_comp){
    const size_t size = fDigiComp.size();
    fDigiComp.emplace(size,digi_comp);
    digi_comp.clear();
  }

  inline G4int   GetParentID(int gate) { return primaryParentID.at(gate);};
  inline G4float GetGateTime(int gate) { return TriggerTimes.at(gate);}
  inline G4int   GetTubeID() {return tubeID;};
  inline G4int   GetLAPPDID() {return lappdID;};
  inline G4float GetPe(int gate)     {return pe.at(gate);};
  inline G4float GetTime(int gate)   {
    try {
      return time.at(gate);
    }
    catch (...) {
      G4cerr<<"Exception occurred while attempting to use WCSimWCDigi::GetTime to retrieve time for pe "
            << gate << " from map of times. The time map has "<<time.size()<<" entries:" << G4endl;
      for (auto& x: time){
        try{
          G4cerr << x.first << ": ";
          G4cerr << x.second << G4endl;
        }
        catch (...) {
          G4cerr << G4endl << "Exception reading map entry!!"<<G4endl;
          break;
        }
      }
      throw;
    }
  };
  inline std::map<int,float>::const_iterator GetTimeMapBegin() {return time.cbegin();}
  inline std::map<int,float>::const_iterator GetTimeMapEnd() {return time.cend();}
  inline G4float GetPreSmearTime(int gate)   {return time_presmear.at(gate);};
  std::vector<int> GetDigiCompositionInfo(int gate);
  inline std::map< int, std::vector<int> > GetDigiCompositionInfo(){return fDigiComp;}
  inline G4int   GetStripNo(int gate){ return stripno[gate];};
  inline std::map<int,double> GetNeighStripNo(int gate){ return neigh_strips_peaks[gate]; };
  inline std::map<int,double> GetNeighStripTime(int gate){ return neigh_strips_times[gate]; };
  inline std::map<int,double> GetNeighStripLeftTime(int gate){ return neigh_strips_lefttimes[gate]; };
  inline std::map<int,double> GetNeighStripRightTime(int gate){ return neigh_strips_righttimes[gate]; };

  inline int NumberOfGates() { return Gates.size();}
  inline int NumberOfSubEvents() { return (Gates.size()-1);}
  inline bool HasHitsInGate(int number) { return (Gates.count(number)>0); }
  
  G4LogicalVolume* GetLogicalVolume() {return pLogV;};


  void SetEdep         (G4double de)                { edep = de; };
  void SetPos          (G4ThreeVector xyz)          { pos = xyz; };
  void SetLogicalVolume(G4LogicalVolume* logV)      { pLogV = logV;}
  void SetTrackID      (G4int track)                { trackID = track; };
  void SetRot          (G4RotationMatrix rotMatrix) { rot = rotMatrix; };
  G4int         GetTotalPe()    { return totalPe;};
  
  void SetMaxPe(G4int number = 0)  {maxPe   = number;};

  void AddPe(G4float hitTime)  
  {
    // Increment the totalPe number
    totalPe++; 
        
    time_float.push_back(hitTime);
  }

  void SortHitTimes() {   sort(time_float.begin(),time_float.end()); }


  void SortDigiMapsByHitTime() {
    int i, j;
    float index_time,index_timepresmear,index_pe;
    int index_primaryparentid;
    std::vector<int> index_digicomp;
    bool sort_digi_compositions = (fDigiComp.size()==time.size());
    // SortDigiMapsByHitTime is called by WCSimWCDigitizerSKI::DigitizeHits to sort the WCRawPMTSignalCollection.
    // Each entry in WCRawPMTSignalCollection represents the set of photon hits on a PMT.
    // Since a photon hit has no "composition", fDigiComp is empty at this time and needn't be sorted.
    // for generality, sort if the digi composition map has the same size as other maps
    for (i = 1; i < (int) time.size(); ++i)
      {
        index_time  = time.at(i);
        index_timepresmear  = time_presmear.at(i);
        index_pe = pe.at(i);
        if(sort_digi_compositions) index_digicomp = fDigiComp.at(i);
        index_primaryparentid = primaryParentID.at(i);
        for (j = i; j > 0 && time.at(j-1) > index_time; j--) {
          time.at(j) = time.at(j-1);
          time_presmear.at(j) = time_presmear.at(j-1);
          pe.at(j) = pe.at(j-1);
          if(sort_digi_compositions) fDigiComp.at(j) = fDigiComp.at(j-1);
          primaryParentID.at(j) = primaryParentID.at(j-1);
          //G4cout <<"swapping "<<time[j-1]<<" "<<index_time<<G4endl;
        }
        time.at(j) = index_time;
        time_presmear.at(j) = index_timepresmear;
        pe.at(j) = index_pe;
        if(sort_digi_compositions) fDigiComp.at(j) = index_digicomp;
        primaryParentID.at(j) = index_primaryparentid;
      }
  }
  
  void insertionSort(int a[], int array_size)
  {
    int i, j, index;
    for (i = 1; i < array_size; ++i)
      {
        index = a[i];
        for (j = i; j > 0 && a[j-1] > index; j--)
          a[j] = a[j-1];
        
        a[j] = index;
      }
  }


  G4float GetFirstHitTimeInGate(G4float low,G4float upevent)
  {
    G4float firsttime;
    std::vector<G4float>::iterator tfirst = time_float.begin();
    std::vector<G4float>::iterator tlast = time_float.end();
    
    std::vector<G4float>::iterator found = 
      std::find_if(tfirst,tlast,
		   compose2(std::logical_and<bool>(),
			    std::bind2nd(std::greater_equal<G4float>(),low),
			    std::bind2nd(std::less_equal<G4float>(),upevent)
			    )
		   );
    if ( found != tlast ) {
      firsttime = *found; // first hit time
    }
    else {
      firsttime = -10000.; //error code.
    }
    //G4cout << "firsthit time " << firsttime << "\n";
    return firsttime;
  }

 
};

typedef G4TDigiCollection<WCSimWCDigi> WCSimWCDigitsCollection;
extern G4Allocator<WCSimWCDigi> WCSimWCDigiAllocator;

inline void* WCSimWCDigi::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) WCSimWCDigiAllocator.MallocSingle();
  return aDigi;
}

inline void WCSimWCDigi::operator delete(void* aDigi)
{
  WCSimWCDigiAllocator.FreeSingle((WCSimWCDigi*) aDigi);
}

#endif









