
#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class ExG4PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ExG4PrimaryGeneratorAction();
    virtual ~ExG4PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun*  fParticleGun;
    G4Box* fEnvelopeBox;
};
#endif
