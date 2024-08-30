#include "WCSimDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4Torus.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4IntersectionSolid.hh"
#include "G4Polyhedra.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4PVReplica.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4AssemblyVolume.hh"
#include "G4SubtractionSolid.hh"
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalSurface.hh"
#include "G4UserLimits.hh"
#include "G4ReflectionFactory.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "WCSimTuningParameters.hh" //jl145

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

/*
G4LogicalVolume* WCSimDetectorConstruction::ConstructArDewar(G4VPhysicalVolume* t_parent_PV)
{
/////////////////////////////////////////
////////// Scuba Tank Geometry //////////
/////////////////////////////////////////
// [** This code was generated by scubaTank.py **]
// [Note] These are the names of all given variables:
//   |---> `t_parent_PV`: the name of the parent physical volume
//   |---> `StainlessSteel`: the material of the scuba tank
//   |---> `StainlessSteel`: the material name of the outer volume

// Variables:
G4double ST_r = 11.0*cm; // radius of the scuba tank [cm]
G4double ST_h = 75*cm; // height of the scuba tank [cm]
G4double ST_t = 0.5*cm; // thickness of the scuba tank [cm]
G4double OA_size[3] = { 100.0*cm, 42.093476939431085*cm, 154.0*cm }; // size of the outer argon [cm]
G4double OV_size[3] = { 101.0*cm, 43.093476939431085*cm, 155.0*cm }; // size of the outer volume [cm]
G4double STLocations[10][3] = {
    { 18.5*cm, -8.04673846971554*cm, -37.5*cm },
    { 37.0*cm, 8.04673846971554*cm, -37.5*cm },
    { -37.0*cm, 8.04673846971554*cm, 37.5*cm },
    { 0.0*cm, 8.04673846971554*cm, -37.5*cm },
    { -18.5*cm, -8.04673846971554*cm, 37.5*cm },
    { 0.0*cm, 8.04673846971554*cm, 37.5*cm },
    { -18.5*cm, -8.04673846971554*cm, -37.5*cm },
    { 18.5*cm, -8.04673846971554*cm, 37.5*cm },
    { -37.0*cm, 8.04673846971554*cm, -37.5*cm },
    { 37.0*cm, 8.04673846971554*cm, 37.5*cm }
}; // locations of the scuba tanks from targetGeom.py [cm]
G4ThreeVector OV_PV_pos = G4ThreeVector(0*cm, 13.470738469715544*cm, 0*cm);

// Inner Argon:
G4Material* IA_M = new G4Material("IA_M", 18, 39.948*g/mole, 0.0004891190388*kg/cm3, kStateGas, 293.15*kelvin, 300*atmosphere);
// Skipping optical properties for now
G4VSolid* IA_S = new G4Tubs("IA_S", 0*cm, ST_r-ST_t, ST_h/2-ST_t, 0*deg, 360*deg);
G4LogicalVolume* IA_LV = new G4LogicalVolume(IA_S, IA_M, "IA_LV");

// Scuba Tank:
G4VSolid* ST_S = new G4Tubs("ST_S", 0*cm, ST_r, ST_h/2, 0*deg, 360*deg);
G4LogicalVolume* ST_LV = new G4LogicalVolume(ST_S, G4Material::GetMaterial("StainlessSteel"), "ST_LV");

// Outer Argon:
G4Material* OA_M = new G4Material("OA_M", 18, 39.948*g/mole, 8.151983979999999e-06*kg/cm3, kStateGas, 293.15*kelvin, 5*atmosphere);
// Skipping optical properties for now
G4VSolid* OA_S = new G4Box("OA_S", OA_size[2]/2, OA_size[0]/2, OA_size[1]/2);
G4LogicalVolume* OA_LV = new G4LogicalVolume(OA_S, OA_M, "OA_LV");

// Outer Volume:
G4VSolid* OV_S = new G4Box("OV_S", OV_size[2]/2, OV_size[0]/2, OV_size[1]/2);
G4LogicalVolume* OV_LV = new G4LogicalVolume(OV_S, G4Material::GetMaterial("StainlessSteel"), "OV_LV");

// Place outer volume:
G4PVPlacement* OV_PV = new G4PVPlacement(0, OV_PV_pos, "OV_PV", OV_LV, t_parent_PV, false, 0, true);

// Place outer argon:
G4PVPlacement* OA_PV = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "OA_PV", OA_LV, OV_PV, false, 0, true);

// Place scuba tanks:
for (int i = 0; i < 10; i++) {
    G4PVPlacement* ST_PV = new G4PVPlacement(0, G4ThreeVector(STLocations[i][0], STLocations[i][1], STLocations[i][2]), "ST_PV", ST_LV, OA_PV, false, i, true);
    G4PVPlacement* IA_PV = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "IA_PV", IA_LV, ST_PV, false, i, true);
}
}
*/

