#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "ExG4DetectorSD.hh"

using namespace std;
ExG4SensitiveDetector::ExG4SensitiveDetector(G4String name): G4VSensitiveDetector(name),
                             HIST_MAX(50*MeV),
                             HIST_MIN(0 *MeV)
{
  for(int i = 0; i<NOBINS; i++){
    histogram[i] = 0;
    histogram_angle[i] = 0;
  }
}
  G4bool ExG4SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
    {
      double energy = step->GetPreStepPoint()->GetKineticEnergy();
      double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
      if(step->GetTrack()->GetDefinition()->GetParticleName() == "proton" ){
        
        int index = int(floor((energy-HIST_MIN)/bin_width));
        if(index >= 0 && index < NOBINS)
          histogram[index]++;
        
        G4ThreeVector ang = step->GetPreStepPoint()->GetMomentumDirection();
        G4ThreeVector *centerVector = new G4ThreeVector(0, 0, 1);
        double angle=ang.angle(*centerVector);
        double bin_width_ang = (3.14) / NOBINS;
        index = int(floor((angle)/bin_width_ang));
        if(index >= 0 && index < NOBINS)
             histogram_angle[index]++;
}
      step->GetTrack()->SetTrackStatus(fStopAndKill);
      return true;
   }
ExG4SensitiveDetector::~ExG4SensitiveDetector()
{
    std::ofstream file("spectrum.dat");
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    for(int i = 0; i<NOBINS; i++)
    {
        double energy = i*bin_width + HIST_MIN;

        file << std::setw(15) << energy/MeV << " "
             << std::setw(15) << histogram[i] << std::endl;
    }
    file.close();
    file.open("angle.dat");
    bin_width = (3.14) / NOBINS;
    for(int i = 0; i<NOBINS; i++)
    {
      double angle = i*bin_width;
      file << std::setw(15) << angle << " "
             << std::setw(15) << histogram_angle[i] << std::endl;
    }
    file.close();
}