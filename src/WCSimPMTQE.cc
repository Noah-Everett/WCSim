//  -*- mode:c++; tab-width:4;  -*-
#include "WCSimDetectorConstruction.hh"
#include "WCSimPMTObject.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

/***********************************************************
 *
 * This file contains the PMT QE as a function of 
 * wavelength for variety of PMTs.  It is used in both the
 * StackingAction and the sensitive detectors so it was 
 * put here (in WCSimDetectorConstruction) so both pieces of 
 * code would have access to it.
 *
 * Sourcefile for the WCSimDetectorConstruction class
 *
 ***********************************************************/


G4float WCSimDetectorConstruction::GetPMTQE(G4String CollectionName, G4float PhotonWavelength, G4int flag, G4float low_wl, G4float high_wl, G4float ratio){
  // XQ  08/17/10
  // Decide to include the QE in the WCSim detector 
  // rathe than hard coded into the StackingAction
  // This way, one can load this QE in both the StackingAction
  // and the sensitive detector.

  // flag
  // flag == 0 return the maximum QE for all wave length
  // flag == 1 return the actual QE for the wave length


  // low_wl and high_wl 
  // remove any optical photons outside the range
  // basically return QE = 0
  
  // ratio, fudge factor to increase QE for certain purpose

  // return 0 for wavelenght outside the range
  if (flag==1){
    if (PhotonWavelength <= low_wl || PhotonWavelength >= high_wl || PhotonWavelength <=280 || PhotonWavelength >=660){
      return 0;
    }
  }else if (flag==0){
    if (PhotonWavelength <= low_wl || PhotonWavelength >= high_wl){
      return 0;
    }
  }
  
  if(CollectionName!="WCIDCollectionNameIsUnused"){
  
  WCSimPMTObject *PMT;
  PMT = GetPMTPointer(CollectionName);
  G4float *wavelength;
  wavelength = PMT->GetQEWavelength();
  G4float *QE;
  QE = PMT->GetQE();
  G4float maxQE;
  maxQE = PMT->GetmaxQE();
  G4double wavelengthQE = 0;

  if (flag == 1){
    //MF: off by one bug fix.
    for (int i=0; i<=18; i++){
	  if ( PhotonWavelength <= *(wavelength+(i+1))){
		wavelengthQE = *(QE+i) + 
		  (*(QE+(i+1))-*(QE+i))/(*(wavelength+(i+1))-*(wavelength+i))*
		  (PhotonWavelength - *(wavelength+i));
      	break;
      }
    }
  }else if (flag == 0){
	wavelengthQE = maxQE; 
  }
  wavelengthQE = wavelengthQE *ratio;
  
  return wavelengthQE;
  
  } else {
    G4double wavelengthQE = 0;
    
    // do a loop over PMTs. If requesting the maxQE, use the max of any tank type
    G4float maxQE;
    for(auto acollection : WCTankCollectionNames){
        WCSimPMTObject *PMT = GetPMTPointer(acollection);
        G4float thismaxQE = PMT->GetmaxQE();
        if(thismaxQE>maxQE) maxQE=thismaxQE;
    }
    
    if (flag == 1){
      // this shouldn't be used - if using WCTankCollectionNames, use PMT_QE_Method=4.
      G4cerr<<"Call to GetPMTQE for wavelength-specific QE for WCIDCollectionName."<<G4endl;
      wavelengthQE = 0;
    }else if (flag == 0){
      wavelengthQE = maxQE; 
    }
    wavelengthQE = wavelengthQE *ratio;
    return wavelengthQE;
  }
}