/*
G4LogicalVolume* WCSimDetectorConstruction::ConstructArDewar(G4VPhysicalVolume* t_parent_PV)
{
/////////////////////////////////////////
////////// Scuba Tank Geometry //////////
/////////////////////////////////////////
// [** This code was generated by scubaTank.py **]
// [Note] These are the names of all given variables:
//   |---> `t_parent_PV`: the name of the parent physical volume
//   |---> `StainlessSteel`: the material of the scuba tank
//   |---> `StainlessSteel`: the material name of the outer volume

// Variables:
G4double ST_r = 11.0*cm; // radius of the scuba tank [cm]
G4double ST_h = 75*cm; // height of the scuba tank [cm]
G4double ST_t = 0.5*cm; // thickness of the scuba tank [cm]
G4double OA_size[3] = { 100.0*cm, 42.093476939431085*cm, 154.0*cm }; // size of the outer argon [cm]
G4double OV_size[3] = { 101.0*cm, 43.093476939431085*cm, 155.0*cm }; // size of the outer volume [cm]
G4double STLocations[10][3] = {
    { 18.5*cm, -8.04673846971554*cm, 37.5*cm },
    { -37.0*cm, 8.04673846971554*cm, -37.5*cm },
    { 0.0*cm, 8.04673846971554*cm, 37.5*cm },
    { 18.5*cm, -8.04673846971554*cm, -37.5*cm },
    { -18.5*cm, -8.04673846971554*cm, 37.5*cm },
    { -18.5*cm, -8.04673846971554*cm, -37.5*cm },
    { 0.0*cm, 8.04673846971554*cm, -37.5*cm },
    { 37.0*cm, 8.04673846971554*cm, -37.5*cm },
    { -37.0*cm, 8.04673846971554*cm, 37.5*cm },
    { 37.0*cm, 8.04673846971554*cm, 37.5*cm }
}; // locations of the scuba tanks from targetGeom.py [cm]
G4ThreeVector OV_PV_pos = G4ThreeVector(0*cm, 41.924*cm, 0*cm);

// Inner Argon:
G4Material* IA_M = new G4Material("IA_M", 18, 39.948*g/mole, 0.0004891190388*kg/cm3, kStateGas, 293.15*kelvin, 300*atmosphere);
// Skipping optical properties for now
G4VSolid* IA_S = new G4Tubs("IA_S", 0*cm, ST_r-ST_t, ST_h/2-ST_t, 0*deg, 360*deg);
G4LogicalVolume* IA_LV = new G4LogicalVolume(IA_S, IA_M, "IA_LV");

// Scuba Tank:
G4VSolid* ST_S = new G4Tubs("ST_S", 0*cm, ST_r, ST_h/2, 0*deg, 360*deg);
G4LogicalVolume* ST_LV = new G4LogicalVolume(ST_S, G4Material::GetMaterial("StainlessSteel"), "ST_LV");

// Outer Argon:
G4Material* OA_M = new G4Material("OA_M", 18, 39.948*g/mole, 8.151983979999999e-06*kg/cm3, kStateGas, 293.15*kelvin, 5*atmosphere);
// Skipping optical properties for now
G4VSolid* OA_S = new G4Box("OA_S", OA_size[2]/2, OA_size[0]/2, OA_size[1]/2);
G4LogicalVolume* OA_LV = new G4LogicalVolume(OA_S, OA_M, "OA_LV");

// Outer Volume:
G4VSolid* OV_S = new G4Box("OV_S", OV_size[2]/2, OV_size[0]/2, OV_size[1]/2);
G4LogicalVolume* OV_LV = new G4LogicalVolume(OV_S, G4Material::GetMaterial("StainlessSteel"), "OV_LV");

// Place outer volume:
G4PVPlacement* OV_PV = new G4PVPlacement(0, OV_PV_pos, "OV_PV", OV_LV, t_parent_PV, false, 0, true);

// Place outer argon:
G4PVPlacement* OA_PV = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "OA_PV", OA_LV, OV_PV, false, 0, true);

// Place scuba tanks:
for (int i = 0; i < 10; i++) {
    G4PVPlacement* ST_PV = new G4PVPlacement(0, G4ThreeVector(STLocations[i][0], STLocations[i][1], STLocations[i][2]), "ST_PV", ST_LV, OA_PV, false, i, true);
    G4PVPlacement* IA_PV = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "IA_PV", IA_LV, ST_PV, false, i, true);
}
}
*/

