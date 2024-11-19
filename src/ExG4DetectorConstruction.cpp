
#include "ExG4DetectorConstruction.hh"
#include "ExG4SensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

ExG4DetectorConstruction::ExG4DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

ExG4DetectorConstruction::~ExG4DetectorConstruction()
{ }

G4VPhysicalVolume* ExG4DetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();

  G4double det_sizeXY = 25*cm, det_sizeZ = 0.15*cm;

  G4Material* det_mat = nist->FindOrBuildMaterial("G4_W");

  G4bool checkOverlaps = true;

  G4double world_sizeXY = 30*cm;
  G4double world_sizeZ  = 20*cm;

  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
    new G4Box("World",                       
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          
                        world_mat,          
                        "World");            

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                    
                      G4ThreeVector(),      
                      logicWorld,           
                      "World",              
                      0,                   
                      false,                
                      0,                    
                      checkOverlaps);       
  G4Box* solidDet =
    new G4Box("Detector",                    
        0.5*det_sizeXY, 0.5*det_sizeXY, 0.5*det_sizeZ); 

  G4LogicalVolume* logicDet =
    new G4LogicalVolume(solidDet,            
                        det_mat,             
                        "Detector");         

  new G4PVPlacement(0,                       
                    G4ThreeVector(0,0,5*cm), 
                    logicDet,                
                    "Detector",              
                    logicWorld,              
                    false,                   
                    0,                       
                    checkOverlaps);          
  G4LogicalVolume* logicTar =
    new G4LogicalVolume(solidDet,            
                        det_mat,             
                        "Target");     
  new G4PVPlacement(0,                       
                    G4ThreeVector(0,0,-5*cm),
                    logicTar,                
                    "Target",              
                    logicWorld,            
                    false,                  
                    0,                      
                    checkOverlaps);
  return physWorld;
}
void ExG4DetectorConstruction::ConstructSDandField()
{
  G4String trackerChamberSDname = "SensitiveDetector";
  ExG4SensitiveDetector* aTrackerSD = new ExG4SensitiveDetector(trackerChamberSDname);
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  SetSensitiveDetector("Detector", aTrackerSD, true);
}