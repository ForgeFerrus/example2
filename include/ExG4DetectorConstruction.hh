
#ifndef ExG4DetectorConstruction_h
#define ExG4DetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class ExG4DetectorConstruction : public G4VUserDetectorConstruction
{
  public:    
    ExG4DetectorConstruction();
    virtual ~ExG4DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
  protected:
};
#endif