G4LogicalVolume* WCSimDetectorConstruction::ConstructArDewar(G4VPhysicalVolume* t_parent_PV)
{
/////////////////////////////////////////
////////// Scuba Tank Geometry //////////
/////////////////////////////////////////
// [** This code was generated by scubaTank.py **]
// [Note] These are the names of all given variables:
//   |---> `t_parent_PV`: the name of the parent physical volume
//   |---> `StainlessSteel`: the material of the scuba tank
//   |---> `StainlessSteel`: the material name of the outer volume

// Variables:
G4double ST_r = 11.0*cm; // radius of the scuba tank [cm]
G4double ST_h = 75*cm; // height of the scuba tank [cm]
G4double ST_t = 0.5*cm; // thickness of the scuba tank [cm]
G4double OA_size[3] = { 100.0*cm, 42.093476939431085*cm, 154.0*cm }; // size of the outer argon [cm]
G4double OV_size[3] = { 101.0*cm, 43.093476939431085*cm, 155.0*cm }; // size of the outer volume [cm]
G4double STLocations[10][3] = {
    { 18.5*cm, -8.04673846971554*cm, -37.5*cm },
    { -37.0*cm, 8.04673846971554*cm, -37.5*cm },
    { 37.0*cm, 8.04673846971554*cm, 37.5*cm },
    { -18.5*cm, -8.04673846971554*cm, -37.5*cm },
    { -18.5*cm, -8.04673846971554*cm, 37.5*cm },
    { 0.0*cm, 8.04673846971554*cm, 37.5*cm },
    { -37.0*cm, 8.04673846971554*cm, 37.5*cm },
    { 18.5*cm, -8.04673846971554*cm, 37.5*cm },
    { 37.0*cm, 8.04673846971554*cm, -37.5*cm },
    { 0.0*cm, 8.04673846971554*cm, -37.5*cm }
}; // locations of the scuba tanks from targetGeom.py [cm]
G4ThreeVector OV_PV_pos = G4ThreeVector(0*cm, 70.37726153028447*cm, 0*cm);

// Inner Argon:
G4Material* IA_M = new G4Material("IA_M", 18, 39.948*g/mole, 0.0004891190388*kg/cm3, kStateGas, 293.15*kelvin, 300*atmosphere);
// Skipping optical properties for now
G4VSolid* IA_S = new G4Tubs("IA_S", 0*cm, ST_r-ST_t, ST_h/2-ST_t, 0*deg, 360*deg);
G4LogicalVolume* IA_LV = new G4LogicalVolume(IA_S, IA_M, "IA_LV");

// Scuba Tank:
G4VSolid* ST_S = new G4Tubs("ST_S", 0*cm, ST_r, ST_h/2, 0*deg, 360*deg);
G4LogicalVolume* ST_LV = new G4LogicalVolume(ST_S, G4Material::GetMaterial("StainlessSteel"), "ST_LV");

// Outer Argon:
G4Material* OA_M = new G4Material("OA_M", 18, 39.948*g/mole, 8.151983979999999e-06*kg/cm3, kStateGas, 293.15*kelvin, 5*atmosphere);
// Skipping optical properties for now
G4VSolid* OA_S = new G4Box("OA_S", OA_size[2]/2, OA_size[0]/2, OA_size[1]/2);
G4LogicalVolume* OA_LV = new G4LogicalVolume(OA_S, OA_M, "OA_LV");

// Outer Volume:
G4VSolid* OV_S = new G4Box("OV_S", OV_size[2]/2, OV_size[0]/2, OV_size[1]/2);
G4LogicalVolume* OV_LV = new G4LogicalVolume(OV_S, G4Material::GetMaterial("StainlessSteel"), "OV_LV");

// Place outer volume:
G4PVPlacement* OV_PV = new G4PVPlacement(0, OV_PV_pos, "OV_PV", OV_LV, t_parent_PV, false, 0, true);

// Place outer argon:
G4PVPlacement* OA_PV = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "OA_PV", OA_LV, OV_PV, false, 0, true);

// Place scuba tanks:
for (int i = 0; i < 10; i++) {
    G4PVPlacement* ST_PV = new G4PVPlacement(0, G4ThreeVector(STLocations[i][0], STLocations[i][1], STLocations[i][2]), "ST_PV", ST_LV, OA_PV, false, i, true);
    G4PVPlacement* IA_PV = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "IA_PV", IA_LV, ST_PV, false, i, true);
}
}
