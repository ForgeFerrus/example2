#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "ExG4DetectorConstruction.hh"
#include "FTFP_BERT.hh" 
#include "ExG4ActionInitialization.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv)
{
	G4RunManager* runManager = new G4RunManager;
		runManager->SetUserInitialization(new ExG4DetectorConstruction);
		runManager->SetUserInitialization(new FTFP_BERT);
		runManager->SetUserInitialization(new ExG4ActionInitialization);
		runManager->Initialize();
	
	G4VisManager* visManager = new G4VisExecutive;
		visManager->Initialize();
		G4UImanager* UImanager = G4UImanager::GetUIpointer();
	
	if (argc == 1) {

	#ifdef G4UI_USE
	#endif
		G4UIExecutive* ui = new G4UIExecutive(argc, argv);
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
	}
	else {
		
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}
		delete runManager;
	return 1;
}