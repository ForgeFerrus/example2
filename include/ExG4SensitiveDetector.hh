#include<G4VSensitiveDetector.hh>
#ifndef ExG4SensitiveDetector_h
#define ExG4SensitiveDetector_h

   class G4Step;
   class G4TouchableHistory;

   class ExG4SensitiveDetector: public G4VSensitiveDetector
     {
     private:
      static const int NOBINS = 1000;
      const double HIST_MAX;
      const double HIST_MIN;
      int histogram[NOBINS];
      int histogram_angle[NOBINS];
     public:
      ExG4SensitiveDetector(G4String name);
      ~ExG4SensitiveDetector();
      G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
     };
#endif /* SENSITIVEDETECTOR */
